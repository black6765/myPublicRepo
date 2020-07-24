#include <pcap.h>
#include <stdio.h>
#include <cstring>
#include <stdint.h>
#include <netinet/in.h>

#define ETHER_ADDR_LEN 6
#define IP_ADDR_LEN 4
#define PAYLOAD_LEN 8
#define ETHER_TYPE_LEN 2
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

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
    uint16_t total_len;

};

struct tcp_hdr
{
    uint16_t src_port;
    uint16_t dest_port;
    uint8_t payload[PAYLOAD_LEN];
};

void pcap_KCJ(const u_char* packet)
{
	int i = 0;
	int index = 0;
	
	struct eth_hdr e_hdr;
	struct ipv4_hdr ip_hdr;
	struct tcp_hdr t_hdr;
	
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
	uint8_t ip_hl = (ip_hdr.ip_ver_hl % 16) * 4;
	uint8_t ip_ver = ip_hdr.ip_ver_hl / 16;
	printf("\nIP Version : %u\n", ip_ver);
	printf("IP Header Length : %u\n", ip_hl); 
		
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
	
	memcpy(&ip_hdr.total_len, packet+16, 2);
	uint8_t tcp_hl = (packet[46] / 16) * 4;
	uint8_t tcp_payload_len = ntohs(ip_hdr.total_len) - ip_hl - tcp_hl;
	
	/* Debug : Print payload length
	printf("\nTotal Length(%u) - IP Header Length(%u) - TCP Header Length(%u) = Payload Length(%u)", 
	ntohs(ip_hdr.total_len), ip_hl, tcp_hl, tcp_payload_len);
	*/ 
	
	memcpy(&t_hdr.payload, packet+54, 16); 
	printf("\nTcp Payload : ");
	for(i=0; i<16; i++)
			printf("%02x ", t_hdr.payload[i]);

}
