#include "wifiDefinition.h"

// wifi function which takes wifi name and password as parameter both parameters are char pointers, like that we do not have to pass strings.
void start_Wifi(const char *wifi_Name, const char *password_N)
{
    // Prints statement
    Serial.print("Connecting to ");
    // Prints wifi name
    Serial.println(wifi_Name);
    // starts the wifi chip and looks for the passed parameters which are the name and password of the wifi.
    WiFi.begin(wifi_Name, password_N);
    // Loop runs as long as the status of the wifi is not connected.
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");
}