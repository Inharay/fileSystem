#include "disk_manager.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h> 
#include "log.h"
#include "super_block_mem.h"
#include "inode_mem.h"
int DiskManager::FormatDisk() {
    if ((disk_fd = open(disk_name, O_RDWR)) < 0) {
        SYS_ERR("open error %s", disk_name);
    }
    struct stat stat;
    if (fstat(disk_fd, &stat) < 0) {
        SYS_ERR("get stat error");
    }

    if ((stat.st_size >> 20) < 10) {
        SYS_ERR("disk size small than 10MB");
    }

    SuperBlockMem sb;
    sb.saveSuperBlockToDisk(disk_fd);

    Inode root_inode;
    root_inode.saveInodeToDisk(disk_fd, 1);
}

DiskManager::~DiskManager()
{
    close(disk_fd);
}