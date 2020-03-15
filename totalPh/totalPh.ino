float ph;  //True value of PH
int acidMotor = 10; //Motor for Acid
int baseMotor  = 21; // Motor for Base
const int adc = A0;  //controlling motor speed 

int Motor = 12; // motor for stirring  cnct in PWM value 
//..............................................
#define SensorPin A1            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;
//................................................


void setup() {
  // put your setup code here, to run once:
  pinMode(Motor,OUTPUT);
  pinMode(acidMotor,OUTPUT);
  pinMode(baseMotor,OUTPUT);
  Serial.begin(9600);
  Serial.println("Hi... Welcome !");
  delay(500);
  Serial.println("Enter your values wants to set ");
  Serial.println("Enter PH value : ");
  setPh();
  Serial.println("Set your POT value to stirring ");
  delay(3000);
  adc = analogRead(adc);
  adc = map(adc, 0, 1023, 0, 255);  
  analogWrite(Motor,adc) ;
  delay(10000);
}
void loop(){

  readPh();
  if(pHvalue>ph){
    digitalWrite(acidMotor , HIGH);
    delay(100);
    digitalWrite(acidMotor , LOW);    
  }
  
}

void readPh(){
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval){
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
 /* if(millis() - printTime > printInterval){   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  
    Serial.print("Voltage:");
    Serial.print(voltage,2);
    Serial.print("    pH value: ");
    Serial.println(pHValue,2);
    digitalWrite(LED,digitalRead(LED)^1);
    printTime=millis();*/
  }
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}

void setPh(){
   while(Serial.available()){
   ph = Serial.read();
   if(isDigit(ph) != 1){
    Serial.println("You are entered wrong value.. \n pls enter a true value ");
   }
   else if((ph>=1) && (ph<=14)){
    Serial.println(ph);
    Serial.print(" is fixed");
   }
   else{
    Serial.println(" you are enetred a wrong ph value \n Enter a value between 1 and 14");
   }
  }
}
