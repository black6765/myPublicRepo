all: pcap_KCJ

pcap_KCJ: main.o
	g++ -o pcap_KCJ main.o -lpcap

main.o: main.cpp pcap.cpp
	g++ -c -o main.o main.cpp -lpcap

clear:
	rm -f pcap_KCJ *.o
