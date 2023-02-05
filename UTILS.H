#ifndef UTILS_H
#define UTILS_H

int SendPacket(int socket, void *buffer, int buffer_size);
int ReceivePacket(int socket, void *buffer, int buffer_size);

#endif