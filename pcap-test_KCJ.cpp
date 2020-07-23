#include <pcap.h>
#include <stdio.h>
#include <cstring>
#include <stdint.h>
#include <netinet/in.h>

#define ETHER_ADDR_LEN 6
#define IP_ADDR_LEN 4
#define PAYLOAD_LEN 8
#define ETHER_TYPE_LEN 2

struct eth_hdr
{
    uint8_t mac_src[ETHER_ADDR_LEN]; // MAC Source
    uint8_t mac_dest[ETHER_ADDR_LEN]; // MAC Destination 
    uint8_t eth_type[ETHER_TYPE_LEN]; // Ether type
};

struct ipv4_hdr
{
    uint8_t ip_ver_hl; // Version and IHL
    uint8_t src_ip[IP_ADDR_LEN]; // Source IP Address
    uint8_t dest_ip[IP_ADDR_LEN]; // Destination IP Address

};

struct tcp_hdr
{
    uint16_t src_port;
    uint16_t dest_port;
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
	
	printf("\nEthernet Header\n");
	
	memcpy(e_hdr.mac_dest, packet, 6);
	printf("\nDestination MAC Address : ");
	for(i=0; i<6; i++)
		printf("%02x ", e_hdr.mac_dest[i]);
	
	memcpy(e_hdr.mac_src, packet+6, 6);
	printf("\nSource MAC Address : ");
	for(i=0; i<6; i++)
		printf("%02x ", e_hdr.mac_src[i]);
	
	memcpy(e_hdr.eth_type, packet+12, 2);
	printf("\nEthernet Type : ");
	for(i=0; i<2; i++)
		printf("%02x ", e_hdr.eth_type[i]);
		
	printf("\n\nIPv4 Header\n");		
	
	memcpy(&ip_hdr.ip_ver_hl, packet+14, 1);
	printf("\nIP Version and Header length : "); // to do : split version / header length 
	for(i=0; i<1; i++)
		printf("%02x ", ip_hdr.ip_ver_hl);
		
	memcpy(ip_hdr.src_ip, packet+26, 4);
	printf("\nSource IP Address : ");
	for(i=0; i<4; i++)
		printf("%d.", ip_hdr.src_ip[i]);
		
	memcpy(ip_hdr.dest_ip, packet+30, 4);
	printf("\nDestination IP Address : ");
	for(i=0; i<4; i++)
		printf("%d.", ip_hdr.dest_ip[i]);
		
	printf("\n\nTCP Header\n");
	
	memcpy(&t_hdr.src_port, packet+34, 2);
	printf("\nSource Port Number : ");
	printf("%u(%#x) ", ntohs(t_hdr.src_port), ntohs(t_hdr.src_port));
	
	memcpy(&t_hdr.dest_port, packet+36, 2);
	printf("\nDestination Port Number : ");
	printf("%u(%#x) ", ntohs(t_hdr.dest_port), ntohs(t_hdr.dest_port));
	
	memcpy(&t_hdr.payload, packet+54, 16); // to do : handling when empty payload case
	printf("\nTcp Payload : ");
	for(i=0; i<16; i++)
		printf("%02x ", t_hdr.payload[i]);
	
            
        printf("\n%u bytes captured\n", header->caplen);
        
        printf("\n====================================================\n");
    }

    pcap_close(handle);
}
