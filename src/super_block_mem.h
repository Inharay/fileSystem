#pragma once

#include "super_block_disk.h"
class SuperBlockMem {
    public:
        SuperBlockDisk sb_disk;
        char *i_map;
        char *d_map;
        SuperBlockMem();
        void loadSuperBlockFromDisk(int fd);
        void saveSuperBlockToDisk(int fd);

};