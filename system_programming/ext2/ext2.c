/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Ext2                    */
/*   Date:      24/04/23                */
/*                                      */
/****************************************/

#include <stdio.h>
#include <stdlib.h>  /*printf*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/types.h>
#include <string.h>

#include "ext2.h" /*header file*/

#define FILE_PATH "/mnt/ram"
#define DEVICE "/dev/ram0"
#define BASE_OFFSET 1024                   /* locates beginning of the super block (first group) */
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1)*block_size)

static unsigned int block_size;
static int ReadSuperBlock(const char *device_path, const char *file_path);
static int ReadGroupDescriptor(const char *device_path, const char *file_path);
static void read_inode(int fd, int inode_no, const group_desc_t *group, ext2_inode_t *inode);
static void read_dir(int fd, const ext2_inode_t *inode, const struct ext2_group_desc *group);

/*--------------------------- ParsingFileSystem --------------------------*/
int ParsingFileSystem(const char *device_path, const char *file_path)
{
	ReadSuperBlock(device_path, NULL)   ;
    ReadGroupDescriptor(device_path, NULL);
    
	(void)file_path;
    
    return 0;
}
/*---------------------------- ReadSuperBlock ------------------------------*/

static int ReadSuperBlock(const char *device_path, const char *file_path)
{
    int fd = 0;
    struct ext2_super_block super_block = {0};
	
    if ((fd = open(device_path, O_RDONLY)) < 0) 
	{
		printf("open failed\n");
 		exit(1);  
	}

    lseek(fd, sizeof(super_block), SEEK_SET);
    read(fd, &super_block, sizeof(super_block));

    block_size = 1024 << super_block.s_log_block_size;

	printf("Reading superblock from device "DEVICE" :\n"
	       "Inodes count            : %u\n"
	       "Blocks count            : %u\n"
	       "Reserved blocks count   : %u\n"
	       "Free blocks count       : %u\n"
	       "Free inodes count       : %u\n"
	       "First data block        : %u\n"
	       "Block size              : %u\n"
	       "Blocks per group        : %u\n"
	       "Inodes per group        : %u\n"
	       "Creator OS              : %u\n"
	       "First non-reserved inode: %u\n"
	       "Size of inode structure : %hu\n"
	       ,
	       super_block.s_inodes_count,  
	       super_block.s_blocks_count,
	       super_block.s_r_blocks_count,     
	       super_block.s_free_blocks_count,
	       super_block.s_free_inodes_count,
	       super_block.s_first_data_block,
	       block_size,
	       super_block.s_blocks_per_group,
	       super_block.s_inodes_per_group,
	       super_block.s_creator_os,
	       super_block.s_first_ino,          
	       super_block.s_inode_size);
    
    close(fd);
	(void)file_path;
    
    return 0;
}

/*------------------------- ReadGroupDescriptor ----------------------------*/
static int ReadGroupDescriptor(const char *device_path, const char *file_path)
{
	struct ext2_group_desc group = {0};
	int fd = 0;
    ext2_inode_t inode = {0};

	if ((fd = open(device_path, O_RDONLY)) < 0) 
	{
		printf("open failed\n");
 		exit(1);  
	}
	
	lseek(fd, block_size, SEEK_SET);
	read(fd, &group, sizeof(group));

	printf("\n\nReading first group-descriptor from device "DEVICE":\n"
	       "Blocks bitmap block: %u\n"
	       "Inodes bitmap block: %u\n"
	       "Inodes table block : %u\n"
	       "Free blocks count  : %u\n"
	       "Free inodes count  : %u\n"
	       "Directories count  : %u\n"
	       ,
	       group.bg_block_bitmap,
	       group.bg_inode_bitmap,
	       group.bg_inode_table,
	       group.bg_free_blocks_count,
	       group.bg_free_inodes_count,
	       group.bg_used_dirs_count);

    read_inode(fd, 3, &group, &inode);
    read_dir(fd, &inode, &group);
  
	 close(fd);
	 (void)file_path;
	 return 0;
}

static void read_inode(int fd, int inode_no, const group_desc_t *group, ext2_inode_t *inode)
{
	lseek(fd, BLOCK_OFFSET(group->bg_inode_table)+(inode_no-1)*sizeof(ext2_inode_t), 
	      SEEK_SET);
	read(fd, inode, sizeof(ext2_inode_t));
} 

static void read_dir(int fd, const ext2_inode_t *inode, const struct ext2_group_desc *group)
{
    struct ext2_dir_entry_2 *entry;
    unsigned int size;
    unsigned char block[4096] = {0};

    lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET) ;
    read(fd, block, block_size);
    size = 0;                                            
    entry = (struct ext2_dir_entry_2 *) block;           
    while(size < inode->i_size /*&& (size_t)entry < (&block + 4096)*/ && entry->rec_len > 0) 
    {
        char file_name[EXT2_NAME_LEN+1];
        memcpy(file_name, entry->name, entry->name_len);
        file_name[entry->name_len] = 0;              
        printf("%10u %s\n", entry->inode, file_name);
        entry = entry + entry->rec_len;      
        size += entry->rec_len;
    }
}
