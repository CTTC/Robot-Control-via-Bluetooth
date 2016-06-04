String inputString = "";         // a string to hold incoming data
String temp="";
boolean stringComplete = false;  // whether the string is complete
int length;
unsigned int MQ_2_sensorvalue=0;
int pos =90;
float dis[3];
int angle[3]={30,90,150};
boolean DistanceFlag=false;
boolean HumanFlag=false;
boolean SmogFlag=false;
#include<Servo.h>
Servo myservo;
#define BackLeft_EN 4    
#define BackRight_EN 5   
#define FrontLeft_EN 6
#define FrontRight_EN 7
#define ArmA_EN 8
#define ArmB_EN 9
#define ArmC_EN 10   
#define LED 13
#define BackLeft_IN1 22 
#define BackLeft_IN2 23
#define BackRight_IN1 24
#define BackRight_IN2 25
#define FrontLeft_IN1 26
#define FrontLeft_IN2 27
#define FrontRight_IN1 28
#define FrontRight_IN2 29
#define ArmA_IN1 30
#define ArmA_IN2 31 
#define ArmB_IN1 32
#define ArmB_IN2 33 
#define ArmC_IN1 34
#define ArmC_IN2 35
#define HumanDetect 36  //Detect human
#define Tonepin 37    // Play music
#define TrigPin 38   //  Measure distance via ultrasound
#define EchoPin 39
#define MQ_2_sensor_DO 40 //This pin is used for sensor that detects smog
#define ActiveBuzzer 41
#define MQ_2_sensor_AO A1 //This pin is used for sensor that detects smog

