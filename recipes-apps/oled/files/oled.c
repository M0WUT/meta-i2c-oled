#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>

#define OLED_ADDR 0x20

int iic;

int main()
{

	//Set things up and check for errors
	iic = open("/dev/i2c-0", O_RDWR);
	if (iic < 0)
	{
		printf("Error opening I2C device");
		return -1;
	}

	int status = 0;
    status = ioctl(iic, I2C_SLAVE_FORCE, OLED_ADDR);
    if(status < 0)
    {
        printf("Unable to set the OLED address to %#04\n", OLED_ADDR);
		close(iic);
        return -1;
    }

	uint8_t buffer[] = {1,2};
	int bytesWritten = write(iic, buffer, 2);
	printf("Successfully wrote %d bytes out of %d\n", bytesWritten, sizeof(buffer) / sizeof(buffer[0]));


	close(iic);		
	return 0;
}
