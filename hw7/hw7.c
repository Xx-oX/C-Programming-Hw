#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

struct Ethernet {
	unsigned char DST_MAC[6];
	unsigned char SRC_MAC[6];
	unsigned char TYPE[2];
	};
struct IP {
    int LENGTH;
	unsigned char Header_1[2];//Version+IHL(Header length)+TOS
	unsigned char TOTAL_LENGTH[2];
	unsigned char Header_2[5];//Identification+IP flag+Fragment offset
	unsigned char PROTOCOL[1];
	unsigned char Header_3[2];//Header Checksum
	unsigned char DST_IP[4];
	unsigned char SRC_IP[4];
	};
struct TCP {
	unsigned char DST_PORT[2];
	unsigned char SRC_PORT[2];
	unsigned char HEADER[16];//other headers
	};
struct UDP {
    unsigned char DST_PORT[2];
    unsigned char SRC_PORT[2];
    unsigned char HEADER[4];//other headers
    };

struct Packet {
	struct Ethernet ETHERNET;
	struct IP IP;
    struct TCP TCP;
	struct UDP UDP;	
	//ICMP don't need to parse
};

int main(int argc,char *argv[])
{
	FILE *fp;
	if(argc != 2) {
      		printf("usage: ./hw7 test.out\n");
      		return -1;
   	}
   	/* open a file as a binary file */
   	fp = fopen(argv[1], "rb");

   	if(!fp) {
      		printf("Can't open file.\n");
      		return -1;
   	}

	int i,n = 0;
	int pro_id = 0;
	int num_of_TCP = 0;
	int num_of_UDP = 0;
	int num_of_ICMP = 0;
	struct Packet pak[999]; 
	unsigned char str[999][1500];

	while(fread(pak[n].ETHERNET.DST_MAC, sizeof(char), 6, fp) > 0) {
	/*Ethernet part*/
	//read MAC address
	printf("#%d\n", n+1);
	printf("DST MAC: ");
	for(i=0; i<5; i++) {
      		printf("%02x:", pak[n].ETHERNET.DST_MAC[i]);
   	}
   	printf("%02x\n",pak[n].ETHERNET.DST_MAC[5]);

	printf("SRC MAC: ");
	fread(pak[n].ETHERNET.SRC_MAC, sizeof(char), 6, fp);
   	for(i=0; i<5; i++) {
      		printf("%02x:", pak[n].ETHERNET.SRC_MAC[i]);
   	}
   	printf("%02x\n",pak[n].ETHERNET.SRC_MAC[5]);
	
	//read type / length
	fread(pak[n].ETHERNET.TYPE, sizeof(char), 2, fp);
	
	/*IPv4 part*/
	//read first 2 bytes
	fread(pak[n].IP.Header_1, sizeof(char), 2, fp);
	
	//read total length
	fread(pak[n].IP.TOTAL_LENGTH, sizeof(char), 2, fp);
	pak[n].IP.LENGTH = 256*pak[n].IP.TOTAL_LENGTH[0] + pak[n].IP.TOTAL_LENGTH[1] + 14;
	
	//read protocol
	fread(pak[n].IP.Header_2, sizeof(char), 5, fp);
	fread(pak[n].IP.PROTOCOL, sizeof(char), 1, fp);
	pro_id = pak[n].IP.PROTOCOL[0];

	//print protocol(1:ICMP,6:TCP,17:UDP)
	printf("Protocol: ");
	switch(pro_id) {
		case 1:
			printf("ICMP\n");
			break;
		case 6:
			printf("TCP\n");
			break;
		case 17:
			printf("UDP\n");
			break;
	}
	
	//read last 2 bytes in header
	fread(pak[n].IP.Header_3, sizeof(char), 2, fp);
	
	// read IP address and transfer
   	printf("SRC IP: ");
   	fread(pak[n].IP.SRC_IP, sizeof(char), 4, fp);
   	for(i=0; i<3; i++) {
   		printf("%d.", pak[n].IP.SRC_IP[i]);
   	}
   	printf("%d\n",pak[n].IP.SRC_IP[3]);
	printf("DST IP: ");
   	fread(pak[n].IP.DST_IP, sizeof(char), 4, fp);
   	for(i=0; i<3; i++) {
   		printf("%d.", pak[n].IP.DST_IP[i]);
   	}
   	printf("%d\n",pak[n].IP.DST_IP[3]);

	/*TCP / UDP part*/
    	// read Port number and transfer
	switch (pro_id) {
		case 1:
			num_of_ICMP++;
			fread(str[n], sizeof(char), pak[n].IP.LENGTH - 14 - 20, fp);//total-ethernet_header-ip_header
			break;
		case 6:
			num_of_TCP++;
			printf("SRC Port: ");
   			fread(pak[n].TCP.SRC_PORT, sizeof(char), 2, fp);
   			printf("%d\n", 256*pak[n].TCP.SRC_PORT[0]+pak[n].TCP.SRC_PORT[1]);
			printf("DST Port: ");
   			fread(pak[n].TCP.DST_PORT, sizeof(char), 2, fp);
   			printf("%d\n", 256*pak[n].TCP.DST_PORT[0]+pak[n].TCP.DST_PORT[1]);
			fread(pak[n].TCP.HEADER, sizeof(char), 16, fp);
			fread(str[n], sizeof(char), pak[n].IP.LENGTH - 14 - 20 - 20, fp);//total-ethernet_header-ip_header-TCP_header
			break;
		case 17:
			num_of_UDP++;
			printf("SRC Port: ");
   			fread(pak[n].UDP.SRC_PORT, sizeof(char), 2, fp);
   			printf("%d\n", 256*pak[n].UDP.SRC_PORT[0]+pak[n].UDP.SRC_PORT[1]);
			printf("DST Port: ");
   			fread(pak[n].UDP.DST_PORT, sizeof(char), 2, fp);
   			printf("%d\n", 256*pak[n].UDP.DST_PORT[0]+pak[n].UDP.DST_PORT[1]);
			fread(pak[n].UDP.HEADER, sizeof(char), 4, fp);
			fread(str[n], sizeof(char), pak[n].IP.LENGTH - 14 - 20 - 8, fp);//total-ethernet_header-ip_header-UDP_header
			break;
	}
	printf("Packet Length: %d\n\n",pak[n].IP.LENGTH);
	n++;
    }
	printf("Number of Packet: %d\n", n);
	printf("Number of TCP Packet: %d\n", num_of_TCP);
	printf("Number of UDP Packet: %d\n", num_of_UDP);
	printf("Number of ICMP Packet: %d\n", num_of_ICMP);
   	fclose(fp);
	return 0;
}