// Make the buzzer play music
#define NTD0 -1
#define NTD1 294
#define NTD2 330
#define NTD3 350
#define NTD4 393
#define NTD5 441
#define NTD6 495
#define NTD7 556
#define NTDL1 147
#define NTDL2 165
#define NTDL3 175
#define NTDL4 196
#define NTDL5 221
#define NTDL6 248
#define NTDL7 278
#define NTDH1 589
#define NTDH2 661
#define NTDH3 700
#define NTDH4 786
#define NTDH5 882
#define NTDH6 990
#define NTDH7 112
//列出全部D调的频率
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625
//列出所有节拍
int tune[]=                 //根据简谱列出各频率
{
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD3,NTD2,NTD2,
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD2,NTD1,NTD1,
  NTD2,NTD2,NTD3,NTD1,
  NTD2,NTD3,NTD4,NTD3,NTD1,
  NTD2,NTD3,NTD4,NTD3,NTD2,
  NTD1,NTD2,NTDL5,NTD0,
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD4,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD2,NTD1,NTD1
};
float durt[]=                   //根据简谱列出各节拍
{
  1,1,1,1,
  1,1,1,1,
  1,1,1,1,
  1+0.5,0.5,1+1,
  1,1,1,1,
  1,1,1,1,
  1,1,1,1,
  1+0.5,0.5,1+1,
  1,1,1,1,
  1,0.5,0.5,1,1,
  1,0.5,0.5,1,1,
  1,1,1,1,
  1,1,1,1,
  1,1,1,0.5,0.5,
  1,1,1,1,
  1+0.5,0.5,1+1,
};
void setup() 
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(BackLeft_EN,OUTPUT);
  pinMode(BackRight_EN,OUTPUT);
  pinMode(FrontLeft_EN,OUTPUT);
  pinMode(FrontRight_EN,OUTPUT);
  pinMode(ArmA_EN,OUTPUT);
  pinMode(ArmB_EN,OUTPUT);
  pinMode(ArmC_EN,OUTPUT);
  pinMode(BackLeft_IN1,OUTPUT);
  pinMode(BackLeft_IN2,OUTPUT);
  pinMode(BackRight_IN1,OUTPUT);
  pinMode(BackRight_IN2,OUTPUT);
  pinMode(FrontLeft_IN1,OUTPUT);
  pinMode(FrontLeft_IN2,OUTPUT);
  pinMode(FrontRight_IN1,OUTPUT);
  pinMode(FrontRight_IN2,OUTPUT);
  pinMode(ArmA_IN1,OUTPUT);
  pinMode(ArmA_IN2,OUTPUT);
  pinMode(ArmB_IN1,OUTPUT);
  pinMode(ArmB_IN2,OUTPUT);
  pinMode(ArmC_IN1,OUTPUT);
  pinMode(ArmC_IN2,OUTPUT);
  pinMode(HumanDetect,INPUT);
  pinMode(Tonepin,OUTPUT);
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  pinMode(MQ_2_sensor_DO,INPUT);
  pinMode(ActiveBuzzer,OUTPUT);
  pinMode(MQ_2_sensor_AO,INPUT);
  pinMode(LED,OUTPUT);
  
  digitalWrite(BackLeft_EN,HIGH);
  digitalWrite(BackRight_EN,HIGH);
  digitalWrite(FrontLeft_EN,HIGH);
  digitalWrite(FrontRight_EN,HIGH);
  digitalWrite(ArmA_EN,HIGH);
  digitalWrite(ArmB_EN,HIGH);
  digitalWrite(ArmC_EN,HIGH);
  digitalWrite(BackLeft_IN1,HIGH);
  digitalWrite(BackLeft_IN2,HIGH);
  digitalWrite(BackRight_IN1,HIGH);
  digitalWrite(BackRight_IN2,HIGH);
  digitalWrite(FrontLeft_IN1,HIGH);
  digitalWrite(FrontLeft_IN2,HIGH);
  digitalWrite(FrontRight_IN1,HIGH);
  digitalWrite(FrontRight_IN2,HIGH);
  digitalWrite(ArmA_IN1,HIGH);
  digitalWrite(ArmA_IN2,HIGH);
  digitalWrite(ArmB_IN1,HIGH);
  digitalWrite(ArmB_IN2,HIGH);
  digitalWrite(ArmC_IN1,HIGH);
  digitalWrite(ArmC_IN2,HIGH);  
  digitalWrite(HumanDetect,LOW); 
  digitalWrite(Tonepin,LOW); 
  digitalWrite(MQ_2_sensor_DO,HIGH);  
  digitalWrite(ActiveBuzzer,LOW);
  myservo.attach(42);
  myservo.write(pos);
  length=sizeof(tune)/sizeof(tune[0]);   //计算长度
  inputString.reserve(200);
  Serial.println("Welcome to use! My name is SIMER. Enjoy your time!");
}
//When input the command code from the phone or computer, do not forget to press the “enter"button in the end.
void loop() 
{
  DetectHuman();
  DetectSmog();
  AutomaticTurn();  
}
void serialEvent()
{
  while (Serial.available()) {
    char inChar = (char)Serial.read();   // get the new byte
    inputString += inChar;                 // add it to the inputString
                   // if the incoming character is a newline, set a flag
                   // so the main loop can do something about it:
    if (inChar == '\n') 
    {
      stringComplete = true;
    }  
    if (stringComplete) 
    {
      if (inputString=="mas\r\n")
      {
          MainTracksAdvance(90);   //Main tracks advance in small speed
          Serial.println("Main tracks advance in small speed");
      }     
      else if (inputString=="mam\r\n")
      {
          MainTracksAdvance(150);   //Main tracks advance in medium speed
          Serial.println("Main tracks advance in medium speed");
      } 
      else if (inputString=="mal\r\n")
      {
        Serial.println("Main tracks advance in large speed");
        MainTracksAdvance(250);   //Main tracks advance in large speed
      } 
      else if (inputString=="was\r\n")
      {
        Serial.println("Whole tracks advance in small speed");  
        WholeTracksAdvance(90);   //Whole tracks advance in small speed
      } 
      else if (inputString=="wam\r\n")
      {
        Serial.println("Whole tracks advance in medium speed");  
        WholeTracksAdvance(150);   //Whole tracks advance in medium speed
      } 
      else if (inputString=="wal\r\n")
      {
        Serial.println("Whole tracks advance in large speed");  
        WholeTracksAdvance(250);   //Whole tracks advance in large speed
      } 
      else if (inputString=="mrs\r\n")
      {
        Serial.println("Main tracks reverse in small speed");    
        MainTracksReverse(90);   //Main tracks reverse in small speed
      } 
      else if (inputString=="mrm\r\n")
      {
        Serial.println("Main tracks reverse in medium speed"); 
        MainTracksReverse(150);   //Main tracks reverse in medium speed
      }
     else if (inputString=="mrl\r\n")
      {
        Serial.println("Main tracks reverse in large speed");   
        MainTracksReverse(250);   //Main tracks reverse in large speed
      }  
      else if (inputString=="wrs\r\n")
      {
        Serial.println("Whole tracks reverse in small speed");   
        WholeTracksReverse(80);   //Whole tracks reverse in small speed
      } 
      else if (inputString=="wrm\r\n")
      {
        Serial.println("Whole tracks reverse in medium speed");  
        WholeTracksReverse(150);   //Whole tracks reverse in medium speed
      } 
      else if (inputString=="wrl\r\n")
      {
        Serial.println("Whole tracks reverse in large speed");   
        WholeTracksReverse(250);   //Whole tracks reverse in large speed
      } 
      else if (inputString=="ms\r\n")
      {
        Serial.println("Main tracks stop");  
        MainTracksStop();   //Main tracks stop
      } 
      else if (inputString=="ws\r\n")
      {
        Serial.println("Whole tracks stop");   
        WholeTracksStop();   //Whole tracks stop
      }
      else if (inputString=="ml\r\n")
      {
        Serial.println("Main tracks turn left"); 
        MainTracksTurnLeft(250);   //Main tracks turn left
      }
      else if (inputString=="mr\r\n")
      {
        Serial.println("Main tracks turn right"); 
        MainTracksTurnRight(250);   //Main tracks turn right
      }
      else if (inputString=="wl\r\n")
      {
        Serial.println("Whole tracks turn left");   
        WholeTracksTurnLeft(250);   //Whole tracks turn left
      }
      else if (inputString=="wr\r\n")
      {
        Serial.println("Whole tracks turn right");     
        WholeTracksTurnRight(250);   //Whole tracks turn right
      }
      else if (inputString=="aau\r\n")
      {
        Serial.println("Arm A rotates up");  
        ArmARotatesUp(180);   //Arm A rotates up
      }
      else if (inputString=="aad\r\n")
      {
        Serial.println("Arm A rotates down");  
        ArmARotatesDown(180);   //Arm A rotates down
      }
      else if (inputString=="abu\r\n")
      {
        Serial.println("Arm B rotates up");    
        ArmBRotatesUp(180);   //Arm B rotates up
      }
      else if (inputString=="abd\r\n")
      {
        Serial.println("Arm B rotates down");   
        ArmBRotatesDown(180);   //Arm B rotates down
      }
      else if (inputString=="acu\r\n")
      {
        Serial.println("Arm C rotates up");  
        ArmCRotatesUp(180);   //Arm C rotates up
      }
      else if (inputString=="acd\r\n")
      {
        Serial.println("Arm C rotates down");   
        ArmCRotatesDown(180);   //Arm C rotates down
      }
      else if (inputString=="aas\r\n")
      {
        Serial.println("Arm A Stops");     
        ArmAStops();       //Arm A Stops
      }
      else if (inputString=="abs\r\n")
      {
        Serial.println("Arm B Stops");   
        ArmBStops();       //Arm B Stops
      }
      else if (inputString=="acs\r\n")
      {
        Serial.println("Arm C Stops");     
        ArmCStops();       //Arm C Stops
      }
      else if (inputString=="uon\r\n") // Turn on the ultrasound mode
      {        
         Serial.println("Turn on the ultrasound mode"); 
         DistanceFlag=true;
      }
      else if (inputString=="uoff\r\n")//Turn off the ultrasound mode
      {
        Serial.println("Turn off the ultrasound mode");
        DistanceFlag=false;        
      }
      else if (inputString=="hon\r\n")// Enter human detect mode
      {
        HumanFlag=true;
        Serial.println("Turn on the human-detect mode"); 
      }
      else if (inputString=="hoff\r\n")// Leave human detect mode
      {
        HumanFlag=false;
        noTone(Tonepin);
        digitalWrite(Tonepin,LOW);
        Serial.println("Turn off the human-detect mode"); 
      }
      else if (inputString=="son\r\n")// Enter smog detect mode
      {
        SmogFlag=true;
        Serial.println("Turn on the smog-detect mode"); 
      }
      else if (inputString=="soff\r\n")// Enter smog detect mode
      {
        SmogFlag=false;
        Serial.println("Turn off the smog-detect mode"); 
        digitalWrite(ActiveBuzzer,LOW);
      }        
      else
      {
        stringComplete=false;
        inputString="";
        Serial.println("Invalid Command!");
        return;
      }
      inputString="";
      stringComplete = false;
    }   
  }
}
void MainTracksAdvance(int x)
{ 
  analogWrite(BackLeft_EN,x);
  analogWrite(BackRight_EN,x);
  digitalWrite(BackLeft_IN1,LOW);
  digitalWrite(BackLeft_IN2,HIGH);
  digitalWrite(BackRight_IN1,LOW);
  digitalWrite(BackRight_IN2,HIGH);
}
void WholeTracksAdvance(int x)
{ analogWrite(BackLeft_EN,x);
  analogWrite(BackRight_EN,x);
  analogWrite(FrontLeft_EN,x);
  analogWrite(FrontRight_EN,x);
  digitalWrite(BackLeft_IN1,LOW);
  digitalWrite(BackLeft_IN2,HIGH);
  digitalWrite(BackRight_IN1,LOW);
  digitalWrite(BackRight_IN2,HIGH);
  digitalWrite(FrontLeft_IN1,LOW);
  digitalWrite(FrontLeft_IN2,HIGH);
  digitalWrite(FrontRight_IN1,LOW);
  digitalWrite(FrontRight_IN2,HIGH);
}
void MainTracksReverse(int x)
{ 
  analogWrite(BackLeft_EN,x);
  analogWrite(BackRight_EN,x);
  digitalWrite(BackLeft_IN1,HIGH);
  digitalWrite(BackLeft_IN2,LOW);
  digitalWrite(BackRight_IN1,HIGH);
  digitalWrite(BackRight_IN2,LOW);
}
void WholeTracksReverse(int x)
{ analogWrite(BackLeft_EN,x);
  analogWrite(BackRight_EN,x);
  analogWrite(FrontLeft_EN,x);
  analogWrite(FrontRight_EN,x);
  digitalWrite(BackLeft_IN1,HIGH);
  digitalWrite(BackLeft_IN2,LOW);
  digitalWrite(BackRight_IN1,HIGH);
  digitalWrite(BackRight_IN2,LOW);
  digitalWrite(FrontLeft_IN1,HIGH);
  digitalWrite(FrontLeft_IN2,LOW);
  digitalWrite(FrontRight_IN1,HIGH);
  digitalWrite(FrontRight_IN2,LOW);
}
void MainTracksTurnLeft(int x)
{
  analogWrite(BackLeft_EN,x);
  analogWrite(BackRight_EN,x);
  digitalWrite(BackLeft_IN1,HIGH);
  digitalWrite(BackLeft_IN2,LOW);
  digitalWrite(BackRight_IN1,LOW);
  digitalWrite(BackRight_IN2,HIGH);
}
void MainTracksTurnRight(int x)
{
  analogWrite(BackLeft_EN,x);
  analogWrite(BackRight_EN,x);
  digitalWrite(BackLeft_IN1,LOW);
  digitalWrite(BackLeft_IN2,HIGH);
  digitalWrite(BackRight_IN1,HIGH);
  digitalWrite(BackRight_IN2,LOW);
}
void WholeTracksTurnLeft(int x)
{
  if(x<=80) x=80;
  analogWrite(BackLeft_EN,x-80);
  analogWrite(BackRight_EN,x);
  analogWrite(FrontLeft_EN,x-80);
  analogWrite(FrontRight_EN,x);
  digitalWrite(BackLeft_IN1,LOW);
  digitalWrite(BackLeft_IN2,HIGH);
  digitalWrite(BackRight_IN1,LOW);
  digitalWrite(BackRight_IN2,HIGH);
  digitalWrite(FrontLeft_IN1,LOW);
  digitalWrite(FrontLeft_IN2,HIGH);
  digitalWrite(FrontRight_IN1,LOW);
  digitalWrite(FrontRight_IN2,HIGH);
}
void WholeTracksTurnRight(int x)
{
  if(x<=80) x=80;
  analogWrite(BackLeft_EN,x);
  analogWrite(BackRight_EN,x-80);
  analogWrite(FrontLeft_EN,x);
  analogWrite(FrontRight_EN,x-80);
  digitalWrite(BackLeft_IN1,LOW);
  digitalWrite(BackLeft_IN2,HIGH);
  digitalWrite(BackRight_IN1,LOW);
  digitalWrite(BackRight_IN2,HIGH);
  digitalWrite(FrontLeft_IN1,LOW);
  digitalWrite(FrontLeft_IN2,HIGH);
  digitalWrite(FrontRight_IN1,LOW);
  digitalWrite(FrontRight_IN2,HIGH);
}
void MainTracksStop()
{ digitalWrite(BackLeft_IN1,HIGH);
  digitalWrite(BackLeft_IN2,HIGH);
  digitalWrite(BackRight_IN1,HIGH);
  digitalWrite(BackRight_IN2,HIGH);
}
void WholeTracksStop()
{ digitalWrite(BackLeft_IN1,HIGH);
  digitalWrite(BackLeft_IN2,HIGH);
  digitalWrite(BackRight_IN1,HIGH);
  digitalWrite(BackRight_IN2,HIGH);
  digitalWrite(FrontLeft_IN1,HIGH);
  digitalWrite(FrontLeft_IN2,HIGH);
  digitalWrite(FrontRight_IN1,HIGH);
  digitalWrite(FrontRight_IN2,HIGH);
}
void ArmARotatesUp(int x)
{
 analogWrite(ArmA_EN,x);
 digitalWrite(ArmA_IN1,LOW);
 digitalWrite(ArmA_IN2,HIGH);
 digitalWrite(ArmB_IN1,HIGH);  //To avoid interference, I stop the 
                                    // other arms when one arm is rotating
 digitalWrite(ArmB_IN2,HIGH);
 digitalWrite(ArmC_IN1,HIGH);
 digitalWrite(ArmC_IN2,HIGH);
}
void ArmBRotatesUp(int x)
{
  analogWrite(ArmB_EN,x);
  digitalWrite(ArmB_IN1,LOW);
  digitalWrite(ArmB_IN2,HIGH);
  digitalWrite(ArmA_IN1,HIGH);
  digitalWrite(ArmA_IN2,HIGH);
  digitalWrite(ArmC_IN1,HIGH);
  digitalWrite(ArmC_IN2,HIGH);
}
void ArmCRotatesUp(int x)
{
  analogWrite(ArmC_EN,x);
  digitalWrite(ArmC_IN1,LOW);
  digitalWrite(ArmC_IN2,HIGH);
  digitalWrite(ArmA_IN1,HIGH);
  digitalWrite(ArmA_IN2,HIGH);
  digitalWrite(ArmB_IN1,HIGH);
  digitalWrite(ArmB_IN2,HIGH);
}
void ArmARotatesDown(int x)
{
  analogWrite(ArmA_EN,x);
  digitalWrite(ArmA_IN1,HIGH);
  digitalWrite(ArmA_IN2,LOW);
  digitalWrite(ArmB_IN1,HIGH);
  digitalWrite(ArmB_IN2,HIGH);
  digitalWrite(ArmC_IN1,HIGH);
  digitalWrite(ArmC_IN2,HIGH);
}
void ArmBRotatesDown(int x)
{
  analogWrite(ArmB_EN,x);
  digitalWrite(ArmB_IN1,HIGH);
  digitalWrite(ArmB_IN2,LOW);
  digitalWrite(ArmA_IN1,HIGH);
  digitalWrite(ArmA_IN2,HIGH);
  digitalWrite(ArmC_IN1,HIGH);
  digitalWrite(ArmC_IN2,HIGH);
}
void ArmCRotatesDown(int x)
{
  analogWrite(ArmC_EN,x);
  digitalWrite(ArmC_IN1,HIGH);
  digitalWrite(ArmC_IN2,LOW);
  digitalWrite(ArmA_IN1,HIGH);
  digitalWrite(ArmA_IN2,HIGH);
  digitalWrite(ArmB_IN1,HIGH);
  digitalWrite(ArmB_IN2,HIGH);
}
void ArmAStops()
{
  digitalWrite(ArmA_IN1,HIGH);
  digitalWrite(ArmA_IN2,HIGH);
}
void ArmBStops()
{
  digitalWrite(ArmB_IN1,HIGH);
  digitalWrite(ArmB_IN2,HIGH);
}
void ArmCStops()
{
  digitalWrite(ArmC_IN1,HIGH);
  digitalWrite(ArmC_IN2,HIGH);
}
void PlayMusic()
{
  for(int x=0;x<length;x++)
  {
    tone(Tonepin,tune[x]);
    delay(500*durt[x]);   
    noTone(Tonepin);
  }
  delay(2000);
}
void DetectHuman()
{
  if(HumanFlag==true)
  {
    if(digitalRead(HumanDetect)==HIGH)
    {
      Serial.println("Notice: Human detected!");
      PlayMusic();      
      return;
    }
    else
    {
      return;
    }
  }
  else if(HumanFlag==false)
  {
    return;
  }
}
void DetectSmog()
{
  if(SmogFlag==true)
  {
  //MQ_2_sensorvalue=analogRead(MQ_2_sensor_AO);
  if( digitalRead(MQ_2_sensor_DO) == LOW ) 
  {  Serial.println("Alarm! Smog is detected");   //Alarm
     digitalWrite(LED,HIGH);      //Turn on the LED
     digitalWrite(ActiveBuzzer,HIGH);
   }
   else
   {
     digitalWrite(LED,LOW);     //Turn off the LED
     digitalWrite(ActiveBuzzer,LOW);
     return;
    }
    // delay(1000);
  }
  else if(SmogFlag==false)
  {
    return;
  }
}
void AutomaticTurn()
{ if(DistanceFlag==true)
  {
  while(FrontCondition())
    {
      WholeTracksStop();
      GetDistanceInfo();
      if(dis[1]>dis[3])
      {
         MainTracksTurnLeft(220);
      }
      else
      {
        MainTracksTurnRight(220);
      }
      delay(1000);
      MainTracksStop();
            
      if(!FrontCondition())
      {
        MainTracksAdvance(220);
      }
      return;
    }
  }
  else if (DistanceFlag==false)
  {
    return;
  }
}
float DistanceDetect()
{
  float distance;
  digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin 
  delayMicroseconds(2); 
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TrigPin, LOW);   
  distance = pulseIn(EchoPin, HIGH) / 58.0; //将回波时间换算成cm 
