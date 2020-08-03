// not my code

#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <arpa/inet.h>

void find_ip(char attacker_ip[], char *argv[])
{
        struct ifreq ifr;
        int s;

        s = socket(AF_INET, SOCK_DGRAM, 0);
        strncpy(ifr.ifr_name, argv[1], IFNAMSIZ);

        if(ioctl(s, SIOCGIFADDR, &ifr) < 0)
        {
                printf("Error");
        }
        else
        {
                inet_ntop(AF_INET, ifr.ifr_addr.sa_data+2,attacker_ip,sizeof(struct sockaddr));
        }
}

