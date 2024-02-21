#include <Ultrasonic.h> 
Ultrasonic ultrasonic(5,4); // (Trig PIN,Echo PIN)
#define mesafe ultrasonic.Ranging(CM)
#define solin1 6
#define solin2 9
#define sagin3 10
#define sagin4 11
#define sagsensor digitalRead(12) //siyah görünce 1, beyaz görünce 0 geliyor.
#define solsensor digitalRead(7)

void ileri(){
  analogWrite(solin1,0);
  analogWrite(solin2,255);
  analogWrite(sagin3,0);
  analogWrite(sagin4,255);
}
void geri(){
  analogWrite(solin1,255);
  analogWrite(solin2,0);
  analogWrite(sagin3,255);
  analogWrite(sagin4,0);
}
void dur(){
  analogWrite(solin1,0);
  analogWrite(solin2,0);
  analogWrite(sagin3,0);
  analogWrite(sagin4,0);
}
void sagadon(){
  analogWrite(solin1,0);
  analogWrite(solin2,255);
  analogWrite(sagin3,0);
  analogWrite(sagin4,64);
}
void soladon(){
  analogWrite(solin1,0);
  analogWrite(solin2,64);
  analogWrite(sagin3,0);
  analogWrite(sagin4,255);
}
void manevra(){
  dur(); 
  delay(250);
  sagadon();
  while(!solsensor); dur(); delay(250); 
  sagadon();
  delay(250);
  analogWrite(solin1,0);
  analogWrite(solin2,128);
  analogWrite(sagin3,0);
  analogWrite(sagin4,255);  
  while(!solsensor && !sagsensor);
  ileri();
}
void setup() {
  pinMode(12,INPUT);
  pinMode(7,INPUT);
  delay(3000);
}
void loop() {
  if(mesafe<30) manevra();
  if(solsensor && !sagsensor){
    soladon();
    while(!sagsensor){
       if(mesafe<30) manevra();
    }
  }
  if(sagsensor && !solsensor){
    sagadon();
    while(!solsensor){
       if(mesafe<30) manevra();
    }
  }
  if(!solsensor && !sagsensor){
    ileri();
  }
  if(solsensor && sagsensor){
    dur();
  }
}
