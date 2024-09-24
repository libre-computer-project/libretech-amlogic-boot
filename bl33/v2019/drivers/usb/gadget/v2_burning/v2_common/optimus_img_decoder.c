// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include "../v2_sdc_burn/optimus_sdc_burn_i.h"
static int image_check_last_verify_item(HIMAGE hImg);

//FIMXE:
COMPILE_TYPE_CHK(128 == sizeof(ItemInfo_V1), _op_a);
COMPILE_TYPE_CHK(576 == sizeof(ItemInfo_V2), __op_a2);
COMPILE_TYPE_CHK(64  == sizeof(AmlFirmwareImg_t), __op_b);

typedef struct _ImgSrcIf{
        unsigned        devIf;             //mmc/usb/store
        unsigned        devNo;          //0/1/2
        unsigned        devAlignSz;     //64K for store
        unsigned        reserv2Align64;
        uint64_t        itemCurSeekOffsetInImg;//fread will auto seek the @readSz, but for STORE we must do it

        char            partName[28];       //partIndex <= 28 (+4 if partIndex not used)
        unsigned        partIndex;      //partIndex and part
	unsigned int	pkg_sz_part1;
	unsigned int	pkg_sz_part2;
	unsigned char   resrv[512 - 32 - 24 - 8];
}ImgSrcIf_t;

COMPILE_TYPE_CHK(512  == sizeof(ImgSrcIf_t), bb);
#define MAX_ITEM_NUM 48

typedef struct _ImgInfo_s
{
        ImgSrcIf_t          imgSrcIf;
        AmlFirmwareImg_t    imgHead;//Must begin align 512, or store read will exception
        union               ItemInfo_u{
                            ItemInfo_V1 v1[MAX_ITEM_NUM];
                            ItemInfo_V2 v2[MAX_ITEM_NUM];
        }itemInfo;

}ImgInfo_t;

typedef struct _AmlFirmwareItem0_s
{
    __u32           itemId;
    __u32           fileType;           //image file type, sparse and normal
    __u64           curoffsetInItem;    //current offset in the item
    __u64           offsetInImage;      //item offset in the image
    __u64           itemSz;             //item size in the image
    const char*     itemMainType;
    const char*     itemSubType;
}ItemInfo;

static int _hFile = -1;
static int _is_part2_pkg;

//open a Amlogic firmware image
//return value is a handle
HIMAGE image_open(const char* interface, const char* device, const char* part, const char* imgPath)
{
    const int HeadSz = sizeof(ImgInfo_t) - sizeof(ImgSrcIf_t);
    ImgInfo_t* hImg = (ImgInfo_t*)OPTIMUS_BURN_PKG_HEAD_BUF_ADDR;
    int ret = 0;
    ImgSrcIf_t* pImgSrcIf = NULL;
    unsigned imgVer = 0;

    pImgSrcIf = &hImg->imgSrcIf;
    memset(pImgSrcIf, 0, sizeof(ImgSrcIf_t));

    if (!strcmp("store", interface))
    {
	DWN_DBG("imgHead=0x%p, hImg=%p\n", &hImg->imgHead, hImg);
	ret = store_logic_read(part, IMG_OFFSET_IN_PART, HeadSz, &hImg->imgHead);
	if (ret) {
		DWN_ERR("Fail to read image header.\n");
		ret = __LINE__; goto _err;
	}
	pImgSrcIf->devIf = IMAGE_IF_TYPE_STORE;
	pImgSrcIf->devAlignSz = 4 * 1024;//512;//OPTIMUS_DOWNLOAD_SLOT_SZ;
	strncpy(pImgSrcIf->partName, part, strnlen(part, 28));
    }
    else
    {
	    pImgSrcIf->pkg_sz_part1 = (unsigned)do_fat_get_fileSz(imgPath);
	    env_set("usb_burn_part1_img", imgPath);
	    run_command("setenv usb_burn_part2_img ${usb_burn_part1_img}.part2", 0);
	    pImgSrcIf->pkg_sz_part2 = (unsigned)do_fat_get_fileSz(env_get("usb_burn_part2_img"));

            int pFile = do_fat_fopen(imgPath);
            if (pFile < 0) {
                    DWN_ERR("Fail to open file %s\n", imgPath);
                    goto _err;
            }
            _hFile = pFile;
	    _is_part2_pkg = 0;

            ret = do_fat_fread(pFile, (u8*)&hImg->imgHead, HeadSz);
            if (ret != HeadSz) {
                    DWN_ERR("want to read %d, but %d\n", HeadSz, ret);
                    goto _err;
            }

            pImgSrcIf->devAlignSz = do_fat_get_bytesperclust(pFile);
	    DWN_MSG("pkg_sz_part1/2 0x%x/0x%x\n",
		    pImgSrcIf->pkg_sz_part1, pImgSrcIf->pkg_sz_part2);
	if (pImgSrcIf->pkg_sz_part1 + pImgSrcIf->pkg_sz_part2 > hImg->imgHead.imageSz) {
		DWN_ERR("pkg_sz_part1/2 head sz 0x%llx\n", hImg->imgHead.imageSz);
		goto _err;
	}
    }

    if (IMAGE_MAGIC != hImg->imgHead.magic) {
        DWN_ERR("error magic 0x%x\n", hImg->imgHead.magic);
        goto _err;
    }
    imgVer = hImg->imgHead.version;
    if (AML_FRMWRM_VER_V1 !=  imgVer && AML_FRMWRM_VER_V2 != imgVer) {
        DWN_ERR("error version 0x%x\n", hImg->imgHead.version);
        goto _err;
    }
    DWN_MSG("image version [0x%08x]\n", imgVer);
    if (MAX_ITEM_NUM < hImg->imgHead.itemNum) {
            DWN_ERR("max itemNum(%d)<actual itemNum (%d)\n", MAX_ITEM_NUM, hImg->imgHead.itemNum);
            goto _err;
    }

	if (image_check_last_verify_item(hImg)) {
		DWN_ERR("Fail in check image integrity\n");
		return NULL;
	}

    return hImg;
_err:
    return NULL;
}

