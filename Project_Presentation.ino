#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
void turnright(int x);
void comeback();
unsigned long time_now = 0;
unsigned long time_final = 0;
int period = 3800;

 
#define LED 13
#define FORWARD_SPEED  200
#define STOP_SPEED  0
 
// this might need to be tuned for different lighting conditions, surfaces, etc.
//#define QTR_THRESHOLD  600 // microseconds  old one
//#define QTR_THRESHOLD  500 ca bloque au niveau des intervalles entre les carreaux
//#define QTR_THRESHOLD  400  walk but dont detect the white band later 
//

#define QTR_THRESHOLD  360
#define QTR_THRESHOLD_TWO  2000
  
// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     200
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms
 
ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
 
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

void waitForButtonAndCountDown()
{
  digitalWrite(LED, HIGH);
  button.waitForButton();
  digitalWrite(LED, LOW);
   
  // play audible countdown
  for (int i = 0; i < 3; i++)
  {
    delay(1000);
    buzzer.playNote(NOTE_G(3), 200, 15);
  }
  delay(1000);
  buzzer.playNote(NOTE_G(4), 500, 15);  
  delay(1000);
}
 
void setup()
{
  // uncomment if necessary to correct motor directions
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true);
   
  pinMode(LED, HIGH);
   
  waitForButtonAndCountDown();
}

void loop()
{
  if (button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }

   sensors.read(sensor_values);
   
   //Serial.println(sensor_values[0]); 
  if (sensor_values[0] >= QTR_THRESHOLD_TWO)
  {
    /* if leftmost sensor detects line, reverse and turn to the right
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED); */
    //motors.setSpeeds(STOP_SPEED, STOP_SPEED);
    // comeback();

   motors.setSpeeds(-FORWARD_SPEED, -FORWARD_SPEED);   
    delay(100);   
   for (int speed = 0; speed >= -400; speed--)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(-speed);
    delay(2);
  }

    
  }
  else if (sensor_values[5] >= QTR_THRESHOLD_TWO )
  {
    /* if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED); */
    //motors.setSpeeds(STOP_SPEED, STOP_SPEED);
   //comeback();

   motors.setSpeeds(-FORWARD_SPEED, -FORWARD_SPEED);   
    delay(100);   
   for (int speed = 0; speed >= -400; speed--)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(-speed);
    delay(2);
  }

  
   
  }
   
  else
  {
    // otherwise, go straight
    time_now = time_now + millis();
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);

    

    
    sensors.read(sensor_values);
 // Serial.println(sensor_values[0]); 
   
  }
}


void turnright(int x){
digitalWrite(7, HIGH);
digitalWrite(8, LOW);
analogWrite(9,x);
analogWrite(10,x);

}

void comeback()
{
   turnright(90);
   delay(1000);
   turnright(90);
   delay(1000);



int i;
   
   for(i = 0; i < time_now ; i++)
   {
      // This turns the robot back and forth by 
      // switching the motors direction every 20 iterations
      if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      {
         motors.setSpeeds(180, 180);
      }
      else
      {
         motors.setSpeeds(180, 180);
      }
      // Since our counter runs to 80, the total delay 
      // will be 80*20 = 1600 ms.
      delay(5);
   }
   
   motors.setSpeeds(0,0);
}
