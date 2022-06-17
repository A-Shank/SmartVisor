// Includes the Arduino.h files as well as all our other headerfiles that are needed.
#include <Arduino.h>
#include "wifiDefinition.h"
#include "wifiVariables.h"
#include "time_Driver.h"

void setup()
{
  // Starting on Serial 115200
  Serial.begin(115200);

  // calling the wifi function with paramaters such as name of network and password.
  start_Wifi(name_of_network, password);
  // calling init time function and passing server as paramter
  init_Time(ntpServer);
  // calling motor init function
  motor_Setup();
  compass_Logic();
}

void loop()
{

  // Uncomment if you would like to have the time printed to see what is going on!
  print_Time();
  compass_Whatever();
  // calling the logic motor function
  logic_Motor();
}
