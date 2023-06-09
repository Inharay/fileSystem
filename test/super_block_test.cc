#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "src/super_block_mem.h"
#include "src/inode_mem.h"
#include "src/const_variable.h"
#include "src/disk_manager.h"
#include "src/entry.h"


using namespace std;


string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
};

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

TEST(testDiskManager, diskformat)
{
  string result = exec("dd if=/dev/zero of=disk bs=1M count=30");
  DiskManager dm{"disk"};
  dm.FormatDisk();
  SuperBlockMem sb;
  sb.sb_disk.sb_magic = 0;
  sb.loadSuperBlockFromDisk(dm.disk_fd);
  EXPECT_EQ(sb.sb_disk.sb_magic, magic);

  Inode inode;
  inode.loadInodeFromDisk(dm.disk_fd, sb.sb_disk.d_map_blocks + sb.sb_disk.i_map_blocks + 1);
  EXPECT_EQ(inode.i_disk.i_data_map[0], 1);

  Entry entry;
  entry.loadEntryFromDisk(dm.disk_fd, dm.GetBlkIdxByDataIdx(sb.sb_disk, 1), 0);
  EXPECT_STREQ(entry.e_disk.name, ".");
  EXPECT_EQ(entry.e_disk.inode_index, 1);

  entry.loadEntryFromDisk(dm.disk_fd, dm.GetBlkIdxByDataIdx(sb.sb_disk, 1), 1);
  EXPECT_STREQ(entry.e_disk.name, "..");
  EXPECT_EQ(entry.e_disk.inode_index, 1);

  result = exec("rm -rf disk");
}