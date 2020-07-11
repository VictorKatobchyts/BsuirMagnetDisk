#include <Arduino.h>
// Аларм мод
bool AlarmMode=1;
// Аларм мод

// Сериал инпут
String inputString = "";         // a String to hold incoming data
char inByte = 0;         // incoming serial byte
bool stringComplete;
String ResultString="";
// Сериал инпут
 
 
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 5 // Data pin ws2812

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
volatile bool activate = 0;// След если в течении минуты было вращение колеса
 
 // Скорость чтение оборотов в сек (герцы)
 unsigned long timingZamerOborotKoleso; // 
 volatile unsigned long timingLightOtchet; // Переменная которая считает время от последнего срабатывания холла для выключения подсветки ws2812
 volatile uint32_t count; // Кол-во общее срабатываний
 // Скорость чтение оборотов в сек (герцы)

 // Скорость чтение оборотов в сек (герцы)
 void detectsMagnet() {
     timingLightOtchet = millis();// Присваивание времени когда в последний раз крутилось колесо
     count++; //Прибавка счётчика пронёсшихся мимо магнитов
     activate=1; // Флаг для ждать мин и погасить
    
     //Serial.println("MOTION DETECTED!!!"); 
}
// Скорость чтение оборотов в сек (герцы)

void setup() {
// put your setup code here, to run once:

pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
 pixels.setPixelColor(0, pixels.Color(1, 1, 1));  delay(100);
 pixels.show(); delay(100);
Serial.begin(115200);
// Скорость чтение оборотов в сек (герцы)
pinMode(16, INPUT_PULLDOWN);
attachInterrupt(digitalPinToInterrupt(16), detectsMagnet, RISING);
// Скорость чтение оборотов в сек (герцы)

//pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
pinMode(27,OUTPUT); // Red Lamp
pinMode(26,OUTPUT); // Green Lamp
pinMode(25,OUTPUT); // Пищалка
digitalWrite(27, 1);digitalWrite(26, 1);digitalWrite(25, 1); //Выкл все реле
delay(50);
}
void SerialInput();
uint32_t Ftime;
uint32_t Secondtime;
bool step=0; // Буль чтоб один раз присваивалось значение времени
bool PazUnPa=0;
void loop() {

// Тут считаем разницу во времени между 2мя соседними срабатываниями
  //Eсли число не чётное то присвоить значение текущего времени переменной Ftime 
  if(count%2==0){
    if(step==0){
      Ftime=millis();
      step=1;PazUnPa=!PazUnPa;
    }
  }
  else {
    if(step==1){
    Secondtime=millis();
    step=0;PazUnPa=!PazUnPa;
    }
  }
  //Затем если число чётное то присвоить 

//Serial.print ("Сount magnets: "); Serial.print( count ); 
//Serial.print ("Ftime: "); Serial.print( Ftime ); 
//Serial.print (" Secondtime: "); Serial.print( Secondtime );
if(PazUnPa==0) {
Serial.print (" Raznost S-F: "); Serial.print( Secondtime-Ftime );
}
else{
  Serial.print (" Raznost F-S: "); Serial.print( Ftime-Secondtime );
}

Serial.println();
// Тут считаем разницу во времени между 2мя соседними срабатываниями

 // Скорость чтение оборотов в сек + ws2812(герцы)
// if (millis() - timingZamerOborotKoleso > 1000){ // Вместо 1000 подставьте нужное вам значение паузы   
   //    Serial.print ("Сount magnets: "); Serial.print( (float)count/3 );  //Обороты в секунду
       //Serial.print (" activate:"); Serial.print (activate);// Подставить кол-во магнитов
      // Serial.print (F(" timingLightOtchet: ")); Serial.print( timingLightOtchet ); 
       //Serial.println();
       //count=0; 
        if(activate==1){  //Если сработал датчик кода (Есть движения колеса)     
         pixels.setPixelColor(0, pixels.Color(150, 150, 150));pixels.show(); // Загорется белым
        }
        //else{    
        //timingZamerOborotKoleso = millis(); //Присвоить значение переменной
        //}

        if (millis() - timingLightOtchet > 60000){ // Если прошло 60сек
         activate=0; // Для ждать мин и погасить
         pixels.setPixelColor(0, pixels.Color(0, 0, 0));pixels.show(); // Погасить 
         timingLightOtchet = millis();
        }
       // timingZamerOborotKoleso=millis();
  //  }
 // Скорость чтение оборотов в сек + ws2812(герцы)
SerialInput(); 

}

void SerialInput(){
// Сериал инпут
 if (Serial.available() > 0) {
    // get incoming byte:
    inByte = (char)Serial.read();
    inputString += inByte;
    //Serial.print(inByte);
    if (inByte == '\n')    {   stringComplete = true;    }
 }
  if (stringComplete)
  {
    //Serial.println(inputString);
     ResultString= inputString;//"L11Z";//inputString;
    // clear the string:
    inputString = "";
    stringComplete = false;

    
    Serial.print("ResultString:");Serial.println(ResultString);
    String ResultString2=ResultString.substring(0,1);
    if(ResultString2=="g")   {  Serial.println(F("Green Lamp"));   digitalWrite( 27, HIGH); digitalWrite( 26, LOW);   }
    if(ResultString2=="r")   {  Serial.println(F("Red Lamp"));     digitalWrite( 27, LOW) ; digitalWrite( 26, HIGH);  }
    if(ResultString2=="p")   {  Serial.println("Pisk On");         digitalWrite( 25, LOW) ;  }
    if(ResultString2=="o")   {  Serial.println("Pisk Off");        digitalWrite( 25, HIGH);  }

  }
// Сериал инпут


}


