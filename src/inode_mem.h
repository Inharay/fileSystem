#pragma once
#include "inode_disk.h"
class Inode {
    public:
        InodeDisk i_disk;
        Inode();
        int loadInodeFromDisk(int fd, int block_index);
        int saveInodeToDisk(int fd, int block_index);

};