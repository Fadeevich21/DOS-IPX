#include "prjct2\utils.h"
#include "prjct2\ipx.h"
#include <conio.h>

void PreparePacket(struct ECB *packet, int socket,
				   struct IPXHeader *header, void *buffer,
				   int buffer_size) {
	memset(packet, 0, sizeof(*packet));
	packet->Socket = IntReverse(socket);
	packet->FragmentCnt = 2;
	packet->Fragments[0].Address = header;
	packet->Fragments[0].Size = sizeof(*header);
	packet->Fragments[1].Address = buffer;
	packet->Fragments[1].Size = buffer_size;
}

int SendPacket(int socket, void *buffer, int buffer_size) {
	struct ECB packet;
	struct IPXHeader header;

	PreparePacket(&packet, socket, &header, buffer, buffer_size);

	header.PacketType = 4;
	memset(header.DestNetwork, 0, 4);
	memset(header.DestNode, 0xFF, 6);
	header.DestSocket = IntReverse(socket);

	memset(packet.ImmAddress, 0xFF, 6);

	IPXSendPacket(&packet);
	delay(30);

	return packet.CCode;
}

int ReceivePacket(int socket, void *buffer, int buffer_size) {
	struct ECB packet;
	struct IPXHeader header;

	PreparePacket(&packet, socket, &header, buffer, buffer_size);

	IPXListenForPacket(&packet);
	while (packet.InUse != ECB_ACCEPTED_OR_TRANSMITTED) {
		IPXRelinquishControl();
		if (kbhit()) {
			IPXCancelEvent(&packet);
			getch();
			packet.CCode = 0xFE;
			break;
		}
	}

	return packet.CCode;
}