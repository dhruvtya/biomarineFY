#include <Servo.h> 

//(2,15)(1,5)(1,15) CONTROL PARAMETERS
int rotSpeed = 2, rotDelay = 15;
int rotSpeedLeft = 1,rotDelayLeft = 10;
int rotSpeedRight = -1,rotDelayRight = 10;
int medianAngle = 90;
int amplitude=60;
int maxAngle = medianAngle + (amplitude/2),minAngle = medianAngle - (amplitude/2);
int servoLeft[3]={3,6,10};
int servoRight[3]={5,9,11};
int startPosLeft[3] = {100,90,80};
int startPosRight[3] = {80,90,100};
const bool finSideLeft = 0, finSideRight = 1;
//

class servoClass
{
  Servo servo;
  int pos;
  int increment;
  int updateInterval;
  unsigned long lastUpdate; 
public: 
  servoClass(int startPos, int finSide)
  {
    pos = startPos;
    if(finSide == 0)
    {
      updateInterval = rotDelayLeft;
      increment = rotSpeedLeft;
    }
    else
    {
      updateInterval = rotDelayRight;
      increment = rotSpeedRight;
    }
  }
  void Attach(int pin)
  {
    servo.attach(pin);
    servo.write(pos);
    delay(5);
  }
  void Update()
  {
    if((millis() - lastUpdate) > updateInterval)
    {
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      if ((pos >= maxAngle) || (pos <= minAngle))
      {
        increment = -increment;
      }
    }
  }
};

//LEFT OBJECTS
servoClass serObjectL0(startPosLeft[0],finSideLeft);
servoClass serObjectL1(startPosLeft[1],finSideLeft);
servoClass serObjectL2(startPosLeft[2],finSideLeft);

//RIGHT OBJECTS
servoClass serObjectR0(startPosRight[0],finSideRight);
servoClass serObjectR1(startPosRight[1],finSideRight);
servoClass serObjectR2(startPosRight[2],finSideRight);

 
void setup() 
{ 
  //LEFT ATTACHMENT
  serObjectL0.Attach(servoLeft[0]);
  serObjectL1.Attach(servoLeft[1]);
  serObjectL2.Attach(servoLeft[2]);

  //RIGHT ATTACHMENT
  serObjectR0.Attach(servoRight[0]);
  serObjectR1.Attach(servoRight[1]);
  serObjectR2.Attach(servoRight[2]);
} 
void loop() 
{ 
  serObjectL0.Update();
  serObjectR0.Update();
  
  serObjectL1.Update();
  serObjectR1.Update();
  
  serObjectL2.Update();
  serObjectR2.Update();
}
