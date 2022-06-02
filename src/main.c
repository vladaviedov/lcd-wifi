#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define SSID_LENGTH 32

void on_intr(int signum);

int main() {
	signal(SIGINT, &on_intr);
	signal(SIGQUIT, &on_intr);
	signal(SIGTERM, &on_intr);

	return 0;
}

void on_intr(int signum) {
	exit(signum);
}
