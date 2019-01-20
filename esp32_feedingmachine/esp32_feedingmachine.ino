#include <Stepper.h>
 
const int stepsPerRevolution = 2050; // change this to fit the number of steps per revolution
 
// initialize the stepper library on pins 15,2,0,4
Stepper myStepper(stepsPerRevolution, 16,21,17,22); 

int stepCount = 0; // number of steps the motor has taken
 
void setup() {
 myStepper.setSpeed(14);
}
 
void loop() {
// step one step:
vibrate(3);
myStepper.step(-500);
vibrate(3);
myStepper.step(1000);
delay(5000);
}

void vibrate(int times)
{
  for(int i;i<times;i++) 
  {
    myStepper.step(-35);
    delay(10);
    myStepper.step(35);
    delay(10);
  }
}

