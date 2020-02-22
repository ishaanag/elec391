int prevState,currState,windCount, sens1flag,sens2flag;
int prevState_1,currState_1,windCount_1;
int LED = 0;
double volts = 5.0/1023;
double angle,angle_1;




/*Author: Brandon Bwanakocha
 * Purpose: Detects a positive edge
 * parameters: pointers to state bits
*/

int posedge(int* prevState, int* currState){

  if(*prevState ^ *currState){
    *prevState = *currState;
    if(*currState == HIGH){

      return 1;
      }
    }
  return 0;
  }





void setup() {
// start with previous state given by the thing.

  prevState = analogRead(A5)*volts > 4.0 ? HIGH: LOW; 
  prevState_1 = analogRead(A4)*volts > 4.0 ? HIGH: LOW;
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  windCount = 0;
  windCount_1 = 0;

}

void loop() {
  // put your main code here, to run repeatedly:
  currState = analogRead(A5)*volts> 4.0 ? HIGH: LOW;
  currState_1 = analogRead(A4)*volts> 4.0 ? HIGH: LOW;

  // check for posedge
  
  sens1flag = posedge(&prevState,&currState);
  sens2flag = posedge(&prevState_1,&currState_1);

  
 // digitalWrite(LED, posedge(&prevState,&currState)? HIGH: LOW);
  windCount = sens1flag ? windCount + 1: windCount;
  windCount_1 = sens2flag ? windCount_1 + 1: windCount_1;
  angle = windCount * 3.6;
  angle_1 = windCount_1 * 3.6;


 Serial.print(angle);
 Serial.print("   ");
 Serial.print(angle_1);
 Serial.print("\n");

}
