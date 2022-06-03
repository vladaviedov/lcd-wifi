#ifndef LCD_WIFI_NETWORK_H
#define LCD_WIFI_NETWORK_H

#include <stddef.h>

#define SSID_LENGTH (32 + 1)

int nw_is_connected(void);
int nw_get_networks(char **list, int max_count);
int nw_connect(char *ssid);
int nw_get_ip(char *ip, size_t buf_size);
int nw_disconnect(void);

#endif // LCD_WIFI_NETWORK_H
