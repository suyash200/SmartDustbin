/*
 * HC-SR04 example sketch
 *
 * https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
 *
 * by Isaac100
 */
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;

const int trigPin = 8;
const int echoPin = 9;
const int sensor_pin = A0;
const int buzzer = 5;
float duration, distance;
float moisture_percentage;
int sensor_analog;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  myservo.attach(10);
  
}

void loop() {
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = (100 - ((sensor_analog / 1023.00) * 100));
  Serial.print(moisture_percentage);
//  if(moisture_percentage <97){
//   myservo.write(0);
//     delay(15);  
//  }
  // for (pos = 0; pos <= 90; pos += 1) {  // goes from 0 degrees to 180 degrees
  //     // in steps of 1 degree
  //     myservo.write(pos);  // tell servo to go to position in variable 'pos'
  //     delay(15);           // waits 15ms for the servo to reach the position
  //   }
  if (moisture_percentage < 85) {
    
    Serial.println("dry");

    for (pos = 0; pos <= 90; pos += 1) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);  // tell servo to go to position in variable 'pos'
      delay(15);           // waits 15ms for the servo to reach the position
    }
   
  
  } else {
    
    // analogWrite(10, 1000);
     for (pos = 180; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
    Serial.println("wet");
  }
  pinMode(3, HIGH);
  pinMode(12, LOW);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;
 
  if (distance <= 5) {
    Serial.println(distance);
    tone(buzzer, 1000);
  
     // Wait for 30 millisecond(s)

  } else {
    Serial.println(distance);
    noTone(buzzer);
     
  }




  delay(200);
}