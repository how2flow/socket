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
	struct socketaddr_in sin, cli;
	int sd; // binding socket => listen socket
	int ns; // connect socket
	int clientlen = sizeof(cli);

	if ((sd = socket(AF_INET, SOCK_STEAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT); // (short)HBO -> (short)NBO
	sin.sin_addr.s_addr = inet_addr("192.168.0.180");

	if (bind(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("listen");
		exit(1);
	}

	if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1) {
		perror("accept");
		exit(1);
	}

	sprintf(buf, "IP addr:%s", inet_ntoa(cli.sin_addr));
	if (send(ns, buf, strlen(buf)+1, 0) == -1) {
		perror("send");
		exit(1);
	}
	// close connect socket
	close(ns);
	// close listen socket
	close(sd);

	return 0;
}
