#ifndef WIFI_PRIVATE_H
#define WIFI_PRIVATE_H

#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"


// AT command definitions
#define READY               "AT\r\n"
#define RESET               "AT+RST\r\n"
#define STATIONMODE         "AT+CWMODE=1\r\n"
#define ACCESSPOINTMODE     "AT+CWMODE=2\r\n"
#define DISABLE_ECHO        "ATE0\r\n"
#define ENABLE_ECHO         "ATE1\r\n"
#define INTERNET_CONNECT    "AT+CWJAP_CUR=\""
#define SERVER_CONNECT      "AT+CIPSTART=\""
#define CHAR_NUM            "AT+CIPSEND="
#define ENTER_COMMAND       "\r\n"
#define GET                 "GET "

// Timeout settings
#define ECHO_TIMEOUT        100
#define NODE_MODE_TIMEOUT   150
#define CONNECT_TIMEOUT     10000
#define SERVER_TIMEOUT      10000
#define PREREQUEST_TIMEOUT  5000
#define REQUEST_TIMEOUT     10000

// Private function prototypes
u8 AsciToHex(u8 Copy_u8Ascii);

#endif /* WIFI_PRIVATE_H */
