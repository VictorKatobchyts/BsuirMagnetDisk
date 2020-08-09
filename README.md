# BsuirMagnetDisk
9.08.20
Замеряет время между срабатываниями магнита на колесе. 
Есть подсветка и управление вводом с клавиатуры для управлением промышеленной лампы.

Если данные кажутся и неадекватными надо посмотреть моргает ли огонёк на синем модуле

*При отсутствии проходов магнита мимо датчика в течении 5 сек, данные сбрасываются на ноль

Есть баг что при включении значение скорости не равно нулю. Поэтому первую минуту подсветка горит даже если колесо не крутится

Команды управления реле
    if(inByte=='g')   {  Serial.println("Green Lamp ON");   digitalWrite( 27, LOW);    }
    if(inByte=='h')   {  Serial.println("Green Lamp Off");   digitalWrite( 27, HIGH);    }

    if(inByte=='r')   {  Serial.println("Red Lamp ON");        digitalWrite( 26, LOW);  }
    if(inByte=='t')   {  Serial.println("Red Lamp Off");        digitalWrite( 26, HIGH);  }

    if(inByte=='p')   {  Serial.println("Pisk On");         digitalWrite( 25, LOW) ;  }
    if(inByte=='o')   {  Serial.println("Pisk Off");        digitalWrite( 25, HIGH);  }
