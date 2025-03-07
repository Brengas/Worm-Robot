// This is the code for the worm movement, it is esentially a sin type signal that is translated
//into angles for the servo, the main sinusoidal has an amplitud of 60 degrees, with a 0.02 Hz frecuency
// this values can be modified if the worm needs to be move faster or do bigger steps 

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const float pi = 3.14159267;
const float frec = 0.02;
const float amplitud = 60;



 float grados(float radianes) {
  return radianes / 2 / pi * 360;
}

//It's important put the right I2C adress of your own driver

Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);

//int pos0 = 110;
//int pos180 = 512;
int pos0 = 110;
int pos180 = 512;
int t=0;
int f=0;

void setup(){
  //Initialize PCA9658 Driver
  servos.begin();
  Serial.begin(115200);
  servos.setPWMFreq(50);
  // Set all the servos at 90 degrees, the worm is completely in a straight position
  setServo(1,90);
  delay(500);
  setServo(2,90);
  delay(500);
  setServo(3,90);
  delay(500);
  setServo(4,90);
  delay(500);
  setServo(0,90);
  delay(500);
}

void loop(){
  
  Serial.println("Cycle starts");
// The worm movement is coceived as a sinusoidal signal which travels arround the body worm
// in order to achieve that, there is a pure sin which moves the first joint, then
// the rest of the joints move following that first signal, but with a certain wave offset

  for(int i = 1; i < 1000; i++){
    float f0 = amplitud*sin(2*pi*frec*i)+90;
    float f1 = amplitud*sin(2*pi*frec*i+pi+(pi/8))+90;
    float f2 = amplitud*sin(2*pi*frec*i+((1/4)*pi))+90;
    float f3 = amplitud*sin(2*pi*frec*i+(pi+(pi/2)))+90;
    float f4 = 80*sin(2*pi*frec*i+(pi+((3/4)*pi)))+90;
   
   /* This is for debugging
    Serial.print(f0);
    Serial.println("\t");
    Serial.print(f1);
    Serial.println("\t");
    Serial.print(f2);
    Serial.println("\t");
    Serial.print(f3);
    Serial.println("\t");
    Serial.print(f4);
    Serial.println("\t");
    //Serial.println(i);
    //setServo(7,f0);
    */
    //After the corresponding angles for each joint, they are sent to the servos
    //Make sure to put the right number
    setServo(0,f0);
    setServo(1,f1);
    setServo(2,f2);
    setServo(3,f3);
    setServo(4,f4);
    
    delay(0.5);
  }
 Serial.println("End of the cycle");
}


//This is the function used for the servo movement using the PCA9685 Driver
void setServo(uint8_t n_servo, int angulo){
  int duty;
  duty = map(angulo,0,180,pos0,pos180);
  servos.setPWM(n_servo,0,duty);
}


