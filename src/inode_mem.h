#pragma once
#include "inode_disk.h"
class Inode {
    public:
        InodeDisk i_disk;
        uint32_t i_num;
        Inode();
        int loadInodeFromDisk(int fd, int block_index);
        int saveInodeToDisk(int fd, int block_index);


};