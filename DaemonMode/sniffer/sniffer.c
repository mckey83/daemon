#include"sniffer.h"
#include <pthread.h>
#include"DaemonMode/macro/ip_to_d_d_d_d.h"
#include"DaemonMode/store/store_simple.h"
#include"DaemonMode/data/record.h"

#define CHILD_NEED_TERMINATE	2
#define COMMAND_SHOW 5
#define COMMAND_SAVE 10
#define COMMAND_LOAD 15
#define COMMAND_SEARCH_IP 25

__u8* networkInterface;


int getifconf(__u8 *intf, struct ifparam *ifp, int mode)
{
    int fd;
    struct sockaddr_in s;
    struct ifreq ifr;

    memset((void *)&ifr, 0, sizeof(struct ifreq));
    if((fd = socket(AF_INET,SOCK_DGRAM,0)) < 0) return (-1);

    sprintf(ifr.ifr_name,"%s",intf);

    if(!mode) goto setmode;

    if(ioctl(fd, SIOCGIFADDR, &ifr) < 0) {
        perror("ioctl SIOCGIFADDR");
        return -1;
    }
    memset((void *)&s, 0, sizeof(struct sockaddr_in));
    memcpy((void *)&s, (void *)&ifr.ifr_addr, sizeof(struct sockaddr));
    memcpy((void *)&ifp->ip, (void *)&s.sin_addr.s_addr, sizeof(__u32));

    if(ioctl(fd, SIOCGIFNETMASK, &ifr) < 0) {
        perror("ioctl SIOCGIFNETMASK");
        return -1;
    }
    memset((void *)&s, 0, sizeof(struct sockaddr_in));
    memcpy((void *)&s, (void *)&ifr.ifr_netmask, sizeof(struct sockaddr));
    memcpy((void *)&ifp->mask, (void *)&s.sin_addr.s_addr, sizeof(u_long));

    if(ioctl(fd, SIOCGIFMTU, &ifr) < 0) {
        perror("ioctl SIOCGIFMTU");
        return -1;
    }
    ifp->mtu = ifr.ifr_mtu;

    if(ioctl(fd, SIOCGIFINDEX, &ifr) < 0) {
        perror("ioctl SIOCGIFINDEX");
        return -1;
    }
    ifp->index = ifr.ifr_ifindex;


setmode:

    if(ioctl(fd, SIOCGIFFLAGS, &ifr) < 0) {
        perror("ioctl SIOCGIFFLAGS");
        close(fd);
        return -1;
    }

    if(mode) ifr.ifr_flags |= IFF_PROMISC;
    else ifr.ifr_flags &= ~(IFF_PROMISC);


    if(ioctl(fd, SIOCSIFFLAGS, &ifr) < 0) {
        perror("ioctl SIOCSIFFLAGS");
        close(fd);
        return (-1);
    }
    return 0;
}


int getsock_recv(int index)
{
    int sd;
    struct sockaddr_ll s_ll;
    sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(sd < 0) return -1;

    memset((void *)&s_ll, 0, sizeof(struct sockaddr_ll));

    s_ll.sll_family = PF_PACKET;
    s_ll.sll_protocol = htons(ETH_P_ALL);
    s_ll.sll_ifindex = index;

    if(bind(sd, (struct sockaddr *)&s_ll, sizeof(struct sockaddr_ll)) < 0) {
        close(sd);
        return -1;
    }
    return sd;
}

void mode_off() {
    if(getifconf(networkInterface, &ifp, PROMISC_MODE_OFF) < 0) {
        perror("getifconf");
        exit(-1);
    }
    return;
}

proceedCommand(int* command, __be32* searchIp){
    if (*command == COMMAND_SHOW) {
        Store_show ();
        *command =1;
    }
    if (*command == COMMAND_LOAD) {
        load ();
        *command =1;
    }
    if (*command == COMMAND_SAVE) {
        save ();
        *command = 1;
    }
    if (*command == COMMAND_SEARCH_IP) {
        Store_searchIp (searchIp);
        *command = 1;
    }
}


void writeRecord(struct iphdr* ip, int quantity ){
    struct Record* record = (struct Record*)malloc(sizeof(struct Record)*1);
    record->sourceIP = ip->saddr;
    record->distanationIP = ip->daddr;
    record->quantityPockets = quantity;
    if (!addData(record)){
        DEBUG_TEST_INFO(printf("==============================!addData==================================\n");)
    }
    free (record);
}



int Sniffer_start( __u8* networkInterface_, int* command, __be32* searchIp) {
DEBUG_TEST_ACTION(int i = 0; char* source = "Sniffer_start"; int result = 0;);

DEBUG_TEST_ACTION(  result =)initializeStore();
DEBUG_TEST_ACTION( if (result) i++; )

    networkInterface = networkInterface_;
    __u8 buff[ETH_FRAME_LEN];
    __u32 num = 0;
    int eth0_if, rec = 0, ihl = 0;
    struct iphdr ip;
    struct tcphdr tcp;
    struct ethhdr eth;
    static struct sigaction act;

    if(getifconf(networkInterface, &ifp, PROMISC_MODE_ON) < 0) {
        perror("getifconf");
        *command = CHILD_NEED_TERMINATE;
        exit(-1);
    }
        printf("networkInterface = %s \n",networkInterface );
        printf("IP address : %d.%d.%d.%d \n", NIPQUAD(ifp.ip));
        printf("Netmask :  %d.%d.%d.%d \n" ,NIPQUAD(ifp.mask));
        printf("MTU - %d\n", ifp.mtu);
        printf("interface - %d\n", ifp.index);
    if((eth0_if = getsock_recv(ifp.index)) < 0) {
        perror("getsock_recv");
        return -1;
    }
    act.sa_handler = mode_off;
    sigfillset(&(act.sa_mask));
    sigaction(SIGINT, &act, NULL);
    int quantity = 0;

    int counter = 0;
    while(*command > 0){
        if (*command > 0)
            proceedCommand(command, searchIp);

        memset(buff, 0, ETH_FRAME_LEN);
        rec = recvfrom(eth0_if, (char *)buff, ifp.mtu + 14, 0, NULL, NULL);
        if(rec < 0 || rec > ETH_FRAME_LEN) {
            perror("recvfrom");
            return -1;
        }
        memcpy((void *)&eth, buff, ETH_HLEN);
        memcpy((void *)&ip, buff + ETH_HLEN, sizeof(struct iphdr));
        if((ip.version) != 4) continue;
        memcpy((void *)&tcp, buff + ETH_HLEN + ip.ihl * 4, sizeof(struct tcphdr));
        writeRecord(&ip, quantity++);

    }    
    DEBUG_TEST_RESULT(if (1 == i && 0 == *command )
                          printf("++++>Test %s - OK\n", source);
                      else {
                        printf("---->Test %s - is Falied, not normall finish\n", source);
                        printf("---->counter = %d \n", counter);
                        });
    if (0 != *command)
        kill(getpid(),SIGTERM);
    return 0;
}
