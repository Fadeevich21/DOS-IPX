#include "prjct2\ipx.h"
#include <dos.h>

void (far *IPXDriverInvoke) (void);

int IPXInit() {
	int intnum = 0x2F;
	int status;

	_AX = 0x7A00;
	geninterrupt(intnum);
	status = _AL;
	IPXDriverInvoke = MK_FP(_ES, _DI);

	return status == 0xFF;
}

unsigned IntReverse(unsigned x) {
	return (((x) & 0x00FF) << 8 | ((x) & 0xFF00) >> 8);
}

int IPXOpenSocket(int socketType, int* socketNumber) {
	int status;

	_AL = socketType;
	_DX = IntReverse(*socketNumber);
	_AL = socketType;
	_BX = 0x00;

	IPXDriverInvoke();
	status = _AL;
	*socketNumber = IntReverse(_DX);

	return status;
}

void IPXCloseSocket(int socket_number) {
	_BX = 0x01;
	_DX = IntReverse(socket_number);

	IPXDriverInvoke();
}

void IPXGetLocalTarget(char *buf) {
	_BX = 0x09;
	_ES = FP_SEG(buf);
	_SI = FP_OFF(buf);

	IPXDriverInvoke();
}

void IPXListenForPacket(struct ECB *packet) {
	_BX = 0x04;
	_ES = FP_SEG(packet);
	_SI = FP_OFF(packet);

	IPXDriverInvoke();
}

void IPXSendPacket(struct ECB *packet) {
	_BX = 0x03;
	_ES = FP_SEG(packet);
	_SI = FP_OFF(packet);

	IPXDriverInvoke();
}

void IPXRelinquishControl() {
	_BX = 0x0A;

	IPXDriverInvoke();
}

int IPXCancelEvent(struct ECB *packet) {
	int status;

	_BX = 0x06;
	_ES = FP_SEG(packet);
	_SI = FP_SEG(packet);

	IPXDriverInvoke();
	status = _AL;

	return status;
}