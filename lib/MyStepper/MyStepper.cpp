#include "MyStepper.h"

long MyStepper::currentPosition()
{
    return _currentPos;
}

void MyStepper::setMaxSpeed(float speed)
{
     if (speed < 0.0)
       speed = -speed;
    if (_maxSpeed != speed)
    {
	_maxSpeed = speed;
	_cmin = 1000000.0 / speed;

	// Recompute _n from current speed and adjust speed if accelerating or cruising

	// if (_n > 0)
	// {
	//     // _n = (long)((_speed * _speed) / (2.0 * _acceleration)); // Equation 16
	//     // computeNewSpeed();
	// }

    }

}

float MyStepper::maxSpeed()
{
    return _maxSpeed;
}

MyStepper::MyStepper(PCF8574 &stepPass, long steps, int pin1, int pin2, int pin3, int pin4)
{
    
    _currentPos = 0;
    _maxSpeed = 0.0;
    _n = 0;
    _cmin = 1.0;
    _targetPos = 0;


    _pin[0]=pin1;
    _pin[1]=pin2;
    _pin[2]=pin3;
    _pin[3]=pin4;
    _steps=steps;

    stepperExpander = &stepPass;

    setMaxSpeed(1);
    enableOutputs();

}

MyStepper::~MyStepper()
{
}

void MyStepper::moveTo(int posToMove)
{
     if (_targetPos != posToMove)
    {
	_targetPos = posToMove;
	//computeNewSpeed();
	// compute new n?
    }
    
}

void MyStepper::setCurrentPosition(long position)
{
    _targetPos = _currentPos = position;
    _n = 0;
    _stepInterval = 0;
    _speed = 0.0;

}

long MyStepper::stepForward()
{
     // Clockwise
    _currentPos += 1;
	//step(_currentPos);
	_lastStepTime = micros();
    return _currentPos;
}

long MyStepper::distanceToGo()
{
     return _targetPos - _currentPos;
}

void MyStepper::setOutputPins(uint8_t mask)
{
   

	uint8_t numpins = 4;
    uint8_t i;
    for (i = 0; i < numpins; i++)
    stepperExpander->digitalWrite(_pin[i], (mask & (1 << i)) ? (HIGH ^ _pinInverted[i]) : (LOW ^ _pinInverted[i]));
}

bool MyStepper::runSpeed()
{
     // Dont do anything unless we actually have a step interval
    

    if (!_stepInterval)
	return false;

    unsigned long time = micros();   
    if (time - _lastStepTime >= _stepInterval)
    {
	if (_direction == DIRECTION_CW)
	{
	    // Clockwise
	    _currentPos += 1;
	}
	else
	{
	    // Anticlockwise  
	    _currentPos -= 1;
	}
	step(_currentPos);

	_lastStepTime = time; // Caution: does not account for costs in step()

	return true;
    }
    else
    {
	return false;
    }
}

void MyStepper::setSpeed(float speed)
{
    if (speed == _speed)
        return;
    speed = constrain(speed, -_maxSpeed, _maxSpeed);
    if (speed == 0.0)
	_stepInterval = 0;
    else
    {
	_stepInterval = fabs(1000000.0 / speed);
	_direction = (speed > 0.0) ? DIRECTION_CW : DIRECTION_CCW;
    }
    _speed = speed;
}

void MyStepper::enableOutputs()
{
    stepperExpander->pinMode(_pin[0], OUTPUT);
    stepperExpander->pinMode(_pin[1], OUTPUT);
    stepperExpander->pinMode(_pin[2], OUTPUT);
    stepperExpander->pinMode(_pin[3], OUTPUT);
}

void MyStepper::step(long step)
{
   // Serial.println(step);

    switch (step & 0x3)
    {
	case 0:    // 1010
	    setOutputPins(0b0101);
	    break;

	case 1:    // 0110
	    setOutputPins(0b0110);
	    break;

	case 2:    //0101
	    setOutputPins(0b1010);
	    break;

	case 3:    //1001
	    setOutputPins(0b1001);
	    break;
    }

}
