#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/socket.h>
#include <linux/ioctl.h>
#include <linux/if.h>
#include <linux/in.h>
#include <linux/types.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <signal.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <string.h> /* memset */
#include <unistd.h> /* close */
#include"DaemonMode/tests/test_sniffer.h"

#define PROMISC_MODE_ON 1
#define PROMISC_MODE_OFF 0

struct ifparam {
    __u32 ip;
    __u32 mask;
    int mtu;
    int index;
} ifp;


int getifconf(__u8 *intf, struct ifparam *ifp, int mode);
int getsock_recv(int index);
void mode_off();
int Sniffer_start(__u8* networkInterface, int * command, __be32* searchIp);
