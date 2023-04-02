#include <string>
#include <vector>
#include "fuse.h"
#include "inode_mem.h"
#include "const_variable.h"
#include "disk_manager.h"
#include "super_block_mem.h"
#include "log.h"
extern "C" {

DiskManager g_diskManger;
SuperBlockMem g_superBlock;

struct fuse_operations ufs_oper = {
	.create		= fs_creat,
	.mkdir		= fs_mkdir,
	.opendir	= fs_opendir,
	.read		= fs_read,
	.readdir	= fs_readdir,
	.write		= fs_write,
};

int fs_mkdir(const char *path, mode_t mode)
{
	if (path == nullptr || path[0] == 0) {
		return -1;
	}
	char pathcpy[UFS_PATH_LEN];
	strcpy(pathcpy, path);
	Inode parent_inode;
	int32_t ret = getInodeByPath(dirname(pathcpy), parent_inode);
	if(ret != 0) {
		LOG_PRINT(ERROR, "find parent inode error %d, %s", ret, path);
		return ret;
	}

	strcpy(pathcpy, path);
	ret = creatDir(parent_inode, basename(pathcpy), mode);
	if(ret != 0) {
		LOG_PRINT(ERROR, "create dir error %d, %s", ret, path);
		return ret;
	}
	return 0;
}

int32_t getInodeByPath(char *path, Inode &inode) 
{
	std::string p = path;
	std::vector<std::string> dirList;
	Inode rootInode;
	rootInode.loadInodeFromDisk(g_diskManger.disk_fd, g_diskManger.GetBlkIdxByInodeIdx(g_superBlock, 1))
	inode = rootInode;
	stringSplit(p, '/', dirList);
	for (string dir:dirList) {
		if (dir.size() == 0) continue;

		int i_num = g_diskManger.findEntryInodeNum(g_superBlock, inode, dir);
		if (i_num == -1) {
			return - 1;
		}
		inode.loadInodeFromDisk(g_diskManger.disk_fd, g_diskManger.GetBlkIdxByInodeIdx(g_superBlock, i_num))
		inode.i_num = i_num;
	}
	return 0;
}

creatDir(parent_inode, basename(pathcpy), mode)
{
	
}

int fs_readdir (const char *, void *, fuse_fill_dir_t, off_t,
			struct fuse_file_info *, enum fuse_readdir_flags)
{


}

void init(char *diskName) {
	g_diskManger = new DiskManager(diskName);
	g_superBlock = new SuperBlockMem();
	g_superBlock.loadSuperBlockFromDisk(g_diskManger.disk_fd);
}

}

int main(int argc, char *argv[])
{
	init(argv[argc - 1]);
	return(fuse_main(argc - 1, argv, &ufs_oper, NULL));
}


