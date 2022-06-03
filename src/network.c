#include "network.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADAPTER "wlan0"
#define BUF_SIZE 128

#define STATUS "nmcli -g GENERAL.STATE device show " ADAPTER
#define SCAN "nmcli -g SSID device wifi list"
#define IP "nmcli -g IP4.ADDRESS device show " ADAPTER
#define CONNECT "nmcli device wifi connect %s"
#define DISCONNECT "nmcli device disconnect " ADAPTER

int pclose_exit_code(FILE *pipe);

int nw_is_connected(void) {
	FILE *res = popen(STATUS, "r");
	if (res == NULL) {
		return -1;
	}

	char buf[BUF_SIZE];
	fread(buf, sizeof(char), BUF_SIZE, res);
	if (ferror(res)) {
		return -1;
	}

	pclose(res);
	int code = strtol(buf, NULL, 10);
	return code == 100;
}

int nw_get_networks(char **list, int max_count) {
	FILE *res = popen(SCAN, "r");
	if (res == NULL) {
		return -1;
	}

	char buf[SSID_LENGTH];
	int count = 0;

	while (count < max_count && fgets(buf, SSID_LENGTH, res) != NULL) {
		char *nl = strchr(buf, '\n');
		*nl = '\0';

		if (*buf == '\0') continue;

		strncpy(*(list + count), buf, SSID_LENGTH);
		count++;
	}

	pclose(res);
	return count;
}

int nw_connect(char *ssid) {
	char buf[BUF_SIZE];
	snprintf(buf, BUF_SIZE, CONNECT, ssid);

	FILE* res = popen(buf, "r");
	if (res == NULL) {
		return -1;
	}

	fread(buf, sizeof(char), BUF_SIZE, res);
	if (ferror(res)) {
		return -1;
	}

	return pclose_exit_code(res);
}

int nw_get_ip(char *ip, size_t buf_size) {
	FILE *res = popen(IP, "r");
	if (res == NULL) {
		return -1;
	}

	fread(ip, sizeof(char), buf_size, res);	
	if (ferror(res)) {
		return -1;
	}

	pclose(res);
	return 0;
}

int nw_disconnect(void) {
	FILE *res = popen(DISCONNECT, "r");
	if (res == NULL) {
		return -1;
	}

	char buf[BUF_SIZE];
	fread(buf, sizeof(char), BUF_SIZE, res);
	if (ferror(res)) {
		return -1;
	}

	return pclose_exit_code(res);
}

int pclose_exit_code(FILE *pipe) {
	int ret = pclose(pipe);
	if (!WIFEXITED(ret)) {
		return -1;
	}

	return WEXITSTATUS(ret);
}
