/*
* Arduino Wireless Communication Tutorial
*     Example 2 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
//#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>



RF24 radio(7, 8); // CE, CSN
const byte addresses[6] = "00001";
Servo servoGas;
int servoStuur = 10; 

 int angleStuur = 0;
 int angleGas = 0;
 int pwm; 

void setup() {
  Serial.begin(9600);
  Serial.print("wollah");
  servoGas.attach(9);
  pinMode(servoStuur, OUTPUT); 
  radio.begin();
  radio.openReadingPipe(0, addresses); // 00001
  radio.setPALevel(RF24_PA_HIGH);
  
}

void loop() {
  
  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      
      radio.read(&angleGas, sizeof(angleGas));
      servoGas.write(angleGas);

      //radio.read(&angleStuur, sizeof(angleStuur));
      servoPulse(servoStuur, (radio.read(&angleStuur, sizeof(angleStuur))/68.256).toInt);
      

      Serial.println(angleGas);
      Serial.print("     ");
      Serial.println(angleStuur);
      delay(5);
      }
    }

    void servoPulse (int servo, int waarde){
      int waarde = radio.read(&angleStuur, sizeof(angleStuur))/68.256;
      pwm = map(waarde,0,15,1200,1800);
      digitalWrite(servo, HIGH);
      delayMicroseconds(pwm);
      digitalWrite(servo, LOW); 
      delay(10); 
    }
    
  }
