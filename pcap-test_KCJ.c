#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ETHER_ADDR_LEN 6
#define IP_ADDR_LEN 4
#define PAYLOAD_LEN 8
#define DEST_ETH_RANGE(x) x >= 0 && x <= 5
#define SRC_ETH_RANGE(x) x >= 6 && X <= 11
#define ETH_TYPE_RANGE(x) x >= 12 && x <= 13
#define IP_VER_HL_RANGE(x) x == 14
#define SCR_IP_RANGE(x) x >= 26 && x <= 29
#define DEST_IP_RANGE(x) x >= 30 && x <= 33
#define SRC_PORT_RANGE(x) x >= 34 && x <= 35
#define DEST_PORT_RANGE(x) x >= 36 && x <= 37
#define PAYLOAD_RANGE(x) x >= 54 && x <= 69

struct eth_hdr
{
    uint8_t src_eth[ETHER_ADDR_LEN]; // destination ethernet address
    uint8_t dest_eth[ETHER_ADDR_LEN]; // source ethernet address
    uint16_t eth_type;
};

struct ipv4_hdr
{
    uint8_t ip_ver_hl;
    uint8_t src_ip[IP_ADDR_LEN];
    uint8_t dest_ip[IP_ADDR_LEN];
    
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
        struct tcp_payload t_pay;
        const u_char* packet;

        int res = pcap_next_ex(handle, &header, &packet);
        if (res == 0) continue;
        if (res == -1 || res == -2) {
            printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(handle));
            break;
        }
        for(i=0; i<257; i++)
        {
            printf("%x[%d]\n",packet[i],i);
        }

        printf("%u bytes captured\n", header->caplen);
    }

    pcap_close(handle);
}

