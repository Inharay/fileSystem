#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <fcntl.h>

#include "src/super_block_mem.h"
#include "src/inode_mem.h"
#include "src/const_variable.h"

using namespace std;
TEST(testSuperBlock, load_and_save)
{
  int fd = open("test", ios::out | ios::in);
  SuperBlockMem sb;
  sb.saveSuperBlockToDisk(fd);
  sb.sb_disk.sb_magic = 2;
  sb.loadSuperBlockFromDisk(fd);
  EXPECT_EQ(sb.sb_disk.sb_magic, magic);
  close(fd);
}

TEST(testInode, load_and_save)
{
  int fd = open("test", ios::out | ios::in);
  Inode inode;
  inode.saveInodeToDisk(fd, 1);
  int size = inode.i_disk.i_size;

  inode.i_disk.i_size = 2;
  inode.loadInodeFromDisk(fd, 1);
  EXPECT_EQ(inode.i_disk.i_size, size);
  close(fd);
}