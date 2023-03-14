

#include "super_block_disk.h"
class SuperBlockMem {
    public:
        SuperBlockDisk sb_disk;
        SuperBlockMem();
        void loadSuperBlockFromDisk(int fd);
        void saveSuperBlockToDisk(int fd);

};