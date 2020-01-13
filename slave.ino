#include <Servo.h>
// Pinii motor 1
#define mpin00 5
#define mpin01 6
// Pinii motor 2
#define mpin10 3
#define mpin11 11
Servo srv;
// Includem biblioteca necesară pentru I2C
#include <Wire.h>
int x = 0;
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;
int state = 0;
int potValue = 0;

void setup() {
 
  digitalWrite(mpin00, 0);
 digitalWrite(mpin01, 0);
 digitalWrite(mpin10, 0);
 digitalWrite(mpin11, 0);
 pinMode (mpin00, OUTPUT);
 pinMode (mpin01, OUTPUT);
 pinMode (mpin10, OUTPUT);
 pinMode (mpin11, OUTPUT);
 // pin LED
 pinMode(13, OUTPUT);

 
 // Pornim busul I2C ca și slave la adresa 9

 
 Wire.begin(9);
 // Atașăm o funcție care să se declanșeze atunci când primim
 //ceva
 Wire.onReceive(receiveEvent);
 Serial.begin(9600);
}
//trimte serial 0 cand e oprit sau 1 contrar
void receiveEvent(int bytes) {
 x = Wire.read(); // citim un caracter din I2C
}


void StartMotor (int m1, int m2, int forward, int speed)
{

 if (speed==0) // oprire
 {
 digitalWrite(m1, 0); 
 digitalWrite(m2, 0);
 }
 else
 {
 if (forward)
 {
 digitalWrite(m2, 0);
 analogWrite (m1, speed); // folosire PWM
 }
 else
 {
 digitalWrite(m1, 0);
 analogWrite(m2, speed);
 }
 }
}

void delayStopped(int ms)
{
 StartMotor (mpin00, mpin01, 0, 0);
 StartMotor (mpin10, mpin11, 0, 0);
 delay(ms);
} 


void loop() {

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);


Wire.beginTransmission(9);
Wire.write(distance);
Wire.endTransmission();
  

 Serial.print(x);
 if(x==0)
 {
 StartMotor (mpin00, mpin01, 0, 0);
 StartMotor (mpin10, mpin11, 0, 0);
 delay(500);
 }
 if(x==1)
 {

 StartMotor (mpin00, mpin01, 0, 128);
 StartMotor (mpin10, mpin11, 0, 128);
 delay (500);
 }

 if(x==2)
 {
 StartMotor (mpin00, mpin01, 1, 128);
 StartMotor (mpin10, mpin11, 0, 128);
 delay (1500);
 x=1;
 }

 if(x==3)
 {
 StartMotor (mpin00, mpin01, 0, 128);
 StartMotor (mpin10, mpin11, 1, 128);
 delay (1500);
x=1;
 }
}
