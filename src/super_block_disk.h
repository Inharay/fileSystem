struct SuperBlockDisk
{
    int sb_magic;     // super block 魔数
    int i_map_blocks; // inode位图所需要的数据块个数
    int d_map_blocks; // data位图所需要的数据块个数
    int i_blocks;     // 元数据inode 所需要的数据块个数
    int d_blocks;     // 数据所需要的元数据个数
};
