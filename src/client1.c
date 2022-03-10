#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PORT	9000
#define BUF_SIZE	256

int main() {
	char buf[BUF_SIZE];
	struct socketaddr_in sin;
	int sd; // connect socket

	if ((sd = socket(AF_INET, SOCK_STEAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT); // (short)HBO -> (short)NBO
	sin.sin_addr.s_addr = inet_addr("192.168.0.180"); // set server IP

	if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("connect");
		exit(1);
	}

	if (recv(sd, buf, sizeof(buf), 0) == -1) {
		perror("recv");
		exit(1);
	}
	// close connect socket
	close(sd);

	printf("From Server: %s\n", buf);

	return 0;
}
