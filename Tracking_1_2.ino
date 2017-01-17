/*
Arduino code for controlling X and Y servos.
This code serves the purpose of 'tracking'
an IR target, and positions its brackets to
get the best picture.

The code first reads the values of all sensors.
Then, if the sensors have a high enough reading,
the differences between the values are taken and
the net direction of motion is calculated. If the
difference between two sensors is large, the servo
will move a more significant distance. This repeats
until the servo reacehs a position where it is able
to lock onto the IR target.
*/

#include <Servo.h> 

#define MAX_ANGLE 180

#define SENSOR1_PIN A0
#define SENSOR2_PIN A1

#define SPEED 100

#define SENSOR_THRESHOLD 200

Servo servox;
Servo servoy;
 
int posx = 0;
int posy = 0;

int deltax = 0;

int offsetx = 0;

int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int sensor4 = 0;

float sensor1v = 0;
float sensor2v = 0;

int plot_flag = 500;

int time1 = 0;
int time2 = 0;
//int deltat = 0;

int flag_counter = 20;
 
void setup() 
{ 
  servox.attach(9);
  
  Serial.begin(9600);
} 
 
void loop() 
{ 
  sensor1 = analogRead(SENSOR1_PIN);
  sensor2 = analogRead(SENSOR2_PIN);
  
  if(sensor1 >= SENSOR_THRESHOLD || sensor2 >= SENSOR_THRESHOLD || sensor3 >= SENSOR_THRESHOLD || sensor4 >= SENSOR_THRESHOLD)
  {
    offsetx = (sensor1 - sensor2)/SPEED;
    
    sensor1v = (float)sensor1*5.0/1023.0;
    sensor2v = (float)sensor2*5.0/1023.0;
    
    posx = constrain(posx + offsetx, 0, MAX_ANGLE);
  
    servox.write(posx);
   
   time2 = millis();
   
   if(time2 - time1 >= 500 && flag_counter > 0)
   {
     Serial.print(sensor1v);
     Serial.print("   ");
     Serial.print(sensor2v);
     Serial.print("   ");
     Serial.print(offsetx);
     Serial.print("   ");
     Serial.println(posx);
     
     flag_counter--;
   }
   
   else if (flag_counter == 0)
   {
     time1 = time2;
     
     Serial.println("------------------------------------");
     
     flag_counter = 20;
   }
  } 
} 
