#include "super_block_mem.h"
#include "const_variable.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
SuperBlockMem::SuperBlockMem() {
    sb_disk.i_map_blocks = 1;
    sb_disk.d_map_blocks = 5;
    sb_disk.i_blocks = 1 * BLK_SIZE;
    sb_disk.d_blocks = 5 * BLK_SIZE;
    sb_disk.sb_magic = magic;
}

void SuperBlockMem::saveSuperBlockToDisk(int fd) 
{
    char buff[BLK_SIZE];
    memset(buff, 0 , sizeof(buff));
    memcpy(buff, &sb_disk, sizeof(sb_disk));
    int ret = ::lseek(fd, 0 , SEEK_SET);
    ret = ::write(fd, buff, BLK_SIZE);
    return;
}

void SuperBlockMem::loadSuperBlockFromDisk(int fd) {
    char buff[BLK_SIZE];
    ::lseek(fd, 0 , SEEK_SET);
    ::read(fd, buff, BLK_SIZE);
    memcpy(&sb_disk, buff, sizeof(sb_disk));

    return;
}