unsigned image_get_crc(HIMAGE hImg)
{
    ImgInfo_t* imgInfo = (ImgInfo_t*)hImg;
    return imgInfo->imgHead.crc;
}


//close a Amlogic firmware image
int image_close(HIMAGE hImg)
{
    DWN_MSG("to close image\n");

    if (_hFile >= 0)do_fat_fclose(_hFile) , _hFile = -1;

    if (hImg) {
        hImg = NULL;
    }
    return 0;
}

static const ItemInfo* image_item_get_item_info_byid(HIMAGE hImg, const int itemIndex)
{
        ImgInfo_t* imgInfo = (ImgInfo_t*)hImg;
        const unsigned imgVer = imgInfo->imgHead.version;
        static ItemInfo theItem;

        switch (imgVer)
        {
                case AML_FRMWRM_VER_V2:
                        {
                                ItemInfo_V2* pItem = &imgInfo->itemInfo.v2[itemIndex];
                                theItem.itemMainType    = pItem->itemMainType;
                                theItem.itemSubType     = pItem->itemSubType;
                                theItem.itemSz          = pItem->itemSz;
                                theItem.offsetInImage   = pItem->offsetInImage;
                                theItem.curoffsetInItem = pItem->curoffsetInItem;
                                theItem.fileType        = pItem->fileType;
                                theItem.itemId          = pItem->itemId;
                        }
                        break;

                case AML_FRMWRM_VER_V1:
                        {
                                ItemInfo_V1* pItem = &imgInfo->itemInfo.v1[itemIndex];
                                theItem.itemMainType    = pItem->itemMainType;
                                theItem.itemSubType     = pItem->itemSubType;
                                theItem.itemSz          = pItem->itemSz;
                                theItem.offsetInImage   = pItem->offsetInImage;
                                theItem.curoffsetInItem = pItem->curoffsetInItem;
                                theItem.fileType        = pItem->fileType;
                                theItem.itemId          = pItem->itemId;
                        }
                        break;

                default:
                        DWN_ERR("Exception, imgVer=0x%x\n", imgVer);
                        return NULL;
        }

        return &theItem;
}

