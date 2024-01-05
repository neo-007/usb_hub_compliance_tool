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
#include <getopt.h>

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

int get_test_action(char *argv)
{
	if (strcmp(argv, "j") == 0)
		return TEST_J;

	if (strcmp(argv, "k") == 0)
		return TEST_K;

	if (strcmp(argv, "se0") == 0)
		return TEST_SE0_NAK;

	if (strcmp(argv, "u2p") == 0)
		return TEST_PACKET;

	if (strcmp(argv, "u3p") == 0)
		return USB_PORT_FEAT_TEST;
	
	return -1;
}

int main(int argc, char *argv[])
{
	int fd = -1;
	int ret = -1;
	int port_num = -1;
	int test_action = -1;
	int c;
	struct usbdevfs_ctrltransfer ctrl_req = { 0 };

	if (argc != 6)
	{
		show_helper(argv[0]);
		return -1;
	}

	opterr = 0;
	while ((c = getopt(argc, argv, "p:a:")) != -1) {

		switch (c) {
		case 'p':
			port_num = atoi(optarg);
			break;
		case 'a':
			test_action = get_test_action(optarg);
			break;

		default:
			printf("Invalid option -%c\n", (char)optopt);
			show_helper(argv[0]);
			return -1;
		}
	}

	printf("port_num:%d\n", port_num);
	printf("test_action:%d\n", test_action);
	
	return 0;
}
 