# BsuirMagnetDisk
30.08.2020
Как работает замер времени между срабатывания ИК датчика. При каждом срабатывании датчика счётчик прирастает на +1. Если он чётный - записывается время из таймера millis в переменную Ftime. Если нечётный то время из таймера millis в переменную Secondtime. Если число не чётное делаем Secondtime - Ftime. Иначе Ftime - Secondtime. И эти значения один раз летят в порт по разрешающему флагу который активируется при сработке датчика. Флаг опускается после отправки инфы в порт


Команды управления реле:


    if(inByte=='r')  {    digitalWrite( 27, LOW);  }  //Serial.println("Green Lamp ON"); 
    if(inByte=='t')  {    digitalWrite( 27, HIGH); }   //Serial.println("Green Lamp Off");

    if(inByte=='g')  {    digitalWrite( 26, LOW);  }    //Serial.println("Red Lamp ON");
    if(inByte=='h')  {    digitalWrite( 26, HIGH); }   //Serial.println("Red Lamp Off"); 

    if(inByte=='p')  {   digitalWrite( 25, LOW) ;  }    //Serial.println("Pisk On");
    if(inByte=='o')  {   digitalWrite( 25, HIGH);  }    //Serial.println("Pisk Off"); 
