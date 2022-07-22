#include <Arduino.h>
#include "time_Driver.h"

// creating a accelstepper object. Passing the Driver, stepPin and dirPin as parameter.
// IMPORTANT: You can define a motorInterfaceType and use enums or just use ints. It is not recommended to do so! Pass the Driver value or others like demonstrated here.
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);
DFRobot_QMC5883 compass(&Wire, /*I2C addr*/ HMC5883L_ADDRESS);
struct tm timeInfo;
sVector_t mag;
int state;
/*
-------------------------------------------------------------------------------------------------------------------------------------------
 _____ _                 ______                _   _
|_   _(_)                |  ___|              | | (_)
  | |  _ _ __ ___   ___  | |_ _   _ _ __   ___| |_ _  ___  _ __  ___
  | | | | '_ ` _ \ / _ \ |  _| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
  | | | | | | | | |  __/ | | | |_| | | | | (__| |_| | (_) | | | \__ \
  \_/ |_|_| |_| |_|\___| \_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|___/
-------------------------------------------------------------------------------------------------------------------------------------------
*/
// initializing the time, passing the server name as parameter, kinda messy might change.
void init_Time(const char *server)
{
    // built in function that takes the timezone as paramater as well as the server.
    // IMPORTANT: Change timezone based on YOUR location.
    configTzTime("MST7", server);
    delay(7000);
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

/*
-------------------------------------------------------------------------------------------------------------------------------------------
___  ___      _              ______                _   _
|  \/  |     | |             |  ___|              | | (_)
| .  . | ___ | |_ ___  _ __  | |_ _   _ _ __   ___| |_ _  ___  _ __  ___
| |\/| |/ _ \| __/ _ \| '__| |  _| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
| |  | | (_) | || (_) | |    | | | |_| | | | | (__| |_| | (_) | | | \__ \
\_|  |_/\___/ \__\___/|_|    \_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|___/
-------------------------------------------------------------------------------------------------------------------------------------------
*/

void move_Motor_Clockwise()
{
    // loop runs as long as the position of motor is not equal to 400 steps
    // while (stepper.currentPosition() != 100)
    // {
    //     // IMPORTANT: DO NOT move setSpeed into the motor_Setup function. This will create an infinite loop.

    //     // setting the speed to 400.
    //     stepper.setSpeed(250);
    //     // makes motor run based on speed.
    //     stepper.runSpeed();
    // }
    stepper.moveTo(100);
    stepper.runToPosition();
}

void move_Motor_CounterClockwise()
{
    // // loops as long as the position is not equal to 0
    // while (stepper.currentPosition() != 0)
    // {
    //     // sets the speed to -400 this indicates to move counter clock wise.
    //     stepper.setSpeed(-250);
    //     // runs the motor
    //     stepper.runSpeed();
    // }
    stepper.moveTo(0);
    stepper.runToPosition();
}

// motor setup function
void motor_Setup()
{
    stepper.setCurrentPosition(0);
    // sets the max speed of stepper to 1000.
    stepper.setMaxSpeed(200);
    stepper.setAcceleration(230);
}

void logic_Motor()
{

    // storing value from photoPin inside a variable
    int lightLevels = analogRead(photoPin);
    Serial.println(lightLevels);

    if (mag.HeadingDegress >= 245 && mag.HeadingDegress <= 290 || mag.HeadingDegress >= 68 && mag.HeadingDegress <= 110)
    {
        if (timeInfo.tm_hour >= 18 && timeInfo.tm_hour <= 23 || timeInfo.tm_hour >= 5 && timeInfo.tm_hour <= 10)
        {
            move_Motor_Clockwise();
        }
    }
    else
    {
        move_Motor_CounterClockwise();
    }

    // night 18 - 23  and day 5 - 10 mag.HeadingDegress >= 245 && mag.HeadingDegress <= 290 || mag.HeadingDegress >= 68 && mag.HeadingDegress <= 110
}
/*
-------------------------------------------------------------------------------------------------------------------------------------------
 _____                                      ______                _   _
/  __ \                                     |  ___|              | | (_)
| /  \/ ___  _ __ ___  _ __   __ _ ___ ___  | |_ _   _ _ __   ___| |_ _  ___  _ __  ___
| |    / _ \| '_ ` _ \| '_ \ / _` / __/ __| |  _| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
| \__/\ (_) | | | | | | |_) | (_| \__ \__ \ | | | |_| | | | | (__| |_| | (_) | | | \__ \
 \____/\___/|_| |_| |_| .__/ \__,_|___/___/ \_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|___/
                      | |
                      |_|
-------------------------------------------------------------------------------------------------------------------------------------------
*/

void compass_Logic()
{
    while (!compass.begin())
    {
        Serial.println("Could not find a valid 5883 sensor, check wiring!");
        delay(500);
    }
    if (compass.isHMC())
    {
        Serial.println("Initialize QMC5883");
        compass.setRange(HMC5883L_RANGE_1_3GA);
        // Serial.print("compass range is:");
        // Serial.println(compass.getRange());

        compass.setMeasurementMode(HMC5883L_CONTINOUS);
        // Serial.print("compass measurement mode is:");
        // Serial.println(compass.getMeasurementMode());

        compass.setDataRate(HMC5883L_DATARATE_15HZ);
        // Serial.print("compass data rate is:");
        // Serial.println(compass.getDataRate());

        compass.setSamples(HMC5883L_SAMPLES_8);
        // Serial.print("compass samples is:");
        // Serial.println(compass.getSamples());
    }
    delay(1000);
    Serial.print("Completed");
}

void compass_Whatever()
{
    float declinationAngle = (9.0 + (55.0 / 60.0)) / (180 / PI);
    compass.setDeclinationAngle(declinationAngle);
    mag = compass.readRaw();
    compass.getHeadingDegrees();
    Serial.print("Degress = ");
    Serial.println(mag.HeadingDegress);
    delay(100);
}