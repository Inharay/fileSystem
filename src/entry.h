#pragma once
#include<string>
struct EntryDisk
{
    char name[20];
    int inode_index;
};

class Entry {
    public:
        EntryDisk e_disk;
        Entry(char *name, int inode_index);
        Entry() {};
        int saveEntryToDisk(int fd, int block_index, int entry_index);
        int loadEntryFromDisk(int fd, int block_index, int entry_index);
        static int isBlkHasEntry(int fd, int blkIndex, std::string entryName);

};