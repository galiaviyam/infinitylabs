/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Ext2                    */
/*   Date:      24/04/23                */
/*                                      */
/****************************************/

#include <stdio.h>

#include "ext2.h"

int main(void)
{
	ParsingFileSystem("/dev/ram0", NULL);
/*	ReadGroupDescriptor("/dev/ram0", NULL);*/
	return 0;
}
/*
sudo modprobe brd
sudo mkfs.ext2 /dev/ram0
sudo mkdir /mnt/ramdisk
sudo mount /dev/ram0 /mnt/ramdisk/ -o sync

*/