static int _do_pkg_fseek(HIMAGE hImg, s64 pkg_offset, int wherehence)
{
	ImgInfo_t *imgInfo          = (ImgInfo_t *)hImg;
	const u32 pkg_sz_part1 = imgInfo->imgSrcIf.pkg_sz_part1;
	int i = 0;

	if (wherehence) {
		DWN_ERR("only start supported\n");
		return -__LINE__;
	}
	DWN_DBG("pkg offset 0x%llx\n", pkg_offset);
	if (_is_part2_pkg) {
		if (pkg_offset < pkg_sz_part1) {
			DWN_MSG("change to pkg part1\n");
			do_fat_fclose(_hFile);
			_hFile = do_fat_fopen(env_get("usb_burn_part1_img"));
			_is_part2_pkg = 0;
		}
	} else {
		if (pkg_offset >= pkg_sz_part1) {
			DWN_MSG("to pkg part2 4 off 0x%llx\n", pkg_offset);
			do_fat_fclose(_hFile);
			_hFile = do_fat_fopen(env_get("usb_burn_part2_img"));
			_is_part2_pkg = 1;
		}
	}
	if (_hFile < 0) {
		DWN_ERR("Err file index\n");
		return -__LINE__;
	}

	pkg_offset -= _is_part2_pkg * (s64)pkg_sz_part1;
	i = do_fat_fseek(_hFile, pkg_offset, wherehence);
	if (i) {
		DWN_ERR("fail to seek, offset is 0x%x\n", (u32)pkg_offset);
		return -__LINE__;
	}

	return 0;
}

//open a item in the image
//@hImage: image handle;
//@mainType, @subType: main type and subtype to index the item, such as ["IMAGE", "SYSTEM"]
HIMAGEITEM image_item_open(HIMAGE hImg, const char* mainType, const char* subType)
{
    ImgInfo_t* imgInfo          = (ImgInfo_t*)hImg;
    const int itemNr            = imgInfo->imgHead.itemNum;
    const ItemInfo*      pItem  = NULL;
    int i = 0;

    for (; i < itemNr ;i++)
    {
            pItem = image_item_get_item_info_byid(hImg, i);
            if (!pItem) {
                    DWN_ERR("Fail to get item at index %d\n", i);
                    return NULL;
            }

            if (!strcmp(mainType, pItem->itemMainType) && !strcmp(subType, pItem->itemSubType))
            {
                    break;
            }
    }
    if (i >= itemNr) {
        DWN_WRN("Can't find item [%s, %s]\n", mainType, subType);
        return NULL;
    }

    if (i != pItem->itemId) {
        DWN_ERR("itemid %d err, should %d\n", pItem->itemId, i);
        return NULL;
    }

    if (IMAGE_IF_TYPE_STORE != imgInfo->imgSrcIf.devIf)
    {
		DWN_MSG("Item offset 0x%llx\n", pItem->offsetInImage);
		i = _do_pkg_fseek(hImg, pItem->offsetInImage, 0);
		if (i) {
			DWN_ERR("fail to seek, offset is 0x%x\n", (u32)pItem->offsetInImage);
			return NULL;
		}
    }
    imgInfo->imgSrcIf.itemCurSeekOffsetInImg = pItem->offsetInImage;

    return (HIMAGEITEM)pItem;
}

//Need this if item offset in the image file is not aligned to bytesPerCluster of FAT
unsigned image_item_get_first_cluster_size(HIMAGE hImg, HIMAGEITEM hItem)
{
    const ImgInfo_t* imgInfo = (ImgInfo_t*)hImg;
    ItemInfo* pItem = (ItemInfo*)hItem;
    unsigned itemSizeNotAligned = 0;
    const unsigned fat_bytesPerCluste = imgInfo->imgSrcIf.devAlignSz;

    itemSizeNotAligned = pItem->offsetInImage & (fat_bytesPerCluste - 1);
    itemSizeNotAligned = fat_bytesPerCluste - itemSizeNotAligned;

    DWN_MSG("itemSizeNotAligned 0x%x\n", itemSizeNotAligned);
    return itemSizeNotAligned;
}

unsigned image_get_cluster_size(HIMAGEITEM hImg)
{
    const ImgInfo_t* imgInfo = (ImgInfo_t*)hImg;
    const unsigned fat_bytesPerCluste = imgInfo->imgSrcIf.devAlignSz;

    return fat_bytesPerCluste;
}

//close a item
int image_item_close(HIMAGEITEM hItem)
{
    return 0;
}

