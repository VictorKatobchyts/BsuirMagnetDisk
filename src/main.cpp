#include <Arduino.h>
#include<ArduinoJson.h>//установить библиотеку scetch->include library->manage libraries->ArduinoJson
void SerialInput();
// Для замера времени между проходами магнита
uint32_t Ftime;
uint32_t Secondtime;
uint32_t timer;
bool step=0; // Буль чтоб 

unsigned long StopWheelOtchet;// Переменная которая считает время от последнего срабатывания холла для сбрасывания переменных замера первого и второго времени в ноль
// Для замера времени между проходами магнита

// Debounce + count
#define buttonPin  16    // the number of the pushbutton pin
// Variables will change:
bool ledState = HIGH;         // the current state of the output pin
bool buttonState;             // the current reading from the input pin
bool lastButtonState = LOW;   // the previous reading from the input pin
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
#define debounceDelay  1    // the debounce time; increase if the output flickers
uint32_t count;
// Debounce + count

const int8_t LedPin=21;
bool activate = 0;// Следим если в течении минуты было вращение колеса
unsigned long timingLightOtchet; // Переменная которая считает время от последнего срабатывания холла для выключения подсветки диод

// Сериал инпут
//String inputString = "";         // a String to hold incoming data
         // incoming serial byte
bool stringComplete;
String ResultString="";
// Сериал инпут
void setup() {
  Serial.begin(115200);//115200
  pinMode(buttonPin, INPUT);
  
    pinMode(27,OUTPUT); // Red Lamp
    pinMode(26,OUTPUT); // Green Lamp
    pinMode(25,OUTPUT); // Пищалка
    digitalWrite(27, 1);digitalWrite(26, 1);digitalWrite(25, 1); //Выкл все реле

    // Подвсетка
    pinMode(LedPin,OUTPUT);
    digitalWrite(LedPin,LOW);
    // Подвсетка
    //delay(50);
}

void loop() {
    char inByte = 0;
  //======================= Debounce
  // read the state of the switch into a local variable:
  bool reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  static bool CanSendSerial = false;//Есть ли сигнал от датчика чтоб один раз отправить в монитор порта
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        ledState = !ledState;
        count++;
        StopWheelOtchet = millis(); // Таймер считает сколько времени не крутилось колесо. Отсюда берётся точка отсчёта
        activate=1; // Флаг для ждать мин и погасить
        CanSendSerial=true; // Поднять флаг!
        //Serial.print("count:"); Serial.print(count ); Serial.print(" digitalPinToInterrupt(16):"); Serial.println(digitalRead(16) );
      }
    }
  }
  lastButtonState = reading;
  //======================= Debounce

  //Eсли число не чётное то присвоить значение текущего времени переменной Ftime
  if (count % 2 == 0) {
    if (step == 0) {
      Ftime = millis();
      step = 1;

    }
  }
  else {
    if (step == 1) {
      Secondtime = millis();
      step = 0;

    }
  }
  //Затем если число чётное то присвоить StopWheelOtchet
  //Serial.print( " Count:" ); Serial.print( count );  Serial.print( " step ");Serial.print( step );Serial.print( "  ");
  if(count!=0){ //Чтоб при старте не давало скорость в порт
      if (step == 0) {
        // Serial.print (" Raznost S-F: ");
        if(CanSendSerial == true){
      timer = Secondtime - Ftime;
      //Serial.println(time); //закомментировал чужой лишний код
            CanSendSerial = false;
        } 
        //  Serial.print (" StopWheelOtchet: "); Serial.print( StopWheelOtchet );
      }
      else {
        // Serial.print (" Raznost F-S: ");
        if(CanSendSerial == true){
      timer = Ftime - Secondtime;
            //Serial.println(time);//закомментировал чужой лишний код
            CanSendSerial = false;
        } 
        // Serial.print (" StopWheelOtchet: "); Serial.print( StopWheelOtchet );
      }
      
  }
  //Serial.println();
  /*
  if (millis() - StopWheelOtchet > 5000){ // Если прошло 5 сек и колесо не крутится обнулить время срабатывания между 2мя магнитами
    Ftime=0;
    Secondtime=0;     
  }
  */
  if(activate==1){  //Если сработал датчик кода (Есть движения колеса)         
      digitalWrite(LedPin,HIGH);// Загорется белым
  }
   if (millis() - timingLightOtchet > 60000){ // Если прошло 60сек
      activate=0; // Для ждать мин и погасить
      digitalWrite(LedPin,LOW);// Погасить 
      timingLightOtchet = millis();
   }
   SerialInput(inByte);
}

