# BsuirMagnetDisk



Команды управления реле:


    if(inByte=='r')   {  Serial.println("Green Lamp ON");   digitalWrite( 27, LOW);    }
    if(inByte=='t')   {  Serial.println("Green Lamp Off");   digitalWrite( 27, HIGH);    }

    if(inByte=='g')   {  Serial.println("Red Lamp ON");        digitalWrite( 26, LOW);  }
    if(inByte=='h')   {  Serial.println("Red Lamp Off");        digitalWrite( 26, HIGH);  }

    if(inByte=='p')   {  Serial.println("Pisk On");         digitalWrite( 25, LOW) ;  }
    if(inByte=='o')   {  Serial.println("Pisk Off");        digitalWrite( 25, HIGH);  }
