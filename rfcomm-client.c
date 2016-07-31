#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main(int argc, char **argv) {
	struct sockaddr_rc addr = { 0 };
	int sock, status;
	char dest[18] = "5C:F3:70:75:C1:27";
	char message[1000];

	// allocate socket
	sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	// set the connection parameters
	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = (uint8_t) 1;
	str2ba(dest, &addr.rc_bdaddr);

	// connect to server
	status = connect(sock, (struct sockaddr *)&addr, sizeof(addr));

	if (status < 0) {
		perror("yeah no");
		return 0;
	}

	// send a message
	printf("Message: ");
	fgets(message, 1000, stdin);
	while (status >= 0) {
		status = write(sock, message, strlen(message));
		printf("Message: ");
		fgets(message, 1000, stdin);
	}

	close(sock);
	return 0;
}