/*
读取一个引脚的脉冲（HIGH或LOW）。例如，如果value是HIGH，pulseIn()会等待引脚变为HIGH，开始计时，再等待引脚变为LOW并停止计时。返回脉冲的长度，单位微秒。如果在指定的时间内无脉冲函数返回。此函数的计时功能由经验决定，长时间的脉冲计时可能会出错。计时范围从10微秒至3分钟。（1秒=1000毫秒=1000000微秒）
接收到的高电平的时间（us）* 340m/s / 2 = 接收到高电平的时间（us） * 17000 cm / 1000000 us = 接收到高电平的时间 * 17 / 1000  (cm)
*/
  distance = (int(distance * 100.0)) / 100.0; //保留两位小数 
  return distance;
}

void GetDistanceInfo()
{
  for(int i=0;i<3;i++)
  {
    myservo.write(angle[i]);
    delay(500);
    dis[i]=DistanceDetect();
    delay(500);
  }
  myservo.write(90);
}
boolean FrontCondition()
{
  myservo.write(90);
  delay(20);
  float distance;
  digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin 
  delayMicroseconds(2); 
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TrigPin, LOW);   
  distance = pulseIn(EchoPin, HIGH) / 58.0; //将回波时间换算成cm 
  distance = (int(distance * 100.0)) / 100.0; //保留两位小数 
  delay(100);
  Serial.print("The obstacle is ");
  Serial.print(distance); 
  Serial.print(" cm away");
  Serial.println(); 
  return (distance<50); 
}
