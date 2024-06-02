//implement song
//mess with delayTime
//playTone
//comments
//implement penalty?

#include <Adafruit_CircuitPlayground.h>

volatile int switchFlag, button4Flag, button5Flag;
bool leftButtonPressed, rightButtonPressed;
int i, ii; 
int delayTime;
int randPixel = random(0, 10);
int score = 0;
int modeCounter = 1;
int count = 0;

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(4), button4Pressed, RISING); 
  attachInterrupt(digitalPinToInterrupt(5), button5Pressed, RISING);
  attachInterrupt(digitalPinToInterrupt(7), switchFlipped, CHANGE);
  //while(!Serial);

}

void loop() {
  leftButtonPressed = CircuitPlayground.leftButton();
  rightButtonPressed = CircuitPlayground.rightButton();

  if(switchFlag)
  {
    CircuitPlayground.clearPixels();
    score = 0;
    switch(modeCounter)
    {
      case 1: 
      delayTime = 200;
      ++count;
      if(count <= 1)
      {
      Serial.println("Choose gamemode: 1. Faster");
      }
      break;

      case 2: 
      delayTime = 25;
      ++count;
      if(count <= 1)
      {
      Serial.println("Choose gamemode: 2. Slower");
      }
      break;

      case 3:
      delayTime = 50;
      ++count;
      if(count <= 1)
      {
        Serial.println("Choose gamemode: 3. Song");
      }
      break;

      case 4: 
      delayTime = random(25, 200);   
      ++count;
      if(count <= 1)
      {
        Serial.println("Choose gamemode: 4. Random"); 
      }
      break;
    }

    if(button5Flag)
    {
      modeCounter++;
      
      if(modeCounter > 4)
      {
        modeCounter = 1;
      }

      count = 0;
      button5Flag = 0;
    }

    if(button4Flag)
    {
      modeCounter--;

      if(modeCounter < 1)
      {
        modeCounter = 4;
      }
      
      count = 0;
      button4Flag = 0;
    }
  }

  if(switchFlag == 0)
  {
    CircuitPlayground.setPixelColor(randPixel, 0, 155, 0); 

    for(i = 0; i < 10; i++)
    {
      CircuitPlayground.setPixelColor(i, 0, 155, 0);

      if(i + 1 >= 9)
      {
        int ii = 0;
        CircuitPlayground.setPixelColor(ii, 0, 155, 0);
        CircuitPlayground.setPixelColor(ii + 1, 0, 155, 0);
      }
      else
      {
        CircuitPlayground.setPixelColor(i + 1, 0, 155, 0);
        CircuitPlayground.setPixelColor(i + 2, 0, 155, 0);
      }
      if(leftButtonPressed || rightButtonPressed)
      {
        if(i == randPixel)
        {
          Serial.println(++score);
          randPixel = random(0, 10);
          switch(modeCounter)
          {
            case 1: 
            delayTime = delayTime / 2;
            break;
            
            case 2: 
            delayTime = delayTime * 2;
            break;

            case 3:
            delayTime = delayTime + 10;
            break;

            case 4:
            delayTime = random(25, 200);
            break;
          }
          break;
        }
      }

      delay(delayTime);

      for (int j = 0; j < 10; j++) 
      {
        if (j != randPixel) 
        {
          CircuitPlayground.setPixelColor(j, 0, 0, 0);
        }
      }
    }
  }
  
}

void switchFlipped()
{
  if(switchFlag == 1)
  {
    switchFlag = 0;
  }
  else
  {
    switchFlag = 1;
  }
}

void button4Pressed()
{
  button4Flag = 1;
}

void button5Pressed()
{
  button5Flag = 1;
}