__u64 image_item_get_size(HIMAGEITEM hItem)
{
    ItemInfo* pItem = (ItemInfo*)hItem;

    return pItem->itemSz;
}


//get image item type, current used type is normal or sparse
int image_item_get_type(HIMAGEITEM hItem)
{
    ItemInfo* pItem = (ItemInfo*)hItem;

    return pItem->fileType;
}

//read item data, like standard fread
int image_item_read(HIMAGE hImg, HIMAGEITEM hItem, void* pBuf, const __u32 wantSz)
{
    ImgInfo_t* imgInfo = (ImgInfo_t*)hImg;
	ImgSrcIf_t *img_src = &imgInfo->imgSrcIf;
    unsigned readSz = 0;

    if (IMAGE_IF_TYPE_STORE == imgInfo->imgSrcIf.devIf)
    {
            char* part = imgInfo->imgSrcIf.partName;
            const uint64_t offsetInPart = imgInfo->imgSrcIf.itemCurSeekOffsetInImg + IMG_OFFSET_IN_PART;
            int rc = 0;
            const unsigned storeBlkSz      = imgInfo->imgSrcIf.devAlignSz;
            const unsigned offsetNotAlign = offsetInPart & (storeBlkSz - 1);
            const unsigned sizeNotAlignInFirstBlk = storeBlkSz - offsetNotAlign;//in the the first block and its offset not aligned

            //Attention: deal with the align issue in "optimus_burn_one_partition", then not need to modify "do_fat_fread"
            if (offsetNotAlign)
            {
                    unsigned char* bufInABlk = NULL;
                    const uint64_t readOffset = offsetInPart - offsetNotAlign;
                    const unsigned bufLen = sizeNotAlignInFirstBlk < wantSz ? sizeNotAlignInFirstBlk : (wantSz);
                    unsigned thisTotalReadSz = wantSz;

                    DWN_MSG("offsetInPart %llx, wantSz=%x\n", offsetInPart, wantSz);
                    bufInABlk = (u8*)malloc(storeBlkSz);
                    rc = store_logic_read(part, readOffset, storeBlkSz, bufInABlk);
                    if (rc) {
                            DWN_ERR("Fail to read: readOffset=%llx, storeBlkSz=%x\n", readOffset, storeBlkSz);
                            free(bufInABlk);
                            return __LINE__;
                    }
                    memcpy(pBuf, bufInABlk + offsetNotAlign, bufLen);
                    thisTotalReadSz -= bufLen;
                    pBuf            += bufLen/sizeof(void);
                    free(bufInABlk);

                    if (sizeNotAlignInFirstBlk < wantSz && offsetNotAlign)
                    {
                            rc = store_logic_read(part, (offsetInPart + sizeNotAlignInFirstBlk), thisTotalReadSz, pBuf);
                            if (rc) {
                                    DWN_ERR("Fail in store_logic_read_ops to read %u at offset %llx.\n", wantSz,
                                                    offsetInPart + sizeNotAlignInFirstBlk);
                                    return __LINE__;
                            }
                    }
            }
            else
            {
                    rc = store_logic_read(part, offsetInPart, wantSz, pBuf);
                    if (rc) {
                            DWN_ERR("Fail in store_logic_read_ops to read %u at offset %llx.\n", wantSz, offsetInPart);
                            return __LINE__;
                    }
            }

            imgInfo->imgSrcIf.itemCurSeekOffsetInImg += wantSz;
    }
    else
    {
	long fpos = 0;
	int part2_need = wantSz;
	int part1_need = 0;
	const unsigned pkg_sz_part1 = img_src->pkg_sz_part1;

	fpos = do_fat_ftell(_hFile);
	if (!_is_part2_pkg && fpos + wantSz > pkg_sz_part1) {
		part2_need  = fpos + wantSz - pkg_sz_part1;
		part1_need = wantSz - part2_need;
		readSz = do_fat_fread(_hFile, pBuf, part1_need);
		if (readSz != part1_need) {
			DWN_ERR("want read 0x%x, but 0x%x\n", part1_need, readSz);
			return __LINE__;
		}
		if (_do_pkg_fseek(hImg, pkg_sz_part1, 0)) {
			DWN_ERR("Fail in pkg seek\n");
			return __LINE__;
		}
	}
	readSz = do_fat_fread(_hFile, pBuf + part1_need, part2_need);
	if (readSz != part2_need) {
		DWN_ERR("want to read 0x%x, but 0x%x\n", part2_need, readSz);
		return __LINE__;
	}
    }

    return 0;
}

