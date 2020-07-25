// [BOB9][Kim Cheong-Jun][pcap-programming]

#include <pcap.h>
#include <stdio.h>
#include <cstring>
#include <stdint.h>
#include <netinet/in.h>

#define ETHER_ADDR_LEN 6
#define IP_ADDR_LEN 4
#define PAYLOAD_LEN 8
#define ETHER_TYPE_LEN 2


// struct headers
struct eth_hdr
{
    uint8_t mac_src[ETHER_ADDR_LEN]; // MAC Source : Locate packet[0]~packet[5]
    uint8_t mac_dest[ETHER_ADDR_LEN]; // MAC Destination : Locate packet[6]~packet[11] 
    uint8_t eth_type[ETHER_TYPE_LEN]; // Ether type : Locate packet[12]~packet[13]
};

struct ipv4_hdr
{
    uint8_t ip_ver_hl; // Version and IHL : Locate packet[14]
    uint8_t src_ip[IP_ADDR_LEN]; // Source IP Address : Locate packet[26]~packet[29]
    uint8_t dest_ip[IP_ADDR_LEN]; // Destination IP Address : Locate packet[30]~packet[33]
   /*
   uint16_t total_len; // Debug : For Calculating TCP Payload Length 
   */
};

struct tcp_hdr
{
    uint16_t src_port; // Source Port Number : Locate packet[34]~packet[35]
    uint16_t dest_port; // Destination Port Number : Locate packet[36]~packet[37]
    uint8_t payload[PAYLOAD_LEN]; // TCP Payload : Locate packet[54]~packet[69]
};

void pcap_KCJ(const u_char* packet)
{
	int i = 0;
	int index = 0;
	
	struct eth_hdr e_hdr;
	struct ipv4_hdr ip_hdr;
	struct tcp_hdr t_hdr;
	
	// Print TCP Packet Information
	printf("\nEthernet Header\n");
	
	// memcpy packet[0]~packet[5]
	memcpy(e_hdr.mac_dest, packet, 6);
	printf("\nDestination MAC Address : ");
	for(i=0; i<6; i++)
		printf("%02x ", e_hdr.mac_dest[i]);
	// memcpy packet[6]~packet[11]
	memcpy(e_hdr.mac_src, packet+6, 6);
	printf("\nSource MAC Address : ");
	for(i=0; i<6; i++)
		printf("%02x ", e_hdr.mac_src[i]);
	// memcpy packet[12]~packet[13]
	memcpy(e_hdr.eth_type, packet+12, 2);
	printf("\nEthernet Type : ");
	for(i=0; i<2; i++)
		printf("%02x ", e_hdr.eth_type[i]);
		
	printf("\n\nIPv4 Header\n");		
	// memcpy packet[14]
	memcpy(&ip_hdr.ip_ver_hl, packet+14, 1);
	printf("\nIP Version and Header length : "); // to do : split version / header length 
	printf("%02x ", ip_hdr.ip_ver_hl);
	// Split IP Version and Header Length(packet[14]) in two bytes -> IP Version / IP Header Length(*4)
	uint8_t ip_hl = (ip_hdr.ip_ver_hl % 16) * 4; 
	uint8_t ip_ver = ip_hdr.ip_ver_hl / 16;
	printf("\nIP Version : %u\n", ip_ver);
	printf("IP Header Length : %u\n", ip_hl); 
	
	// memcpy packet[26]~packet[29]
	memcpy(ip_hdr.src_ip, packet+26, 4);
	printf("\nSource IP Address : ");
	for(i=0; i<4; i++)
		printf("%d.", ip_hdr.src_ip[i]);
	// memcpy packet[30]~packet[33]
	memcpy(ip_hdr.dest_ip, packet+30, 4);
	printf("\nDestination IP Address : ");
	for(i=0; i<4; i++)
		printf("%d.", ip_hdr.dest_ip[i]);
		
	printf("\n\nTCP Header\n");
	// memcpy packet[34]~packet[35]
	memcpy(&t_hdr.src_port, packet+34, 2);
	printf("\nSource Port Number : ");
	printf("%u(%#x) ", ntohs(t_hdr.src_port), ntohs(t_hdr.src_port));
	// memcpy packet[36]~packet[37]
	memcpy(&t_hdr.dest_port, packet+36, 2);
	printf("\nDestination Port Number : ");
	// Convert Network Byte Order to Host Byte Order for print decimal number
	printf("%u(%#x) ", ntohs(t_hdr.dest_port), ntohs(t_hdr.dest_port));
	
	/* Debug : Print payload length
	// memcpy packet[16]~packet[17] : Total Length(For Calculating TCP Payload Length)
	memcpy(&ip_hdr.total_len, packet+16, 2);
	uint8_t tcp_hl = (packet[46] / 16) * 4;
	uint8_t tcp_payload_len = ntohs(ip_hdr.total_len) - ip_hl - tcp_hl;
	printf("\nTotal Length(%u) - IP Header Length(%u) - TCP Header Length(%u) = Payload Length(%u)", 
	ntohs(ip_hdr.total_len), ip_hl, tcp_hl, tcp_payload_len);
	*/ 
	
	// Print TCP Payload 16 bytes
	memcpy(&t_hdr.payload, packet+54, 16); 
	printf("\nTcp Payload : ");
	for(i=0; i<16; i++)
			printf("%02x ", t_hdr.payload[i]);

}
