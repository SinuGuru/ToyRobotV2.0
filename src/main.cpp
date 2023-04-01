#include <Arduino.h>
#include <PCF8574.h>
#include "MyStepper.h"
#include "MyMultiStepp.h"

// this is my code how to run two steppers synchronized 

PCF8574 pcf(0x20);

MyStepper leftMot(pcf,4098,0,2,1,3);
MyStepper rigthMot(pcf,4098,4,6,5,7);

MyMultiStepp motors;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  delay(1000);
  Serial.print("Init pcf8574...");
	if (pcf.begin()){
		Serial.println("OK");
	}else{
		Serial.println("KO");
	}
 
 leftMot.setMaxSpeed(600);
 rigthMot.setMaxSpeed(600);

 motors.addStepper(leftMot);
 motors.addStepper(rigthMot);



}

void loop() {
  // put your main code here, to run repeatedly:

  // leftMot.moveTo(500);
  // rigthMot.moveTo(500);

  long dist[2];
  dist[0]=1024;
  dist[1]=-1024;

  motors.moveTo(dist);
  motors.runSpeedToPosition();
  Serial.print("Left motor =");
  Serial.println(leftMot.currentPosition());
  Serial.print("Right motor =");
  Serial.println(rigthMot.currentPosition());

  delay(1000);
   
  dist[0]=-1024;
  dist[1]=1024;

  motors.moveTo(dist);
  motors.runSpeedToPosition();
  Serial.print("Left motor =");
  Serial.println(leftMot.currentPosition());
  Serial.print("Right motor =");
  Serial.println(rigthMot.currentPosition());
  delay(1000);


}