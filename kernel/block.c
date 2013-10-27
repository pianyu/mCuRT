#include "kernel/block.h"

#if 0
#define BLOCK_DEVICE_MAX_NUMBER			(32)

struct block_device {
	/* set by block driver */
	unsigned int sector_size;
	unsigned int total_sector;
	unsigned char *name;

	int (*read_sector)(struct block_device *dev, unsigned char *buf, unsigned int sector_off, unsigned int sector_count);
	int (*write_sector)(struct block_device *dev, unsigned char *buf, unsigned int sector_off, unsigned int sector_count);

	/* only used by block layer */
	unsigned int id;
};
#endif
struct block_device *block_device_list[BLOCK_DEVICE_MAX_NUMBER];

int block_subsystem_init(void)
{
	return 0;
}

int block_device_register(struct block_device *dev)
{
	unsigned id = 0;

	for (; id < BLOCK_DEVICE_MAX_NUMBER ; ++id) {
		if (block_device_list[id] == 0) {
			break;
		}
	}

	if (id == BLOCK_DEVICE_MAX_NUMBER) {
		return -1;
	}

	dev->id = id;

	return 0;
}

int block_read(struct block_device *dev, unsigned char *buf, unsigned int sector_off, unsigned int sector_count)
{
	return dev->read_sector(dev, buf, sector_off, sector_count);
}

int block_write(struct block_device *dev, unsigned char *buf, unsigned int sector_off, unsigned int sector_count)
{
	return dev->write_sector(dev, buf, sector_off, sector_count);
}