int get_total_itemnr(HIMAGE hImg)
{
    ImgInfo_t* imgInfo = (ImgInfo_t*)hImg;

    return imgInfo->imgHead.itemNum;
}

HIMAGEITEM get_item(HIMAGE hImg, int itemId)
{
    int ret = 0;
    ImgInfo_t* imgInfo = (ImgInfo_t*)hImg;
    const ItemInfo* pItem    = NULL;

    pItem = image_item_get_item_info_byid(hImg, itemId);
    if (!pItem) {
            DWN_ERR("Fail to get item at index %d\n", itemId);
            return NULL;
    }
    if (itemId != pItem->itemId) {
        DWN_ERR("itemid %d err, should %d\n", pItem->itemId, itemId);
        return NULL;
    }
    DWN_MSG("get item [%s, %s] at %d\n", pItem->itemMainType, pItem->itemSubType, itemId);

    if (IMAGE_IF_TYPE_STORE != imgInfo->imgSrcIf.devIf)
    {
	ret = _do_pkg_fseek(hImg, pItem->offsetInImage, 0);
	if (ret) {
		DWN_ERR("fail to seek, offset is 0x%x, ret=%d\n", (u32)pItem->offsetInImage, ret);
		return NULL;
	}
    }
    imgInfo->imgSrcIf.itemCurSeekOffsetInImg = pItem->offsetInImage;

    return (HIMAGEITEM)pItem;
}

int get_item_name(HIMAGE hImg, int itemId, const char** main_type, const char** sub_type)
{
    const ItemInfo* pItem    = NULL;

    pItem = image_item_get_item_info_byid(hImg, itemId);
    if (!pItem) {
            DWN_ERR("Fail to get item at index %d\n", itemId);
            return __LINE__;
    }
    if (itemId != pItem->itemId) {
        DWN_ERR("itemid %d err, should %d\n", pItem->itemId, itemId);
        return __LINE__;
    }
    DWN_DBG("get item [%s, %s] at %d\n", pItem->itemMainType, pItem->itemSubType, itemId);

    *main_type = pItem->itemMainType;
    *sub_type  = pItem->itemSubType;

    return OPT_DOWN_OK;
}

__u64 image_get_item_size_by_index(HIMAGE hImg, const int itemId)
{
    const ItemInfo* pItem    = NULL;

    pItem = image_item_get_item_info_byid(hImg, itemId);
    if (!pItem) {
            DWN_ERR("Fail to get item at index %d\n", itemId);
            return 0;
    }
    if (itemId != pItem->itemId) {
        DWN_ERR("itemid %d err, should %d\n", pItem->itemId, itemId);
        return __LINE__;
    }
    DWN_DBG("get item [%s, %s] at %d\n", pItem->itemMainType, pItem->itemSubType, itemId);

    return pItem->itemSz;
}

static int image_check_last_verify_item(HIMAGE hImg)
{
	int i = 0;
	int last_index = get_total_itemnr(hImg) - 1;
	ItemInfo *cur_info = NULL;
	const int rd_len = 32;
	char rd_buf[rd_len];
	char *Vry_head = "sha1sum ";

	for (i = last_index; i >= 0; --i) {
		cur_info = get_item(hImg, i);
		if (!cur_info) {
			DWN_ERR("Fail in get item by id\n");
			return -__LINE__;
		}
		if (strcmp(cur_info->itemMainType, "VERIFY"))
			continue;
		break;//find last verify item
	}
	if (image_item_read(hImg, cur_info, rd_buf, rd_len)) {
		DWN_ERR("Fail read last vry item\n");
		return -__LINE__;
	}
	DWN_DBG("rd_buf %s\n", rd_buf);
	if (strncmp(rd_buf, Vry_head, strlen(Vry_head))) {
		DWN_ERR("verify item head error\n");
		return -__LINE__;
	}

	return 0;
}

