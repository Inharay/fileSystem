#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "inode_mem.h"
#include "const_variable.h"
Inode::Inode() {
    i_disk.i_nlink = 2;
    i_disk.i_size = 0;
}

int Inode::saveInodeToDisk(int fd, int block_index) {
    char buff[BLK_SIZE];
    ::memset(buff, 0 , sizeof(buff));
    ::memcpy(buff, &i_disk, sizeof(i_disk));
    int ret = ::lseek(fd, block_index *  BLK_SIZE, SEEK_SET);
    ret = ::write(fd, buff, BLK_SIZE);
    return 0;
}

int Inode::loadInodeFromDisk(int fd, int block_index) {
    char buff[BLK_SIZE];
    ::lseek(fd, block_index *  BLK_SIZE, SEEK_SET);
    ::read(fd, buff, BLK_SIZE);
    ::memcpy(&i_disk, buff, sizeof(i_disk));
    return 0;
}