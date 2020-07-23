#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ETHER_ADDR_LEN 6
#define IP_ADDR_LEN 4
#define PAYLOAD_LEN 8
#define DEST_ETH_RANGE(x) (((x) >= (0)) && ((x) <= (5)))
#define SRC_ETH_RANGE(x) (((x) >= (6)) && ((x) <= (11)))
#define ETH_TYPE_RANGE(x) (((x) >= (12)) && ((x) <= (13)))
#define IP_VER_HL_RANGE(x) ((x) == (14))
#define SCR_IP_RANGE(x) (((x) >= (26)) && ((x) <= (29)))
#define DEST_IP_RANGE(x) (((x) >= (30)) && ((x) <= (33)))
#define SRC_PORT_RANGE(x) (((x) >= (34)) && ((x) <= (35)))
#define DEST_PORT_RANGE(x) (((x) >= (36)) && ((x) <= (37)))
#define PAYLOAD_RANGE(x) (((x) >= (54)) && ((x) <= (69)))
#define EOI 69

struct eth_hdr
{
    uint8_t mac_src[ETHER_ADDR_LEN]; // MAC Source
    uint8_t mac_dest[ETHER_ADDR_LEN]; // MAC Destination 
    uint16_t eth_type; // Ether type
};

struct ipv4_hdr
{
    uint8_t ip_ver_hl; // Version and IHL
    uint8_t src_ip[IP_ADDR_LEN]; // Source IP Address
    uint8_t dest_ip[IP_ADDR_LEN]; // Destination IP Address

};

struct tcp_hdr
{
    uint32_t src_port;
    uint32_t dest_port;
    uint8_t payload[PAYLOAD_LEN];
};


void usage() {
    printf("syntax: pcap-test <interface>\n");
    printf("sample: pcap-test wlan0\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        usage();
        return -1;
    }
    int i = 0;
    int index = 0;
    char* dev = argv[1];
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        fprintf(stderr, "pcap_open_live(%s) return nullptr - %s\n", dev, errbuf);
        return -1;
    }

    while (true) {
        struct pcap_pkthdr* header;
        struct eth_hdr e_hdr;
        struct ipv4_hdr ip_hdr;
        struct tcp_hdr t_hdr;
        const u_char* packet;

        int res = pcap_next_ex(handle, &header, &packet);
        if (res == 0) continue;
        if (res == -1 || res == -2) {
            printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(handle));
            break;
        }

	printf("Ethernet Header\n");
        printf("\nDEST MAC : ");
        for(i=0; i<=5; i++)
            printf("%02x ", packet[i]);
        printf("\nSRC MAC : ");
        for(i=6; i<=11; i++)
            printf("%02x ", packet[i]);
        printf("\nETH TYPE : ");
        for(i=12; i<=13; i++)
            printf("%02x ", packet[i]);
        
    	printf("IPv4 Header\n");	
        printf("\nIP Version and Header length : ");
        printf("%02x ", packet[14]);
        printf("\nSRC IP : ");
        for(i=26; i<=29; i++)
            printf("%d.", packet[i]);
	printf("\b\b");
        printf("\nDEST IP : ");
        for(i=30; i<=33; i++)
            printf("%d.", packet[i]);
        printf("\b\b");

	printf("TCP Header\n");
        printf("\nSRC PORT : ");
        for(i=34; i<=35; i++)
            printf("%02x ", packet[i]);
        printf("\nDEST PORT : ");
        for(i=36; i<=37; i++)
            printf("%02x ", packet[i]);
      	printf("\nTCP PAYLOAD : ");
	for(i=54; i<=69; i++)
            printf("%02x ", packet[i]);
            
        printf("%u bytes captured\n", header->caplen);
    }

    pcap_close(handle);
}
