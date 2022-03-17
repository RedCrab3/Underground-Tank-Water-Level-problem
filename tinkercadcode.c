#include <LiquidCrystal.h>

/*
Divyabrata Das Gupta
19BBS0099
*/

int inches = 0;
int cm = 0;
int buzzer = 9;
int pump = 8;
int buzflag = 1;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void playMarioTone()
{
    tone(buzzer, 659,100);
    delay(150);
    tone(buzzer, 659, 100);
    delay(150);
    tone(buzzer, 659, 100);
    delay(300);
    tone(buzzer, 659, 100);
    delay(300);
    tone(buzzer, 523, 100);
    delay(100);
    tone(buzzer, 659, 100);
    delay(300);
    tone(buzzer, 784, 100);
    delay(550);
    tone(buzzer, 392, 100);
    delay(800);
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Water Tank Level");
  lcd.setCursor(5,1);
  lcd.print("System");
  delay(1000);
  lcd.clear();

}

void loop()
{
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  int level = map(cm, 400 , 10, 0 , 100);
  lcd.setCursor(0, 0);
  lcd.print( "Tank Level");
  lcd.setCursor(0, 1);
  lcd.print(level);
  lcd.setCursor(3, 1);
  lcd.print("%");
  Serial.print(cm);
  Serial.println("cm");
  if(cm >50){
    digitalWrite(pump, HIGH);
    buzflag=1;
  }
  else{
    digitalWrite(pump, LOW);
    buzflag=0;
  }
  delay(100);
  if((cm < 100)&&(buzflag == 1)){
    playMarioTone();
  }
  else{
    digitalWrite(buzzer,LOW);
    delay(100);
  }
  
}
