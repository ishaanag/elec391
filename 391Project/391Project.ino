int windCount, Direction;
int prevState [2];
int currState[2];
int LED = 0;
double volts = 5.0/1023;
double angle,angle_1;

int sens1prev, sens1time, sens1prevtime;
int sens2prev,sens2time, sens2prevtime;


/*Author: Brandon Bwanakocha
 * Purpose: Detects a positive edge
 * parameters: pointers to state bits
*/

int posedge(int prev, int curr){

  if(prev ^ curr){
    if(curr == HIGH){

      return 1;
      }
    }
  return 0;
  }

double getAngle(int dir){
  if(dir > 1)
   return windCount*3.6;
   
  windCount = dir ? windCount + 1: windCount-1;
  
  return windCount * 3.6;
  }
  
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




void setup() {
// start with previous state given by the thing.

  prevState[0] = analogRead(A5)*volts > 4.0 ? HIGH: LOW; 
  prevState[1] = analogRead(A4)*volts > 4.0 ? HIGH: LOW;

  pinMode(LED, OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  Serial.begin(9600);
  windCount = 0;
  Direction = 2;


}

void loop() {
  // put your main code here, to run repeatedly:
  currState[0] = analogRead(A5)*volts> 4.0 ? HIGH: LOW;
  currState[1] = analogRead(A4)*volts> 4.0 ? HIGH: LOW;


    
    Direction = sensorDirec(prevState, currState);
   if(posedge(prevState[0], currState[0])){
    angle = getAngle(Direction);
    }
    prevState[0] = currState[0];
    prevState[1] = currState[1];
    


    
  

 Serial.print(angle);
 Serial.print("     ");
 Serial.print(Direction);
 Serial.print("\n");


}
