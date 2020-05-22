#define memosize 40
#define ADCPin A0
#define printDelay 0
#define databuffer 5
#define BT_ONpin A2
#define SegA A4
#define SegB 9
#define SegC 7
#define SegD 5
#define SegE 3 
#define SegF 4
#define SegG 8
#define RDP 6
#define LED1 10
#define LED2 11
#define LED3 12
#define bluetooth 2
#define backbutton A3
#define frontbutton A1
#include "AnalogFrequency.h"

float speedKM[databuffer]={};
float speedshow=0;
float Measured=0;
int digit1=0;
int digit2=0;
int digit3=0;
int j=0;
int k=0;
uint32_t displayTimer = 0;
uint32_t slot_time = 0;
float memo[memosize]={}; //tab for save of measured values
bool going;


void setup() {
  Serial.begin(9600);
  setupADC(ADCPin);
 
  pinMode(BT_ONpin,OUTPUT);
  digitalWrite(BT_ONpin,LOW);
  pinMode(bluetooth,INPUT);
  pinMode(backbutton,INPUT);
  pinMode(frontbutton,INPUT);
  pinMode(RDP,OUTPUT);
  pinMode(SegG,OUTPUT);
  pinMode(SegF,OUTPUT);
  pinMode(SegE,OUTPUT);
  pinMode(SegD,OUTPUT);
  pinMode(SegC,OUTPUT);
  pinMode(SegB,OUTPUT);
  pinMode(SegA,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
 digitalWrite(LED1,LOW);
 digitalWrite(LED2,LOW);
 digitalWrite(LED3,LOW);
  digitalWrite(RDP,HIGH);

}
//bluetooth sending function
void send_data()
{
  bool flag=false;
  bool sending=true;
  digitalWrite(BT_ONpin,HIGH);
  digitalWrite(SegA,HIGH);
  digitalWrite(SegB,HIGH);
  digitalWrite(SegC,HIGH);
  digitalWrite(SegD,HIGH);
  digitalWrite(SegE,HIGH);
  digitalWrite(SegF,HIGH);
  digitalWrite(SegG,LOW);
  digitalWrite(RDP,LOW);
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,HIGH);
  digitalWrite(LED3,HIGH);
 
   while(sending)
  {
   
    if(digitalRead(backbutton)==LOW)
    {
      
    for(int i=0;i<memosize; i++)
      {
      
      Serial.print(i);
      Serial.print(". KM/h: ");
      Serial.println(memo[i]);
       
       }
      for(int i=0;i<memosize;i++)memo[i]=0;
      sending=false;
      }
    
     
   }
  delay(5000);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(BT_ONpin,LOW);
  }
  