void SerialInput(char inByte){
// Сериал инпут
 if (Serial.available() > 0) {
    // get incoming byte:
    inByte = (char)Serial.read();
//    inputString += inByte;
    // Serial.print("inByte:");Serial.println(inByte);
    //Serial.print(inByte);
    if (inByte == '\n')    {   stringComplete = true;    }
 }

    if(inByte=='r')  {    
   digitalWrite( 27, LOW);
   DynamicJsonDocument rjson(1024);
   rjson["Time"] = timer; 
   rjson["Color"] = "Red"; 
   if (digitalRead(25)== 0){
    rjson["Pisk"] = true;}
   else {
    rjson["Pisk"] = false;
    }
   serializeJsonPretty(rjson,Serial); 
   //Serial.println();
   Serial.flush();
  }  //Serial.println("Green Lamp ON"); красный вкл по идее(red)
    if(inByte=='t')  {
   digitalWrite( 27, HIGH);
   DynamicJsonDocument tjson(1024);
   tjson["Time"] = timer; 
   tjson["Color"] = "None"; 
   if (digitalRead(25)== 0){
    tjson["Pisk"] = true;}
   else {
    tjson["Pisk"] = false;
    }
   serializeJsonPretty(tjson,Serial); 
   Serial.flush(); 
  }   //Serial.println("Green Lamp Off");красный выкл по идее(red)

    if(inByte=='g')  {
   digitalWrite( 26, LOW);
   DynamicJsonDocument gjson(1024);
   gjson["Time"] = timer; 
   gjson["Color"] = "Green";
   if (digitalRead(25)== 0){
    gjson["Pisk"] = true;}
   else {
    gjson["Pisk"] = false;
    }
   serializeJsonPretty(gjson,Serial); 
   Serial.flush();
  }    //Serial.println("Red Lamp ON"); зеленый вкл (green)
    if(inByte=='h')  {
   digitalWrite( 26, HIGH); 
   DynamicJsonDocument hjson(1024);
   hjson["Time"] = timer; 
   hjson["Color"] = "None";
   if (digitalRead(25)== 0){
    hjson["Pisk"] = true;}
   else {
    hjson["Pisk"] = false;
    }
   serializeJsonPretty(hjson,Serial);  
   Serial.flush();
  }   //Serial.println("Red Lamp Off"); зеленый выкл (green)

    if(inByte=='p')  {   
   digitalWrite( 25, LOW) ; 
   DynamicJsonDocument pjson(1024);
   pjson["Time"] = timer; 
   if (digitalRead(25)== 0){
    pjson["Pisk"] = true;}
   else {
    pjson["Pisk"] = false;
    }
   serializeJsonPretty(pjson,Serial); 
   Serial.flush();
  }    //Serial.println("Pisk On"); пищалка вкл
    if(inByte=='o')  {
   digitalWrite( 25, HIGH);
   DynamicJsonDocument ojson(1024);
   ojson["Time"] = timer; 
   if (digitalRead(25)== 0){
    ojson["Pisk"] = true;}
   else {
    ojson["Pisk"] = false;
    } 
   serializeJsonPretty(ojson,Serial); 
   Serial.flush();
  }//Serial.println("Pisk Off"); 
    if(inByte=='s')  {
   DynamicJsonDocument sjson(1024);
   sjson["Time"] = timer;
   if (digitalRead(25)== 0){
    sjson["Pisk"] = true;}
   else {
    sjson["Pisk"] = false;
    }
   serializeJsonPretty(sjson,Serial); 
   Serial.flush();
  }
// Сериал инпут


}

