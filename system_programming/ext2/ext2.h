/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Ext2                    */
/*   Date:      24/04/23                */
/*                                      */
/****************************************/
#include <stdlib.h>  /*printf*/
#include <assert.h>  /*assert*/

#define	EXT2_NDIR_BLOCKS		(12)
#define	EXT2_IND_BLOCK			EXT2_NDIR_BLOCKS
#define	EXT2_DIND_BLOCK			(EXT2_IND_BLOCK + 1)
#define	EXT2_TIND_BLOCK			(EXT2_DIND_BLOCK + 1)
#define	EXT2_N_BLOCKS			(EXT2_TIND_BLOCK + 1)
#define EXT2_NAME_LEN           (120)

struct ext2_super_block 
{
    unsigned int	s_inodes_count;             /* Inodes count */
    unsigned int	s_blocks_count;             /* Blocks count */
    unsigned int	s_r_blocks_count;           /* Reserved blocks count */
    unsigned int	s_free_blocks_count;    	/* Free blocks count */
    unsigned int	s_free_inodes_count;	    /* Free inodes count */
    unsigned int	s_first_data_block;         /* First Data Block */
    unsigned int	s_log_block_size;           /* Block size */
    int	            s_log_frag_size;            /* Fragment size */
    unsigned int	s_blocks_per_group;         /* # Blocks per group */
    unsigned int	s_frags_per_group;          /* # Fragments per group */
    unsigned int	s_inodes_per_group;         /* # Inodes per group */
    unsigned int	s_mtime;                    /* Mount time */
    unsigned int	s_wtime;                    /* Write time */
    unsigned short	s_mnt_count;		        /* Mount count */
    short	        s_max_mnt_count;	        /* Maximal mount count */
    unsigned short	s_magic;                    /* Magic signature */
    unsigned short	s_state;		            /* File system state */
    unsigned short	s_errors;                   /* Behaviour when detecting errors */
    unsigned short	s_minor_rev_level;          /* minor revision level */
    unsigned int	s_lastcheck;                /* time of last check */
    unsigned int	s_checkinterval;            /* max. time between checks */
    unsigned int	s_creator_os;               /* OS */
    unsigned int	s_rev_level;                /* Revision level */
    unsigned short	s_def_resuid;               /* Default uid for reserved blocks */
    unsigned short	s_def_resgid;               /* Default gid for reserved blocks */
    unsigned int	s_first_ino;                /* First non-reserved inode */
    unsigned short  s_inode_size;               /* size of inode structure */
    unsigned short	s_block_group_nr;           /* block group # of this superblock */
    unsigned int	s_feature_compat;           /* compatible feature set */
    unsigned int	s_feature_incompat;     	/* incompatible feature set */
    unsigned int	s_feature_ro_compat; 	    /* readonly-compatible feature set*/
    unsigned char	s_uuid[16];                 /* 128-bit uuid for volume */
    char	        s_volume_name[16];  	    /* volume name */
    char	        s_last_mounted[64];     	/* directory where last mounted */
    unsigned int	s_algorithm_usage_bitmap;   /* For compression */
    unsigned char	s_prealloc_blocks;	        /* Nr of blocks to try to preallocate*/
    unsigned char	s_prealloc_dir_blocks;      /* Nr to preallocate for dirs */
    unsigned short	s_padding1;
    unsigned int	s_reserved[204];	        /* Padding to the end of the block */
};
	
typedef struct ext2_group_desc
{
	unsigned int	bg_block_bitmap;        /* Blocks bitmap block */
	unsigned int	bg_inode_bitmap;        /* Inodes bitmap block */
	unsigned int	bg_inode_table;         /* Inodes table block */
	unsigned short	bg_free_blocks_count;   /* Free blocks count */
	unsigned short	bg_free_inodes_count;   /* Free inodes count */
	unsigned short	bg_used_dirs_count;     /* Directories count */
	unsigned short	bg_pad;
	unsigned int	bg_reserved[3];
} group_desc_t;

typedef struct ext2_inode 
{
   unsigned short int	i_mode;		/* File mode */
   unsigned short int	i_uid;		/* Low 16 bits of Owner Uid */
   unsigned int	i_size;		/* Size in bytes */
   unsigned int	i_atime;	/* Access time */
   unsigned int	i_ctime;	/* Creation time */
   unsigned int	i_mtime;	/* Modification time */
   unsigned int	i_dtime;	/* Deletion Time */
   unsigned short int	i_gid;		/* Low 16 bits of Group Id */
   unsigned short int	i_links_count;	/* Links count */
   unsigned int	i_blocks;	/* Blocks count */
   unsigned int	i_flags;	/* File flags */
   union {
   struct {
   unsigned int  l_i_reserved1;
   } linux1;
   struct {
   unsigned int  h_i_translator;
   } hurd1;
   struct {
   unsigned int  m_i_reserved1;
   } masix1;
   } osd1;				/* OS dependent 1 */
   unsigned int	i_block[EXT2_N_BLOCKS];/* Pointers to blocks */
   unsigned int	i_generation;	/* File version (for NFS) */
   unsigned int	i_file_acl;	/* File ACL */
   unsigned int	i_dir_acl;	/* Directory ACL */
   unsigned int	i_faddr;	/* Fragment address */
   union {
   struct {
   unsigned char	l_i_frag;	/* Fragment number */
   unsigned char	l_i_fsize;	/* Fragment size */
   unsigned short int	i_pad1;
   unsigned short int	l_i_uid_high;	/* these 2 fields    */
   unsigned short int	l_i_gid_high;	/* were reserved2[0] */
   unsigned int	l_i_reserved2;
   } linux2;
   struct {
   unsigned char	h_i_frag;	/* Fragment number */
   unsigned char	h_i_fsize;	/* Fragment size */
   unsigned short int	h_i_mode_high;
   unsigned short int	h_i_uid_high;
   unsigned short int	h_i_gid_high;
   unsigned int	h_i_author;
   } hurd2;
   struct {
   unsigned char	m_i_frag;	/* Fragment number */
   unsigned char	m_i_fsize;	/* Fragment size */
   unsigned short int	m_pad1;
   unsigned int	m_i_reserved2[2];
   } masix2;
   } osd2;				/* OS dependent 2 */
} ext2_inode_t;

struct ext2_dir_entry_2
{
	unsigned int	inode;			/* Inode number */
	unsigned short int	rec_len;		/* Directory entry length */
	unsigned char	name_len;		/* Name length */
	unsigned char	file_type;
	char	name[EXT2_NAME_LEN];	/* File name */
};

/*----------------------------------------------------------------------------*/
int ParsingFileSystem(const char *device_path, const char *file_path);

