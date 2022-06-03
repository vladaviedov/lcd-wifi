#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "network.h"

void on_intr(int signum);

int main() {
	signal(SIGINT, &on_intr);
	signal(SIGQUIT, &on_intr);
	signal(SIGTERM, &on_intr);

	char *networks[16];
	for (int i = 0; i < 16; i++) {
		networks[i] = malloc(sizeof(char) * SSID_LENGTH);
	}

	char ipbuf[32];

	while (1) {
		if (nw_is_connected()) {
			nw_get_ip(ipbuf, 32);
			printf("%s", ipbuf);
		} else {
			int nets = nw_get_networks(networks, 16);
			int i = 0;
			while (1) {
				printf("%s\n", networks[i]);

				int ch = getchar();
				getchar();
				if (ch == 'a') {
					nw_connect(networks[i]);
					break;
				}
				if (ch == 'b') {
					i++;
					if (i == nets) i = 0;
				}
			}
		}

		int ch = getchar();
		if (ch == 'd') {
			nw_disconnect();
		}
		if (ch == 'q') {
			break;
		}
	}

	return 0;
}

void on_intr(int signum) {
	exit(signum);
}