u64 optimus_img_decoder_get_data_parts_size(HIMAGE hImg, int* hasBootloader)
{
    int i = 0;
    int ret = 0;
    u64 dataPartsSz = 0;
    const int totalItemNum = get_total_itemnr(hImg);

    *hasBootloader = 0;
    for (i = 0; i < totalItemNum; i++)
    {
        const char* main_type = NULL;
        const char* sub_type  = NULL;

        ret = get_item_name(hImg, i, &main_type, &sub_type);
        if (ret) {
            DWN_ERR("Exception:fail to get item name!\n");
            return __LINE__;
        }

        if (strcmp("PARTITION", main_type)) { continue; }
        if (!strcmp("bootloader", sub_type)) {
                *hasBootloader = 1;
                continue;
        }
        if (!strcmp(AML_SYS_RECOVERY_PART, sub_type))
        {
                if (OPTIMUS_WORK_MODE_SYS_RECOVERY == optimus_work_mode_get()) continue;
        }

        dataPartsSz += image_get_item_size_by_index(hImg, i);
    }

    return dataPartsSz;
}

int optimus_img_item2buf(HIMAGE hImg, const char* main, const char* sub, char* buf, int* bufsz)
{
    HIMAGEITEM hImgItem = NULL;
    hImgItem = image_item_open(hImg, main, sub);
	unsigned itemSzNotAligned = 0;
	int		 alignSz	= 0;

    if (!hImgItem) {
        DWN_WRN("Fail to open item [%s,%s]\n", main, sub);
        return ITEM_NOT_EXIST;
    }

    const s64 itemSz = image_item_get_size(hImgItem);
    if (!itemSz) {
        DWN_ERR("Item size 0\n");
        image_item_close(hImgItem); return __LINE__;
    }
    if (itemSz > *bufsz) {
        DWN_ERR("item sz %lld > bufsz %d\n", itemSz, *bufsz);
        image_item_close(hImgItem); return __LINE__;
    }

	itemSzNotAligned = image_item_get_first_cluster_size(hImg, hImgItem);
	if (itemSzNotAligned /*& 0x7*/) {//Not Aligned 8bytes/64bits, mmc dma read will failed
		const unsigned clusterSz = image_get_cluster_size(hImg);

		alignSz	 = clusterSz - itemSzNotAligned;
		if (*bufsz < itemSz + alignSz) {
			DWN_ERR("item buf sz not enough for align\n");
			return -__LINE__;
		}
		DWN_MSG("align buf 0x%p for sdc read...\t", buf);
		buf += alignSz;
	}

    int rc = image_item_read(hImg, hImgItem, buf, (unsigned)itemSz);
    if (rc) {
        DWN_ERR("Fail read item data, rc %d\n", rc);
        image_item_close(hImgItem); return __LINE__;
    }
	if (alignSz) memmove(buf - alignSz, buf, itemSz);

    image_item_close(hImgItem);
    *bufsz = itemSz;
    return 0;
}

//get item num which has same main_type
int get_subtype_nr(HIMAGE hImg, const char* main_type)
{
    int i = 0;
    int ret = 0;
    int itemNum = 0;
    const int totalItemNum = get_total_itemnr(hImg);

    for (i = 0; i < totalItemNum; i++)
    {
        const char* mainType = NULL;
        const char* sub_type  = NULL;

        ret = get_item_name(hImg, i, &mainType, &sub_type);
        if (ret) {
            DWN_ERR("Exception:fail to get item name!\n");
            return -__LINE__;
        }

        if (strcmp(main_type, mainType)) continue;
        itemNum += 1;
    }

    return itemNum;
}

int get_subtype_nm_by_index(HIMAGE hImg, const char* main_type, const char** sub_type, const int itemIndex)
{
    int i = 0;
    int ret = 0;
    int itemNum = 0;
    const int totalItemNum = get_total_itemnr(hImg);
    const int nSubType     = get_subtype_nr(hImg, main_type);

    if (nSubType < 1) {
        DWN_ERR("err main type[%s]\n", main_type);
        return -__LINE__;
    }
    if (nSubType <= itemIndex) {
        DWN_ERR("item index %d > max %d for main[%s]\n", itemIndex, nSubType, main_type);
        return -__LINE__;
    }

    for (i = 0; i < totalItemNum; i++)
    {
        const char* mainType = NULL;

        ret = get_item_name(hImg, i, &mainType, sub_type);
        if (ret) {
            DWN_ERR("Exception:fail to get item name!\n");
            return __LINE__;
        }

        if (strcmp(mainType, main_type)) continue;
        if (itemIndex == itemNum) return OPT_DOWN_OK;
        itemNum += 1;
    }

    return OPT_DOWN_FAIL;
}

