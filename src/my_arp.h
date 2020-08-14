#pragma once

void arp_request(const char attacker_ip[], const char attacker_mac[], char sender_mac[], char* argv[], pcap_t *handle);

void arp_reply(const char attacker_ip[], const char attacker_mac[], char sender_mac[], char *argv[], pcap_t *handle);
