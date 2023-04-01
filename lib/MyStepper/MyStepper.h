#include <PCF8574.h>

/// @brief 
class MyStepper
{


protected:
     typedef enum
    {
	DIRECTION_CCW = 0,  ///< Counter-Clockwise
        DIRECTION_CW  = 1   ///< Clockwise
    } Direction;
    /// The current interval between steps in microseconds.
    /// 0 means the motor is currently stopped with _speed == 0
    unsigned long  _stepInterval;
    /// The last step time in microseconds
    unsigned long  _lastStepTime;
    boolean _direction; // 1 == CW
    virtual void    setOutputPins(uint8_t mask);

private:
    /* data */
    u_int8_t        _pin[4]; 

    u_int8_t        _steps;
    /// The step counter for speed calculations
     /// Whether the _pins is inverted or not
    uint8_t        _pinInverted[4];
    long _n;
    /// The current absolution position in steps.
    long           _currentPos;    // Steps
    /// The maximum permitted speed in steps per second. Must be > 0.
    float          _maxSpeed;
    /// Min step size in microseconds based on maxSpeed
    float           _cmin; // at max speed
    /// The target position in steps. The AccelStepper library will move the
    long           _targetPos;     // Steps
    /// The current motos speed in steps per second
    /// Positive is clockwise
    float          _speed;         // Steps per second

    PCF8574* stepperExpander;


public:

     MyStepper(PCF8574 &stepPass,long steps,int pin1, int pin2, int pin3, int pin4);
    ~MyStepper();


    long    currentPosition(); 
    void    setMaxSpeed(float speed);
    float   maxSpeed();
    void    moveTo(int posToMove);
    void    setCurrentPosition(long position);  
    long    stepForward();
    long    distanceToGo();
    bool    runSpeed();
    void    setSpeed(float speed);
     /// If the enable Pin is defined, sets it to OUTPUT mode and sets the pin to enabled.
    virtual void    enableOutputs();
    virtual void    step(long step);
   
};

