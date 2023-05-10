# DendoStepper

Work in progress, maybe unstable. Opening issues is more than welcome.  
This library takes care of pulse generating for stepper motor drivers with STEP/DIR interface. Pulse generating utilizes general purpose timers to achieve some usable accuracy and smoothness.  
Currently supports only linear acceleration and deceleration.

### Known limitations
- maximum number of controlled stepper motors is 4, this is limited by number of general purpose timers
- If the motor is moving, it is not possible to move it to another direction.

## Usage

```c++
typedef struct
{
    uint8_t stepPin;           /** step signal pin */
    uint8_t dirPin;            /** dir signal pin */
    uint8_t enPin;             /** enable signal pin */
    timer_group_t timer_group; /** timer group, useful if we are controlling more than 2 steppers */
    timer_idx_t timer_idx;     /** timer index, useful if we are controlling 2steppers */
    microStepping_t miStep;    /** microstepping configured on driver - used in distance calculation */
    float stepAngle;           /** one step angle in degrees (usually 1.8deg), used in steps per rotation calculation */
} DendoStepper_config_t;

enum microStepping_t
{
    MICROSTEP_1 = 0x1,
    MICROSTEP_2,
    MICROSTEP_4 = 0x4,
    MICROSTEP_8 = 0x8,
    MICROSTEP_16 = 0x10,
    MICROSTEP_32 = 0x20,
    MICROSTEP_64 = 0x40,
    MICROSTEP_128 = 0x80,
    MICROSTEP_256 = 0x100,
};

```  
Configuration struct, can be allocated on stack or heap.

```c++
void init();
```  
Initializes GPIO and Timer peripherals, registers ISR. Expects populated config struct is alreay passed to the class using config()  

```c++
void config(DendoStepper_config_t* config);
```
Configures the class as per passed config struct pointer.  

```c++
void setStepsPerMm(uint16_t steps);
uint16_t getStepsPerMm();
```
Sets or gets steps needed to move one millimiter, useful if stepper is moving along linear axis.  

```c++
void setSpeed(uint16_t speed,uint16_t accT, uint16_t decT);
uint16_t getSpeed();
float getAcc();
```
Sets maximum speed in steps per second, acceleration and deceleration time in milliseconds.  
Gets speed in steps per second  
Gets acceleration in steps per second per second

```c++
void setSpeedMm(uint16_t speed,uint16_t accT, uint16_t decT);
```
Sets maximum speed in mm/s, acceleration and deceleration time in milliseconds. Expects already defined steps per millimeter with setStepsPerMm()  

```c++
void runPos(int32_t relative);
```
Runs motor to position relative from current position in steps, respecting constraints set with setSpeed()  

```c++
void runPosMm(int32_t relative);
```
Runs motor to position relative from current position in millimeters, respecting constraints set with setSpeed()  
Expects already defined steps per millimeter with setStepsPerMm()  

```c++
 bool runAbsolute(uint32_t position);
```
Runs motor in absolute coordinate plane. Unit: steps (should be constrained with home switch)  

```c++
 bool runAbsoluteMm(uint32_t position);
```
Runs motor in absolute coordinate plane. Unit: millimeters (should be constrained with home switch)  
Expects already defined steps per millimeter with setStepsPerMm()  

```c++
 bool runInf(bool direction);
```
Runs motor infintely in desired direction with constrains set using setSpeed().  

```c++
void disableMotor();
void enableMotor();
```
Disables and enables motor via EN pin

```c++
uint8_t getState();

enum motor_status{
    DISABLED,
    IDLE,
    ACC,
    COAST,
    DEC,
};
```
Returns current state of motor, return type is enum motor_status  


```c++
void resetAbsolute();
```
Resets absolute position to 0. Called for ex. when endswitch is hit.  

```c++
void getPosition();
```
Gets current position in absolute coordinate plane in steps.  

```c++
void getPositionMm();
```
Gets current position in absolute coordinate plane in millimeters.  
Expects already defined steps per millimeter with setStepsPerMm()  

```c++
void stop();
```
Stops the motor dead on the spot. No deceleration is performed this way. Eg. e-stop.  


