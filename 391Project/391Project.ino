#include <Stepper.h>

#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11
#define Kp 100
#define Ki 0.0005



int windCount = 0;
int Direction = 2;
int prevState [2];
int Integral = 0;
int currState[2];
int LED = 12;
double volts = 5.0/1023;
double angle,angle_1;


int sens1prev, sens1time, sens1prevtime;
int sens2prev,sens2time, sens2prevtime;
int stepCount = 0;
const int stepsPerRevolution = 200;

int pinA = 2;
int pinB = 3;
int step_number = 0;
bool wheel_dir = false;
int motorSpeed = 100;

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);




//========================================================================================================================================
// DETECTING A RISING EDGE
// =======================================================================================================================================
int posedge(int prev, int curr){

  if(prev ^ curr){
    if(curr == HIGH){

      return 1;
      }
    }
  return 0;
  }
// =============================================================================================
// Getting the Angle
// =============================================================================================
double getAngle(int dir){
  if(dir > 1)
   return windCount*3.6;
   
  windCount = dir ? windCount + 1: windCount-1;
  
  return windCount * 3.6;
  }
//=============================================================================================================
// SENSOR DIRECTION
//================================================================================================================

  
int sensorDirec(int* prev,int* curr){
// finite state machine
// Values producing positive direction
if((prev[0] == 0 && prev[1] == 0) && (curr[0] == 1 && curr[1] == 0))
 return 1;
if((prev[0] == 1 && prev[1] == 0) && (curr[0] == 1 && curr[1] == 1))
 return 1;
if((prev[0] == 1 && prev[1] == 1) && (curr[0] == 0 && curr[1] == 1))
 return 1;
if((prev[0] == 0 && prev[1] == 1) && (curr[0] == 0 && curr[1] == 0))
 return 1;

// values producing negative direction

 if((prev[0] == 0 && prev[1] == 0) && (curr[0] == 0 && curr[1] == 1))
 return 0;
 if((prev[0] == 0 && prev[1] == 1) && (curr[0] == 1 && curr[1] == 1))
 return 0;
 if((prev[0] == 1 && prev[1] == 1) && (curr[0] == 1 && curr[1] == 0))
 return 0;
 if((prev[0] == 1 && prev[1] == 0) && (curr[0] == 0 && curr[1] == 0))
 return 0;

 return 2;
  }
//==============================================================================================================================
// Interrupt Service Routine
//==============================================================================================================================
  void ISR_(){
  currState[0] = digitalRead(pinA);
  currState[1] = digitalRead(pinB);


    
    Direction = sensorDirec(prevState, currState);
   if(posedge(prevState[0], currState[0])){
    angle = getAngle(Direction);
    }
    prevState[0] = currState[0];
    prevState[1] = currState[1];
 
 Serial.print(abs(angle));
 Serial.print("     ");
 Serial.print(Direction ? "Forward" : "Backward");
 Serial.print("\n");
    }
//========================================================================================================================================
// FORWARD STEP
//========================================================================================================================================
void forward(int speed_inv){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
} 

step_number++;
  if(step_number > 3)
    step_number = 0;
delay(speed_inv);
}


//===============================================================================================================================================
// BACKWARD STEP
//===============================================================================================================================================

void backward(int speed_inv){
  switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
} 
  step_number++;
  if(step_number > 3)
    step_number = 0;
  delay(speed_inv);
  }
//===============================================================================================================================================================
// SETUP FUNCTION
//===============================================================================================================================================================

//===============================================================================================================================================================
// PID CONTROL
//===============================================================================================================================================================

int K_Control(int targ_angle){ 
  return Kp * abs(abs(angle) - abs(targ_angle));                  // K variable control
  }

int I_Control(int targ_angle){
  Integral = Integral + abs(targ_angle - abs(angle));
  return Ki*Integral;
  }


void setup() {
// start with previous state given by the thing.



  pinMode(pinA,INPUT);
  pinMode(pinB,INPUT);

  
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);

  
  attachInterrupt(digitalPinToInterrupt(pinA),ISR_,CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB),ISR_,CHANGE);
  prevState[0] = digitalRead(pinA);
  prevState[1] = digitalRead(pinB);
  Serial.begin(9600);

  pinMode(LED,OUTPUT);
/*
  cli();//stop interrupts

//set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
sei();

*/

interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:
  
if(abs(angle)<= 90){
 
  backward(100-K_Control(180)/18000.0*100 + I_Control(180));
  
// Serial.print(K_Control(90));
 //Serial.print("\n");
  }




}
