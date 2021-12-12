
// hidden_config.h includes the two function
// getSSIDName() and getSSIDPassword() 
// which return my wifi name and the wifi password
//You will need to create this file manually and add these two functions to it.
#include "hidden_config.h"

const char *gHostName = "esp32UDPServer";
unsigned int gUdpPort = 1234;
