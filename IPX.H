#ifndef TEST_H
#define TEST_H

#define SHORT_LIVED_SOCKET 0x00
#define LONG_LIVED_SOCKET 0xFF

#define SOCKET_IS_OPEN 0x00
#define SOCKET_WAS_OPENED_EARLIER  0xFF
#define SOCKET_TABLE_OVERFLOW 0xFE

#define ECB_FOR_SENDING 0xFF
#define ECB_FOR_RECEIVING 0xFE
#define ECB_IS_USED_BY_AES 0xFD
#define ECB_IN_INTERNAL_QUEUE 0xFB
#define ECB_ACCEPTED_OR_TRANSMITTED 0x00

/* States when receiving or transmitting an ECB packet */
#define ECB_SUCCESS 0x00
#define ECB_REQUEST_CANCELED 0xFC

/* States when receiving an ECB packet */
#define ECB_SOCKET_NOT_OPEN 0xFF
#define ECB_PACKET_OVERFLOW 0xFD

/* States when transmitting an ECB packet */
#define ECB_PHYSICAL_ERROR 0xFF
#define ECB_NO_STATION_WITH_THIS_ADDRESS 0xFE
#define ECB_PACKET_FAULTY 0xFD

#define ECB_PROCESSING_CANNOT_BE_CANCELED 0xF9
#define THIS_ECB_NOT_USED 0xFF

#define BUFFER_SIZE 512

struct IPXHeader {
	unsigned int Checksum;
	unsigned int Length;
	unsigned char TransportControl;
	unsigned char PacketType;
	unsigned char DestNetwork[4];
	unsigned char DestNode[6];
	unsigned int DestSocket;
	unsigned char SourceNetwork[4];
	unsigned char SourceNode[6];
	unsigned int SourceSocket;
};

struct Fragment {
	void far *Address;
	unsigned int Size;
};

struct ECB {
	void far *Link;
	void far (*ESRAddress)(void);
	unsigned char InUse;
	unsigned char CCode;
	unsigned int Socket;
	unsigned char IPXWorkspace[4];
	unsigned char DriverWorkspace[12];
	unsigned char ImmAddress[6];
	unsigned int FragmentCnt;
	struct Fragment Fragments[2];
};

unsigned IntReverse(unsigned x);

int IPXInit();

int IPXOpenSocket(int socketType, int *socketNumber);
void IPXCloseSocket(int socketNumber);

void IPXGetLocalTarget(char *buf);

void IPXListenForPacket(struct ECB *packet);
void IPXSendPacket(struct ECB *packet);

void IPXRelinquishControl();

int IPXCancelEvent(struct ECB *packet);

#endif