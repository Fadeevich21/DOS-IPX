#include <stdio.h>
#include "prjct2\ipx.h"
#include "prjct2\msg_cmd.h"
#include "prjct2\utils.h"

int main(int argc, char *argv[]) {
	FILE* file;
	char* filename;
	int socket = 0x0;
	char rxBuffer[BUFFER_SIZE];
	int res;
	int countPacket = 0;

	print_dbg("I'm client!\n", 0);
	if (argc != 2) {
		print_error("not 1 argument was passed", 0);
		exit(-1);
	}
	filename = argv[1];

	if (IPXInit())
		print_dbg("IPX driver is loaded!\n", 0);
	else {
		print_error("IPX driver is not loader!\n", 0);
		exit(-1);
	}

	res = IPXOpenSocket(SHORT_LIVED_SOCKET, &socket);
	if (res == SOCKET_WAS_OPENED_EARLIER) {
		print_error("socket was opened earlier\n", 0);
		exit(-1);
	} else if (res == SOCKET_TABLE_OVERFLOW) {
		print_error("socket table overflow\n", 0);
		exit(-1);
	}

	file = fopen(filename, "wb");
	while (1) {
		res = ReceivePacket(socket, rxBuffer, BUFFER_SIZE);
		if (res != ECB_SUCCESS) {
			if (res != ECB_NO_STATION_WITH_THIS_ADDRESS)
				print_error("receive packet failed\n", 0);
			break;
		}
		print_dbg("packet number: %d\n", 1, ++countPacket);

		if (fwrite(rxBuffer, sizeof(char), BUFFER_SIZE, file) != BUFFER_SIZE)
			break;
	}

	print_dbg("the client accepted %d packages\n", 1, countPacket);

	fclose(file);
	IPXCloseSocket(socket);
	return 0;
}