int optimus_img_secureboot_signed(HIMAGE hImg)
{
	const int n_usb_bootloader = get_subtype_nr(hImg, "USB");

	DWN_MSG("USB item num %d\n", n_usb_bootloader);
	return n_usb_bootloader == 4;
}

#ifndef CONFIG_SYS_SOC
int optimus_img_chk_soctype(HIMAGE hImg)
{
	DWN_WRN("cfg SYS_SOC undef\n");
	return 0;
}
#else
int optimus_img_chk_soctype(HIMAGE hImg)
{
	char *buf = NULL;
	int ret = 0;
	char *pbuf = NULL;
	const char *socstr = "soctype:";
	const char *socstr1 = "\"soctype\":";
	char *cfgn = NULL;
	char *tmp1, *tmp2 = NULL;
	const char *SOC_NAME = CONFIG_SYS_SOC;
	const int _BUFLEN = 4096;
	const int BUFLEN = _BUFLEN + image_get_cluster_size(hImg);
	int bufsz = BUFLEN - 1;
	int json_fmt = 0;

	buf = (char *)malloc(BUFLEN);
	if (!buf) {
		DWN_ERR("Fail in alloc buf sz 0x%x\n", BUFLEN);
		return __LINE__;
	}
	ret = optimus_img_item2buf(hImg, "conf", "platform", buf, &bufsz);
	if (ret) {
		DWN_ERR("Pkg no platform.conf\n");
		free(buf);
		return __LINE__;
	}
	DWN_MSG("conf sz %d\n", bufsz);
	buf[bufsz] = '\0';
	for (tmp1 = buf, tmp2 = buf + _BUFLEN; *tmp1; ++tmp1, ++tmp2) {
		while (*tmp1 == ' ')
			++tmp1;
		*tmp2 = *tmp1;
	}
	pbuf = buf + _BUFLEN;
	DWN_DBG("%s\n", pbuf);
	pbuf = strstr(pbuf, socstr);
	if (!pbuf) {
		pbuf = buf + _BUFLEN;
		pbuf = strstr(pbuf, socstr1);
		json_fmt = 1;
	}
	if (!pbuf) {
		DWN_ERR("img not config soctype\n");
		free(buf);
		return __LINE__;
	}
	DWN_MSG("%s json fmt\n", json_fmt ? "is" : "not");
	pbuf += strlen(json_fmt ? socstr1 : socstr);
	cfgn  = pbuf;
	if (!strsep(&pbuf, "\n")) {
		DWN_ERR("err soctype cfg\n");
		free(buf);
		return -__LINE__;
	}
	DWN_MSG("%s%s\n", socstr, cfgn);
	if (json_fmt)
		*(pbuf - 3) = '\0';
	ret = !json_fmt;
	for (pbuf = cfgn; ret && strsep(&pbuf, ":"); cfgn = pbuf) {
		ret = strcasecmp(SOC_NAME, cfgn);
		DWN_MSG("soc[%s] %s match IMG cfg[%s]\n", SOC_NAME,
			ret ? "NOT" : "DO", cfgn);
	}

	if (json_fmt) {
		ret = 1;
		SOC_NAME = "\"" CONFIG_SYS_SOC "\"";
		for (pbuf = ++cfgn; ret && strsep(&pbuf, ","); cfgn = pbuf) {
			ret = strcasecmp(SOC_NAME, cfgn);
			DWN_MSG("soc %s %s match IMG cfg %s\n", SOC_NAME,
				ret ? "NOT" : "DO", cfgn);
		}
	}

	free(buf);
	return ret;
}
#endif// #ifndef CONFIG_SYS_SOC

