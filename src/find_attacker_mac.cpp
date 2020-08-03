#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

// This is not my origin code
// I just modify some code
// Source : https://community.onion.io/topic/2441/obtain-the-mac-address-in-c-code/2
void find_mac(char attacker_mac[], char* argv[])
{
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    char temp[10];

    strcpy(s.ifr_name, argv[1]);
    if (0 == ioctl(fd, SIOCGIFHWADDR, &s))
    {
        int i = 0;
        for (i = 0; i < 6; ++i)
        {
            sprintf(temp, "%02x:", (unsigned char)s.ifr_addr.sa_data[i]);
            strcpy(attacker_mac + i * 3, temp);
        }
        attacker_mac[17] = '\0';
    }
}
