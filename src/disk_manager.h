#pragma once
#include <string.h>
class DiskManager
{
private:

public:
    char* disk_name;
    int disk_fd;
    DiskManager(char* name):disk_name(name){};
    ~DiskManager();
    int FormatDisk();
};


