#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include "disk_manager.h"
int main(int argc, char *argv[])
{
    if (argc < 1) throw std::exception();
    std::cout<<"disk name "<<argv[1]<<std::endl;
    DiskManager dm{argv[0]};
    dm.FormatDisk();
    SuperBlockMem sb;
    sb.sb_disk.sb_magic = 0;
    sb.loadSuperBlockFromDisk(dm.disk_fd);
    EXPECT_EQ(sb.sb_disk.sb_magic, magic);
    result = exec("rm -rf disk");
}