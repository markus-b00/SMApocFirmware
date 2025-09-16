//Code immer auskommentiert lassen

/*

//Funktionsprototypen
//void PGAsetup();
//void PGAcontrol(); 
//void PWMsetup();
//void TimerStart(Tc *tc, uint32_t channel, IRQn_Type irq);




_______________________________________________________________________________________________
//Warten bis Bus Bereit

      switch(Serial_Step)
      {
        case 1:
        {
//          if(digitalRead(18)==HIGH)    //Wenn RX1 high dann überprüfung starten.
//          {
//            T_serial_start = GLtime;               
//            Serial_Step++;
//          }  
            Serial_Step++;        
        }
        break;
        case 2:
        {
//          if((digitalRead(18)==HIGH)&&(GLtime - T_serial_start > T_serial_start_Dauer))        //Wenn RX1 high und Zeit von 0,5µs abgelaufen dann Zähler um 1 erhöhen
//          {
//            Serial_Start++;
//            T_serial_start = GLtime;
//          }
//
//          if (digitalRead(18)==LOW) Serial_Step=0;                                             //Wenn RX1 low bevor Schwellwert von 30µs erreicht, dann erneut zum Zählen beginnen
//
//          if (Serial_Start >= 60)                                                              //Wenn RX1 mindestens 30µs auf High war, dann mit Übertragung beginnen
//          {
//            Serial_Step++;
//          }
           //if (Serial1.available()) Serial_Step++;
              
          Serial_Step++; 
        }
        break;
        case 3:
        { 

 
            Serial_Step = 0;         
            
        }
        break;
        default:
        {
          Serial_Start = 0;                               //Zähler zurücksetzten
          Serial_Step++;
        }
      }//Ende Stateflow 2
___________________________________________________________________________________________


*/



//Serial Code alt______________________________________________________

    //Testwerte 
      //StatusOut = 85;
      //SensorMittelwert1 = 170;
      //SensorMittelwert2 = 85;
      
//      outBytes[0] = StatusOut;
//      outBytes[1] = SensorMittelwert1;
//      outBytes[2] = SensorMittelwert1>>8;
//      outBytes[3] = SensorMittelwert2;
//      outBytes[4] = SensorMittelwert2>>8;

//      //Test
//      outBytes[0] = inBytes[0];
//      outBytes[1] = inBytes[1];
//      outBytes[2] = inBytes[2];
//      outBytes[3] = inBytes[3];
//      outBytes[4] = inBytes[4];
//
//      outBytes[0] = merkerBytes[0];
//      outBytes[1] = merkerBytes[1];
//      outBytes[2] = merkerBytes[2];
//      outBytes[3] = merkerBytes[3];
//      outBytes[4] = merkerBytes[4];

//      outBytes[0] = 55;
//      outBytes[1] = 170;
//      outBytes[2] = 12;
//      outBytes[3] = 42;
//      outBytes[4] = 9;



//          if(SerialStart == 0)
//          {
//            inBytes[0] = Serial1.read();    //Stautsbytes Auslesen              
//            inBytes[1] = Serial1.read();
//          }
//          else
//          {
//            Serial1.readBytes(inBytes, Buffer_Laenge);
//          }
          
          
          //Serial1.readBytes(inBytes, Buffer_Laenge);
//        
//        inBytes[2] = Serial1.read();
//        inBytes[3] = Serial1.read();
//        inBytes[4] = Serial1.read();
//        inBytes[5] = Serial1.read();
  
//          if((inBytes[0]==1) && (inBytes[1]==125))
//          {
//
//            SerialStart = 1;
//            Serial1.write(outBytes, Buffer_Laenge);       //x Bytes des Arrays senden
//         
//            Step++;                                       //Weiter zum nächsten Schritt
//          }
//          else 
//          {
//            inBytes[2] = Serial1.read();
//            inBytes[2] = Serial1.read();
//          }
      //digitalWrite(13, HIGH);       //Debugging SPG-Messung
//            inBytes[3] = Serial1.read();
//            inBytes[4] = Serial1.read();
//            inBytes[0] = Serial1.read();
//            inBytes[1] = Serial1.read();
//            inBytes[2] = Serial1.read();

      
      //digitalWrite(13, LOW);       //Debugging SPG-Messung
      //digitalWrite(RTS, HIGH);          //Handshake 
      
      //digitalWrite(13, HIGH);       //Debugging SPG-Messung            
      //Serial1.write(outBytes, Buffer_Laenge);       //x Bytes des Arrays senden
      //digitalWrite(13, LOW);       //Debugging SPG-Messung

      //      DutyCycle1 = DutyCycle1<<1;                   //DutyCycle mal 2, um vollen DutyCycle auszunutzen (evtl. bessere Einstellmöglichkeit in den PWM Parametern)
//      DutyCycle3 = DutyCycle3<<1;                   //DutyCycle mal 2

      
      //Serial.println("Case 3");
//      Serial.print(inBytes[1]);
//      Serial.print("   ");
//      Serial.println(inBytes[2]);
      

        //Step++;                                       //Weiter zum nächsten Schritt
//_____________________________________________________________________________________________________________________
