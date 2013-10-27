#ifndef __BLOCK_H__
#define __BLOCK_H__

#define BLOCK_DEVICE_MAX_NUMBER			(32)

struct block_device {
	/* set by block driver */
	unsigned int sector_size;
	unsigned int total_sector;
	char *name;

	int (*read_sector)(struct block_device *dev, unsigned char *buf, unsigned int sector_off, unsigned int sector_count);
	int (*write_sector)(struct block_device *dev, unsigned char *buf, unsigned int sector_off, unsigned int sector_count);

	void *priv;

	/* only used by block layer */
	unsigned int id;
};

extern struct block_device *block_device_list[BLOCK_DEVICE_MAX_NUMBER];

int block_subsystem_init(void);
int block_device_register(struct block_device *dev);
int block_read(struct block_device *dev, unsigned char *buf, unsigned int sector_off, unsigned int sector_count);
int block_write(struct block_device *dev, unsigned char *buf, unsigned int sector_off, unsigned int sector_count);

#endif //end of __BLOCK_H__
