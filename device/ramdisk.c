#include "kernel/block.h"
#include "lib/stdio.h"

#define RAMDISK_SECTOR_SIZE			(1)
#define RAMDISK_MAX_SECTOR			(8192)

int ramdisk_read_sector(struct block_device *dev, unsigned char *buf, unsigned int sector_off, unsigned int sector_count)
{
	unsigned addr = sector_off*RAMDISK_SECTOR_SIZE;
	unsigned bytes = sector_count*RAMDISK_SECTOR_SIZE;
	unsigned char *content = dev->priv;

	if (addr + bytes >= RAMDISK_MAX_SECTOR) {
		return -1;
	}

	memcpy(buf, &content[addr], bytes);

	return 0;
}

int ramdisk_write_sector(struct block_device *dev, unsigned char *buf, unsigned int sector_off, unsigned int sector_count)
{
	unsigned addr = sector_off*RAMDISK_SECTOR_SIZE;
	unsigned bytes = sector_count*RAMDISK_SECTOR_SIZE;
	unsigned char *content = dev->priv;

	if (addr + bytes >= RAMDISK_MAX_SECTOR) {
		return -1;
	}

	memcpy(&content[addr], buf, bytes);

	return 0;
}

static unsigned char ramdisk_content[RAMDISK_MAX_SECTOR*RAMDISK_SECTOR_SIZE];

struct block_device ramdisk_dev = {
	.sector_size = RAMDISK_SECTOR_SIZE,
	.total_sector = RAMDISK_MAX_SECTOR,
	.name = "ramdisk",

	.read_sector = ramdisk_read_sector,
	.write_sector = ramdisk_write_sector,
	.priv = ramdisk_content
};

int ramdisk_init(void)
{
	int i = 0;

	for (; i < RAMDISK_MAX_SECTOR*RAMDISK_SECTOR_SIZE ; ++i) {
		ramdisk_content[i] = i;
	}

	if (block_device_register(&ramdisk_dev) != 0) {
		return -1;
	}

	return 0;
}

