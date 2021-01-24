LDLIBS=-lpcap

all: arp-spoof

send-arp-test: main.o arphdr.o ethhdr.o ip.o mac.o find_attacker_mac.o find_attacker_ip.o my_arp.o
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f send-arp-test *.o