void zero()//function writing 0 on 7seg display
{
  digitalWrite(SegA,LOW);
  digitalWrite(SegB,LOW);
  digitalWrite(SegC,LOW);
  digitalWrite(SegD,LOW);
  digitalWrite(SegE,LOW);
  digitalWrite(SegF,LOW);
  digitalWrite(SegG,HIGH);
 // digitalWrite(RDP,HIGH);
  }
  void one()//function writing 1 on 7seg display
  {
  digitalWrite(SegA,HIGH);
  digitalWrite(SegB,LOW);
  digitalWrite(SegC,LOW);
  digitalWrite(SegD,HIGH);
  digitalWrite(SegE,HIGH);
  digitalWrite(SegF,HIGH);
  digitalWrite(SegG,HIGH);
 // digitalWrite(RDP,HIGH);
    
    }
  void two()//function writing 2 on 7seg display
{
  digitalWrite(SegA,LOW);
  digitalWrite(SegB,LOW);
  digitalWrite(SegC,HIGH);
  digitalWrite(SegD,LOW);
  digitalWrite(SegE,LOW);
  digitalWrite(SegF,HIGH);
  digitalWrite(SegG,LOW);
 // digitalWrite(RDP,HIGH);

  }
    void three()//function writing 3 on 7seg display
{
  digitalWrite(SegA,LOW);
  digitalWrite(SegB,LOW);
  digitalWrite(SegC,LOW);
  digitalWrite(SegD,LOW);
  digitalWrite(SegE,HIGH);
  digitalWrite(SegF,HIGH);
  digitalWrite(SegG,LOW);
 // digitalWrite(RDP,HIGH);

  }
   void four()//function writing 4 on 7seg display
{
  digitalWrite(SegA,HIGH);
  digitalWrite(SegB,LOW);
  digitalWrite(SegC,LOW);
  digitalWrite(SegD,HIGH);
  digitalWrite(SegE,HIGH);
  digitalWrite(SegF,LOW);
  digitalWrite(SegG,LOW);
 // digitalWrite(RDP,HIGH);

  }

   void five()//function writing 5 on 7seg display
{
  digitalWrite(SegA,LOW);
  digitalWrite(SegB,HIGH);
  digitalWrite(SegC,LOW);
  digitalWrite(SegD,LOW);
  digitalWrite(SegE,HIGH);
  digitalWrite(SegF,LOW);
  digitalWrite(SegG,LOW);
 // digitalWrite(RDP,HIGH);

  }

   void six()//function writing 6 on 7seg display
{
   digitalWrite(SegA,LOW);
  digitalWrite(SegB,HIGH);
  digitalWrite(SegC,LOW);
  digitalWrite(SegD,LOW);
  digitalWrite(SegE,LOW);
  digitalWrite(SegF,LOW);
  digitalWrite(SegG,LOW);
 // digitalWrite(RDP,HIGH);

  }

   void seven()//function writing 7 on 7seg display
{
  digitalWrite(SegA,LOW);
  digitalWrite(SegB,LOW);
  digitalWrite(SegC,LOW);
  digitalWrite(SegD,HIGH);
  digitalWrite(SegE,HIGH);
  digitalWrite(SegF,HIGH);
  digitalWrite(SegG,HIGH);
//  digitalWrite(RDP,HIGH);

  }


   void eight() //function writing 8 on 7seg display
{
   digitalWrite(SegA,LOW);
  digitalWrite(SegB,LOW);
  digitalWrite(SegC,LOW);
  digitalWrite(SegD,LOW);
  digitalWrite(SegE,LOW);
  digitalWrite(SegF,LOW);
  digitalWrite(SegG,LOW);
 // digitalWrite(RDP,HIGH);

  }


   void nine() //function writing 9 on 7seg display
{
  digitalWrite(SegA,LOW);
  digitalWrite(SegB,LOW);
  digitalWrite(SegC,LOW);
  digitalWrite(SegD,LOW);
  digitalWrite(SegE,HIGH);
  digitalWrite(SegF,LOW);
  digitalWrite(SegG,LOW);
  //digitalWrite(RDP,HIGH);

  }
  void _display(int digit) //function to display digit on 7seg display
  {
    switch(digit)
    {
      case 0:zero();
      break;
      case 1:one();
      break;
      case 2:two();
      break;
      case 3:three();
      break;
      case 4:four();
      break;
      case 5:five();
      break;
      case 6:six();
      break;
      case 7:seven();
      break;
      case 8:eight();
      break;
      case 9:nine();
      break;
      default:
      break;
      }
    
  }
  void showscreen(float tmp2,bool lock)
  {
    int tmp = tmp2;
digit1=tmp%10;
 tmp=(tmp-(tmp%10));
 digit2=tmp%100*0.1;
 tmp=(tmp-(tmp%100));
 digit3=tmp%1000*0.01;
 tmp=(tmp-(tmp%1000));
 //display last measured speed
 if(k==(memosize)&&lock)digitalWrite(RDP,LOW);
   else digitalWrite(RDP,HIGH);
 _display(digit1);
  digitalWrite(LED1,HIGH);
  delay(5);
  digitalWrite(LED1,LOW);
 _display(digit2);
  digitalWrite(LED2,HIGH);
   delay(5);
  digitalWrite(LED2,LOW);
  if(lock)digitalWrite(RDP,LOW);
 _display(digit3);
  digitalWrite(LED3,HIGH);
   delay(5);
  digitalWrite(LED3,LOW);

    }
 
void loop() {
  //measure speed
 if( fAvailable() && millis() - displayTimer > printDelay ){
   
   
   displayTimer = millis();   
   uint32_t frequency = getFreq();
    speedKM[j] = frequency/19.49;
   j++;
   if(j>databuffer-1)
   {j=0;
   for(int i=0;i<databuffer;i++)
   {
    speedshow+=speedKM[i];
    }
    speedshow=speedshow/databuffer;
    if(speedshow<1.0)speedshow=0;
    if(speedshow>Measured||(millis()-slot_time)>500)
     {
      Measured=speedshow;
      slot_time=millis();
     }
   speedshow=0;
  }
 }
 if(digitalRead(bluetooth)==LOW)send_data();
 if(digitalRead(frontbutton)==LOW)
 {
     going=true;
     if(k>=memosize)
      {k=0;
      send_data();
      }
     memo[k]=Measured;
     k++;
   
     while(going)
     {
      showscreen(Measured,true);
      if(digitalRead(backbutton)==LOW)going=false;
      }
 
  }
 showscreen(Measured,false);

}
