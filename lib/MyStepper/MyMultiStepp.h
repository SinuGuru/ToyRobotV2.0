#include <Arduino.h>


#define MULTISTEPPER_MAX_STEPPERS 3

class MyStepper;

class MyMultiStepp
{
private:

    MyStepper*    _steppers[MULTISTEPPER_MAX_STEPPERS];
    uint8_t       _num_steppers;

public:

    MyMultiStepp(/* args */);
    ~MyMultiStepp();
    boolean addStepper(MyStepper& stepper);
    void moveTo(long moveTo[]);
    void runSpeedToPosition();
    boolean run();

};

