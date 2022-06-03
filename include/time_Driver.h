#pragma once
// Includes
#include <Arduino.h>
#include <time.h>
#include <AccelStepper.h>

// int variables that are based on Pins
const int stepPin = 12;  // REPLACE VALUE based on pin layout
const int dirPin = 14;   // REPLACE VALUE based on pin layout
const int photoPin = 34; // REPLACE VALUE based on pin layout
struct tm timeInfo;      // time struct
// function prototypes
void motor_Setup();
void logic_Motor();

void init_Time(const char *server);
void print_Time();
