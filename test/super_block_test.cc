#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <fcntl.h>

#include "src/super_block_mem.h"
#include "src/const_variable.h"

using namespace std;
TEST(testAdd, test0)
{
  int fd = open("test", ios::out | ios::in);
  SuperBlockMem sb;
  sb.saveSuperBlockToDisk(fd);
  sb.sb_disk.sb_magic = 2;
  sb.loadSuperBlockFromDisk(fd);
  EXPECT_EQ(sb.sb_disk.sb_magic, magic);
  close(fd);
}