#include <stdio.h>
#include "prjct2\ipx.h"
#include "prjct2\msg_cmd.h"
#include "prjct2\utils.h"

int main(int argc, char *argv[]) {
	FILE *file;
	char* filename;
	int socket = 0x0;
	char txBuffer[BUFFER_SIZE];
	int res;
	int countPacket = 0;

	print_dbg("I'm server!\n", 0);
	if (argc != 2) {
		print_error("not 1 argument was passed", 0);
		exit(-1);
	}
	filename = argv[1];

	if (IPXInit())
		print_dbg("IPX driver is loaded!\n", 0);
	else {
		print_error("IPX driver is not loaded!\n", 0);
		exit(-1);
	}

	res = IPXOpenSocket(SHORT_LIVED_SOCKET, &socket);
	if (res == SOCKET_WAS_OPENED_EARLIER) {
		print_error("Socket was opened earlier", 0);
		exit(-1);
	} else if (res == SOCKET_TABLE_OVERFLOW) {
		print_error("Socket table overflow", 0);
		exit(-1);
	}

	file = fopen(filename, "rb");
	if (file == NULL) {
		print_error("fopen failed\n", 0);
		exit(-1);
	};

	while(1) {
		print_dbg("packet number: %d\n", 1, ++countPacket);
		fread(txBuffer, sizeof(char), BUFFER_SIZE, file);
		if (ferror(file)) {
			print_error("error reading file\n", 0);
			exit(-1);
		}

		res = SendPacket(socket, txBuffer, BUFFER_SIZE);
		if (res != ECB_SUCCESS) {
			print_error("send packet failed\n", 0);
			break;
		}

		if (feof(file))
			break;
	}

	fclose(file);
	IPXCloseSocket(socket);
	return 0;
}