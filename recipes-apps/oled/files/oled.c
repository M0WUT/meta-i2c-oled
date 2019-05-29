#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>

#define OLED_BASE_ADDR 0b01111000
const int oledAddrBit = 0; // SA0 pin can be used to give 2 possible addresses

////////////////////////////////////////////////////////
// Writes array of command bytes to OLED
// Arguments:
//		iic:	file descriptor for open I2C device 
//				OLED slave address must have been set
//				using ioctl
//		commands:
// Returns:
//		0: 		Success
//		-1: 	Error writing to OLED
////////////////////////////////////////////////////////	
int write_command(int iic, uint8_t* cmd, uint8_t cmdLength)
{
	// Before command, a control byte of all 0s needs to be sent
	uint8_t buffer[cmdLength + 1]; 
	buffer[0] = 0;
	int i = 0;
	for(i = 0; i < cmdLength; i++)
	{
		buffer[i + 1] = cmd[i];
	}

	// Write to device. Third argument is number of bytes
	int bytesWritten = write(iic, buffer, cmdLength + 1);

	// Status now contains number of bytes successfully written
	if(bytesWritten == cmdLength + 1)
		return 0;
	else
		return -1;
}

////////////////////////////////////////////////////////
// Sets config registers of OLED that are wanted to be
// non-default
// Arguments:
//		iic:	file descriptor for open I2C device 
//				OLED slave address must have been set
//				using ioctl
// Returns:
//		0: 		Success
//		-1: 	Error writing to OLED
////////////////////////////////////////////////////////	

int init_display(int iic)
{
	uint8_t buffer[6]; // 6 bytes is largest possible command

	// This assumes that all other registers contain RESET values

	// Disable display
	buffer[0] = 0xAE;
	if(write_command(iic, buffer, 1))
		return -1;

	// Vertical Paging mode
	buffer[0] = 0x20;
	buffer[1] = 0x01;
	if(write_command(iic, buffer, 2))
		return -1;

	// Set column range
	buffer[0] = 0x21; // Command
	buffer[1] = 0; // Start address
	buffer[2] = 127; // End address
	if(write_command(iic, buffer, 3))
		return -1;

	// Set page range (1 page is 8 pixels tall)	
	buffer[0] = 0x22; // Command
	buffer[1] = 0; // Start page
	buffer[2] = 3; // End page (32 pixel display)
	if(write_command(iic, buffer, 3))
		return -1;

	/* 
	N.B. Display is not yet enabled.
	RAM should be filled before enabling the display
	*/
	return 0;
}

////////////////////////////////////////////////////////
// Populates OLED RAM with IP address shown in 16x8 font
// Arguments:
//		iic:	file descriptor for open I2C device 
//				OLED slave address must have been set
//				using ioctl
//		ipAddr:	char point to IP address as a string.
//				Values should be ASCII, '.' should be 
//				included
//		length: number of elements in ipAddr
// Returns:
//		0: 		Success
//		-1: 	Error writing to OLED
////////////////////////////////////////////////////////		

int fill_ram(int iic, uint8_t *ipAddr)
{
	uint8_t buffer[512]; // 128 columns * 4 pages (32 pixels)

	// @TODO finish this section



}
int main()
{

	//Open I2C device driver
	int iic = open("/dev/i2c-0", O_RDWR);
	if (iic < 0)
	{
		printf("Error opening I2C kernel module");
		return -1;
	}

    int status = ioctl(iic, I2C_SLAVE_FORCE, (OLED_BASE_ADDR | (oledAddrBit << 1)));
    if(status < 0)
    {
        printf("Unable to set the OLED address to %#04\n", (OLED_BASE_ADDR | (oledAddrBit << 1)));
		close(iic);
        return -1;
    }

	init_display(iic);






	close(iic);		
	return 0;
}
