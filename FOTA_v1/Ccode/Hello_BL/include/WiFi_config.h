

#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

// Define your WiFi network credentials
#define WIFI_SSID         "Mo"        // Replace with your network name
#define WIFI_PASSWORD     "12345678"    // Replace with your network password

// Define server connection details
#define WIFI_PROTOCOL     "TCP"
#define WIFI_PORT         "80"
#define WIFI_IP           "128.204.223.111"

// Define AT command settings
#define WIFI_ECHO_STATE                   "ATE0\r\n"
#define WIFI_NODE_MODE                    "AT+CWMODE=1\r\n"
#define WIFI_DisConnect                   "AT+CWQAP\r\n"
#define WIFI_ProcessHexRequest      "GET http://mohamedbakr.serv00.net/ProcessHex.php\r\n"
#define WIFI_RecordRequest         "GET http://mohamedbakr.serv00.net/Record.txt\r\n"

#endif /* WIFI_CONFIG_H */
