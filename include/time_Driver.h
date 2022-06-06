#pragma once
// Includes
#include <Arduino.h>
#include <time.h>
#include <AccelStepper.h>
#include <DFRobot_QMC5883.h>
// int variables that are based on Pins
const int stepPin = 12;  // REPLACE VALUE based on pin layout
const int dirPin = 14;   // REPLACE VALUE based on pin layout
const int photoPin = 34; // REPLACE VALUE based on pin layout

// function prototypes
void motor_Setup();
void logic_Motor();

void init_Time(const char *server);
void print_Time();

void compass_Logic();
void compass_Whatever();