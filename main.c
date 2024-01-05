/******************************************************
 * main.c 
 * The main function for usb_hub_compliance_tool
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h> // for open()
#include <unistd.h> // for close()

#include <linux/usbdevice_fs.h>
#include <linux/usb/ch9.h>
#include <linux/usb/ch11.h>

// below defination is from ch9.h
// #define	TEST_J		1
// #define	TEST_K		2
// #define	TEST_SE0_NAK	3
// #define	TEST_PACKET	4
// #define	TEST_FORCE_EN	5

// below defination is from ch1.h
// #define USB_PORT_FEAT_TEST              21

void show_helper(char *pg_name)
{
	printf("\nThis is a tool for making usb hub into compoance mode.\n");
	printf("Usage:    %s /dev/bus/usb/XXX/YYY -p [port_number] -a [test_action]\n", pg_name);
	printf("          XXX is usb bus number the DUT(hub) belongs to.\n");
	printf("          YYY is usb dev number the DUT(hub) belongs to.\n");
	printf("          XXX and YYY can be determinated by `lsusb` shell command.\n");
	printf("          port_number can be 1, 2, 3, 4, 5... Cannot be 0.\n");
	printf("          test_action can be j(means test_j),\n\
                             k(means test_k),\n\
                             se0(means test_se0_nak),\n\
                             u2p(means u2_test_packet),\n\
                             u3p(means u3_test_packet).\n");
	printf("Example:\n");
	printf("%s /dev/bus/usb/001/002 -p 1 -a j\n", pg_name);
	printf("%s /dev/bus/usb/001/002 -p 2 -a k\n", pg_name);
	printf("%s /dev/bus/usb/001/002 -p 3 -a u2p\n", pg_name);
}

int main(int argc, char *argv[])
{
	int fd = -1;
	int ret = -1;
	int port_num = -1;
	int test_action = -1;
	struct usbdevfs_ctrltransfer ctrl_req = { 0 };

	if (argc != 6)
	{
		show_helper(argv[0]);
		return -1;
	}
	
	return 0;
}
 