#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "entry.h"
#include "const_variable.h"
Entry::Entry(char *name, int inode_index) {
    strcpy(e_disk.name, name);
    e_disk.inode_index = inode_index;
}

int Entry::saveEntryToDisk(int fd, int block_index, int entry_index) {
    char buff[BLK_SIZE];
    ::memset(buff, 0 , sizeof(buff));
    ::lseek(fd, block_index *  BLK_SIZE, SEEK_SET);
    ::read(fd, buff, BLK_SIZE);
    EntryDisk *e_diskArray = (EntryDisk *)buff;
    e_diskArray[entry_index] = e_disk;

    ::lseek(fd, block_index *  BLK_SIZE, SEEK_SET);
    ::write(fd, buff, BLK_SIZE);
    return 0;
}

int Entry::loadEntryFromDisk(int fd, int block_index, int entry_index) {
    char buff[BLK_SIZE];
    ::lseek(fd, block_index *  BLK_SIZE, SEEK_SET);
    ::read(fd, buff, BLK_SIZE);
    EntryDisk *e_diskArray = (EntryDisk *)buff;
    e_disk = e_diskArray[entry_index];
    return 0;
}
