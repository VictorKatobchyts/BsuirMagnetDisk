# BsuirMagnetDisk
30.08.2020
Как работает вкратце замер времени между срабатывания ИК датчика. При каждом срабатывании датчика счётчик прирастает на +1. Если он чётный - записывается время из таймера millis в переменную Ftime. Если нечётный то время из таймера millis в переменную Secondtime. Если число не чётное делаем Secondtime - Ftime. Иначе Ftime - Secondtime. И эти значения один раз летят в порт по разрешающему флагу который активируется при сработке датчика. Флаг опускается после отправки инфы в порт


Команды управления реле:


    if(inByte=='r')   {  Serial.println("Green Lamp ON");   digitalWrite( 27, LOW);    }
    if(inByte=='t')   {  Serial.println("Green Lamp Off");   digitalWrite( 27, HIGH);    }

    if(inByte=='g')   {  Serial.println("Red Lamp ON");        digitalWrite( 26, LOW);  }
    if(inByte=='h')   {  Serial.println("Red Lamp Off");        digitalWrite( 26, HIGH);  }

    if(inByte=='p')   {  Serial.println("Pisk On");         digitalWrite( 25, LOW) ;  }
    if(inByte=='o')   {  Serial.println("Pisk Off");        digitalWrite( 25, HIGH);  }
