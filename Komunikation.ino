
//---------------------------------------------------------------------------------------------------------------------------------------------------------
// Kommunikationsprotoll mit Serial 0
void kom_function(){
    
   

//        StatusOut = 117;
//        StatusOut2 = 122;
        StatusOut = 88;
        StatusOut2 = 99;
        // Desktop RealTime
        outBytesC[0] = StatusOut;
        outBytesC[1] = StatusOut2;
        outBytesC[2] = Wert1out;            //Status 222
        outBytesC[3] = Wert1out >> 8;
        outBytesC[4] = Wert2out;            //Widerstandswert Ch1
        outBytesC[5] = Wert2out >> 8;
        outBytesC[6] = Wert3out;            //Widerstandswert Ch2
        outBytesC[7] = Wert3out >> 8;
        outBytesC[8] = Wert4out;            //Widerstandswert Ch3
        outBytesC[9] = Wert4out >> 8;
        outBytesC[10] = Wert5out;           //Widerstandswert Ch4
        outBytesC[11] = Wert5out >> 8;
        outBytesC[12] = Wert6out;           //Widerstandswert Ch5
        outBytesC[13] = Wert6out >> 8;
        outBytesC[14] = Wert7out;           //Widerstandswert Ch6
        outBytesC[15] = Wert7out >> 8;
        
    

        digitalWrite(RTS, LOW);          //Handshake


       //digitalWrite(LED_g,HIGH);
        if ((Serial.available()) && (Serial.find("uz"))) {     //Sind Daten zum abholen bereit und ist das Protokoll bei den StatusBytes
        digitalWrite(LED_g,HIGH);
          
          Serial.readBytes(inBytesC, Buffer_Laenge_in);
//                  //Test für Debbuging
      //  outBytesC[0] = 99; //inBytesC[0];
      //  outBytesC[1] = 88; //inBytesC[1];
      //  outBytesC[2] = inBytesC[0];
      //  outBytesC[3] = inBytesC[1];
      //  outBytesC[4] = inBytesC[2];
      //  outBytesC[5] = inBytesC[3];
      //  outBytesC[6] = inBytesC[4];
      //  outBytesC[7] = inBytesC[5];
      //  outBytesC[8] = inBytesC[6];
      //  outBytesC[9] = inBytesC[7];
      //  outBytesC[10] = inBytesC[8];
      //  outBytesC[11] = inBytesC[9];
      //  outBytesC[12] = inBytesC[10];
      //  outBytesC[13] = inBytesC[11];
      //  outBytesC[14] = inBytesC[12];
      //  outBytesC[15] = inBytesC[13];
      //  outBytesC[16] = inBytesC[14];
      //  outBytesC[17] = inBytesC[15];
      //  outBytesC[18] = inBytesC[16];
      //  outBytesC[19] = inBytesC[17];
      //  outBytesC[20] = inBytesC[18];
      //  outBytesC[21] = inBytesC[19];
      //  outBytesC[22] = inBytesC[20];
      //  outBytesC[23] = inBytesC[21];
      
        
          Serial.write(outBytesC, Buffer_Laenge_out);       //x Bytes des Arrays senden
          digitalWrite(RTS, HIGH);          //Handshake

          
          //merkerBytesC[0] = 88;
          //merkerBytesC[1] = 99;    

          merkerBytesC[0] = inBytesC[0];    
          merkerBytesC[1] = inBytesC[1];                
          
          merkerBytesC[2] = inBytesC[2];
          merkerBytesC[3] = inBytesC[3];
          merkerBytesC[4] = inBytesC[4];
          merkerBytesC[5] = inBytesC[5];
          merkerBytesC[6] = inBytesC[6];      //Byte Handling
          merkerBytesC[7] = inBytesC[7];
          merkerBytesC[8] = inBytesC[8];
          merkerBytesC[9] = inBytesC[9];
          merkerBytesC[10] = inBytesC[10];
          merkerBytesC[11] = inBytesC[11];
          merkerBytesC[12] = inBytesC[12];
          merkerBytesC[13] = inBytesC[13];
          merkerBytesC[14] = inBytesC[14];
          merkerBytesC[15] = inBytesC[15];
       
          
          StatusIn  = merkerBytesC[0];                        //Statusbyte neu beschreiben
          StatusIn2 = merkerBytesC[1];                        //Statusbyte1 neu beschreiben

          //Duty Cycle neu einstellen Kanal 1
          Wert1 = merkerBytesC[2];                      //Leistung 1 Lowbyte Schreiben
          Wert1 |= merkerBytesC[3] << 8;                //Leistung 1 Highbyte schreiben
          Wert1out=Wert1;

          //Duty Cycle neu einstellen Kanal 2
          Wert2 = merkerBytesC[4];                      //Leistung 2 Lowbyte schreiben
          Wert2 |= merkerBytesC[5] << 8;                //Leistung 2 3 Highbyte schreiben
          Wert2out=Wert2;
          
          Wert3 = merkerBytesC[6];                      //Leistung 3 Lowbyte schreiben
          Wert3 |= merkerBytesC[7] << 8;                //Leistung 3 Highbyte schreiben
          Wert3out = Wert3;

          Wert4 = merkerBytesC[8];                      //Leistung 4 Lowbyte schreiben
          Wert4 |= merkerBytesC[9] << 8;                //Leistung 4 Highbyte schreiben
          Wert4out = Wert4;

          Wert5 = merkerBytesC[10];                      //Leistung 5 Lowbyte schreiben
          Wert5 |= merkerBytesC[11] << 8;                //Leistung 5 Highbyte schreiben
          Wert5out = Wert5;

          Wert6 = merkerBytesC[12];                      //Leistung 6 Lowbyte schreiben
          Wert6 |= merkerBytesC[13] << 8;                //Leistung 6 Highbyte schreiben
          Wert6out = Wert6;

          //Serial.println(Wert3);   // send Text
          digitalWrite(LED_g, LOW);
          StepC= Wert1out;
          flag_com =1;
        
   }
}

