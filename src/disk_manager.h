#pragma once
#include <string.h>
#include <stdint.h>
#include "super_block_mem.h"
class DiskManager
{
private:
    void InitMapBlock(SuperBlockDisk &s_block);


    void SetMapStatus(int startBlkIdx, int mapIdx, int8_t status);

public:
    char* disk_name;
    int disk_fd;
    int GetBlkIdxByDataIdx(SuperBlockDisk &s_block, int data_blk_index);
    int GetBlkIdxByInodeIdx(SuperBlockDisk &s_block, int inode_blk_index);

    DiskManager(char* name):disk_name(name){};
    ~DiskManager();
    int FormatDisk();

};


