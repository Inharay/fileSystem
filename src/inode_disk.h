
#include <sys/types.h>
#include <unistd.h>
struct InodeDisk
{
    /* # of links into this inode */
	nlink_t	i_nlink;
	/* file type and permission */
	mode_t	i_mode;
	/* the size of file */
	unsigned int i_size;
	/* # of disk blocks allocated */
	unsigned int i_blocks;
	/* the last time this file modifed */
	time_t	i_mtime;
	/* the owner of this file */
	uid_t	i_uid;
	/* the owner'group of this file */
	gid_t	i_gid;

	unsigned int i_data_map[8];
};
