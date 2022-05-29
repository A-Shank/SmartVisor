#include <Arduino.h>
#include "time_Driver.h"
#include "timeStruct.h"

// creating a accelstepper object. Passing the Driver, stepPin and dirPin as parameter.
// IMPORTANT: You can define a motorInterfaceType and use enums or just use ints. It is not recommended to do so! Pass the Driver value or others like demonstrated here.
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

// initializing the time, passing the server name as parameter, kinda messy might change.
void init_Time(const char *server)
{
    // built in function that takes the timezone as paramater as well as the server.
    // IMPORTANT: Change timezone based on YOUR location.
    configTzTime("MST7", server);
    // If conditions checks if it is able to get the local time out of the timeinfo struct. If not it will return an error.
    if (!getLocalTime(&timeInfo))
    {
        // Prints error
        Serial.println("Failed to obtain time");
        return;
    }
}

void print_Time()
{
    // If conditions checks if it is able to get the local time out of the timeinfo struct. If not it will return an error.
    if (!getLocalTime(&timeInfo))
    {
        Serial.println("Failed to obtain time!");
        return;
    }
    // Prints the time.
    Serial.println(&timeInfo, "%A, %B %d %Y %H:%M:%S zone %Z %z ");
}

void move_Motor_Clockwise()
{
    // loop runs as long as the position of motor is not equal to 400 steps
    while (stepper.currentPosition() != 400)
    {
        // IMPORTANT: DO NOT move setSpeed into the motor_Setup function. This will create an infinite loop.

        // setting the speed to 400.
        stepper.setSpeed(400);
        // makes motor run based on speed.
        stepper.runSpeed();
    }
}

void move_Motor_CounterClockwise()
{
    // loops as long as the position is not equal to 0
    while (stepper.currentPosition() != 0)
    {
        // sets the speed to -400 this indicates to move counter clock wise.
        stepper.setSpeed(-400);
        // runs the motor
        stepper.runSpeed();
    }
}

// motor setup function
void motor_Setup()
{
    // sets the max speed of stepper to 1000.
    stepper.setMaxSpeed(1000);
}

void logic_Motor()
{
    // storing value from photoPin inside a variable
    int lightLevels = analogRead(photoPin);
    // if checks if the time is greater or equal to 17 or 5pm in 12 hour format and checks for the lightlevels of the photo sensor
    if (timeInfo.tm_hour >= 17 && lightLevels >= 2000)
    {
        move_Motor_Clockwise();
    }
    // Else comes in effect if the time is not greater or equal to 17 which means 5 pm in 12 hour format and the lightlevels are less than 2000
    else
    {
        move_Motor_CounterClockwise();
    }
}
