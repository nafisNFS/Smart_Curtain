#include <OneWire.h>
#include <DallasTemperature.h>
const int ena=5;
const int in1=6;
const int in2=7;
int f=0;
int l=0;
char sms;
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

float Celsius = 0;

void setup() {
  sensors.begin();
  Serial.begin(9600);
  pinMode(ena,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()!=0){
    sms=Serial.read();
    if(sms=='1'){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena,255);
    delay(1000);
    }
    else if(sms=='0'){
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      analogWrite(ena,0);
      delay(1000);
    }

    else if(sms=='2'){
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      analogWrite(ena,255);
      delay(1000);
    }

  }
  
  else{
    sensors.requestTemperatures();
    float Celsius = sensors.getTempCByIndex(0);
    if(Celsius>25.0 && f==0 && l==0){
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      analogWrite(ena,255);
      delay(5000);
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      analogWrite(ena,0);
      f=1;
    }
    if(Serial.available()!=0){
          sms=Serial.read();
          if(sms=='1'){
          digitalWrite(in1,HIGH);
          digitalWrite(in2,LOW);
          analogWrite(ena,255);
          delay(1000);
          l=0;
          }
        else if(sms=='0'){
          digitalWrite(in1,LOW);
          digitalWrite(in2,LOW);
          analogWrite(ena,0);
          delay(1000);
          l=1;
          }

        else if(sms=='2'){
          digitalWrite(in1,LOW);
          digitalWrite(in2,HIGH);
          analogWrite(ena,255);
          delay(1000);
          l=0;
        }
      
     }
     else{
       f=0;
     }
     
  
    
    delay(1000);
  }
}
