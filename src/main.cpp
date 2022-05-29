// basic includes
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
}

void loop()
{

  // Uncomment if you would like to have the time printed to see what is going on!
  // print_Time();
  // calling the logic motor function
  logic_Motor();
}