#define MYDBG 0
#if MYDBG
static int test_item(HIMAGE hImg, const char* main_type, const char* sub_type, char* pBuf, const int sz)
{
    HIMAGEITEM hItem = NULL;
    int ret = 0;

    hItem = image_item_open(hImg, main_type, sub_type);
    if (!hItem) {
        DWN_ERR("fail to open %s, %s\n", main_type, sub_type);
        return __LINE__;
    }

    ret = image_item_read(hImg, hItem, pBuf, sz);
    if (ret) {
        DWN_ERR("fail to read\n");
        goto _err;
    }
    if (64 >= sz)DWN_MSG("%s\n", pBuf) ;

_err:
    image_item_close(hItem);
    return ret;
}

static int test_pack(const char* interface, const char* device, const char* part, const char* imgPath)
{
    const int ImagBufLen = OPTIMUS_DOWNLOAD_SLOT_SZ;
    char* pBuf = (char*)OPTIMUS_DOWNLOAD_TRANSFER_BUF_ADDR + ImagBufLen;
    int ret = 0;
    int i = 0;
    HIMAGEITEM hItem = NULL;

    if (!strcmp("store", interface))
    {
            ret = run_command("store init 1", 0);
            if (ret) {
                    DWN_ERR("Fail in init mmc, Does sdcard not plugged in?\n");
                    return __LINE__;
            }
    }
    else
    {
            s64 fileSz = 0;

            ret = run_command("mmcinfo", 0);
            if (ret) {
                    DWN_ERR("Fail in init mmc, Does sdcard not plugged in?\n");
                    return __LINE__;
            }

            fileSz = do_fat_get_fileSz(imgPath);
            if (!fileSz) {
                    DWN_ERR("file %s not exist\n", imgPath);
                    return __LINE__;
            }
    }

    HIMAGE hImg = image_open(interface, device, part, imgPath);
    if (!hImg) {
        DWN_ERR("Fail to open image\n");
        return __LINE__;
    }

    const int itemNr = get_total_itemnr(hImg);
    for (i = 0; i < itemNr ; i++)
    {
        __u64 itemSz = 0;
        int fileType = 0;

        hItem = get_item(hImg, i);
        if (!hItem) {
            DWN_ERR("Fail to open item at id %d\n", i);
            break;
        }

        itemSz = image_item_get_size(hItem);
        DWN_MSG("Item Sz is 0x%llx\n", itemSz);

        unsigned wantSz = ImagBufLen > itemSz ? (unsigned)itemSz : ImagBufLen;
        unsigned itemSizeNotAligned = 0;
        char* readBuf = pBuf;
        unsigned readSz = wantSz;

        itemSizeNotAligned = image_item_get_first_cluster_size(hImg, hItem);
        if (itemSizeNotAligned)
        {
                ret = image_item_read(hImg, hItem, readBuf, itemSizeNotAligned);
                readSz = (wantSz > itemSizeNotAligned) ? (wantSz - itemSizeNotAligned) : 0;
        }

        if (readSz)
        {
                ret = image_item_read(hImg, hItem, readBuf + itemSizeNotAligned, readSz);
                if (ret) {
                        DWN_ERR("fail to read item data\n");
                        break;
                }
        }

        fileType = image_item_get_type(hItem);
        if (IMAGE_ITEM_TYPE_SPARSE == fileType)
        {
                DWN_MSG("sparse packet\n");
                ret = optimus_simg_probe((const u8*)pBuf, wantSz);
                if (!ret) {
                        DWN_ERR("item data error, should sparse, but no\n");
                        break;
                }
        }
    }

#if 1
    test_item(hImg, "PARTITION", "logo", pBuf, ImagBufLen);
    test_item(hImg, "VERIFY", "logo", pBuf, 50);
#endif

    image_close(hImg);
    return 0;
}

static int do_unpack(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int rcode = 0;
    const char* imgPath = "a";

#if 1
    if (2 > argc) imgPath = "dt.img";
#else
    if (2 > argc) {
        cmd_usage(cmdtp);
        return -1;
    }
#endif//#if MYDBG
    DWN_MSG("argc %d, %s, %s\n", argc, argv[0], argv[1]);

    rcode = test_pack("mmc", "0", "aml_sysrecovery", imgPath);

    DWN_MSG("rcode %d\n", rcode);
    return rcode;
}

U_BOOT_CMD(
   unpack,      //command name
   5,               //maxargs
   1,               //repeatable
   do_unpack,   //command function
   "unpack the image in sdmmc ",           //description
   "Usage: unpack imagPath\n"   //usage
);
#endif//#if MYDBG

