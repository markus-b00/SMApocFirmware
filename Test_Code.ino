//Platz für Main Testcode

void Test_Code() {

  //Wenn Kalibrierung abgeschlossen. Dann kann kann der Testcode ausgeführt werden
  if (cali_flag == 0) {
    if (Switch2_in == 1) {
      //Wenn Taster gedrückt dann Leistung auf CHx ausgeben
      //  T_duty_cycle1 = 52500*0.25;
      //  T_duty_cycle2 = 52500*0.25;
      //  T_duty_cycle3 = 5000;
      //  T_duty_cycle4 = 5000;
      //  T_duty_cycle5 = 5000;
      //  T_duty_cycle6 = 5000;
      P_in1 = 50;   //mW
      P_in2 = 150;  //mW
      P_in3 = 250;  //mW
      flag_loop = 1;
      digitalWrite(LED_y, HIGH);

      //Calib_CHx_ON_OFF[1] = 1;
      //Calib_R1_ON_OFF = OFF;
      //Calib_R2_ON_OFF = ON;



    } else {
      //Wenn Taster nicht gedrückt keine Leistung ausgeben
      /*T_duty_cycle1 = 0;
     T_duty_cycle2 = 0;
     T_duty_cycle3 = 0;
     T_duty_cycle4 = 0;
     T_duty_cycle5 = 0;
     T_duty_cycle6 = 0;
     */
      //flag_loop = 3;

      digitalWrite(LED_y, LOW);




      //Calib_CHx_ON_OFF[1] = 1;
      //Calib_R1_ON_OFF = ON;
      //Calib_R2_ON_OFF = OFF;
    }
  }
}



//  if (Serial.available()) {
//             datenpaket = Serial.read(); //liest die Daten
//
//             //if (datenpaket == 1) { digitalWrite(13, HIGH); Serial.write(50);}
//             //if (datenpaket == 0) { digitalWrite(13, LOW);  Serial.write(51);}
//
//             Serial.flush(); //seriellen Puffer löschen
//
//
//   }

//P_in1=0;          // [mW] Leistungen manuell einstellen
//P_in2=0;

//I_leis1 = 0.516;    // [A] Spitzenstrom Leistungpuls Ch1
//I_leis2 = 0.516;    // [A] Spitzenstrom Leistungpuls Ch1
//Serial.println("Test");   // send Text

//Testcode, wenn Taster gedrückt, dann wird die jeweilige Stromquelle aktiv
//  if ((Switch1_in == 1)&&(Switch2_in == 1)) {LED_y_ontime = 6000;}
//  else if ((Switch1_in == 1) && (TestVar_1 == 0)) {LED_y_ontime = 3000; StepC++; TestVar_1 = 1;}                    //Kalibrationsschritt um 1 Hochzählen
//  else if (Switch2_in == 1) {LED_y_ontime = 3000; TestVar_1 = 0;}                                                   //Erst wenn Taster 2 gedrückt wurde kann weiter hochgezählt werden.
//  else {LED_y_ontime = 0;}

//Testcode für Kalibrierung von DAC0 bis DAC3
//  if ((Switch1_in == 1)&&(Switch2_in == 1)) {LED_y_ontime = 6000;}
//  else if ((Switch1_in == 1) && (TestVar_1 == 0))
//    {
//      LED_y_ontime = 3000;
//
//      Spg_Messpuls_Ch1 = Spg_Messpuls_Ch1+1000;            //Wert für DAC0 0-52500 Schritte = 0V bis 3,3V --> ISp = 71mA
//      Spg_Leistungspuls_Ch1 = Spg_Leistungspuls_Ch1+1000;       //Wert für DAC1 0-52500 Schritte = 0V bis 3,3V --> ISp = 516mA
//      Spg_Messpuls_Ch2 = Spg_Messpuls_Ch2+1000;            //Wert für DAC0 0-52500 Schritte = 0V bis 3,3V
//      Spg_Leistungspuls_Ch2 = Spg_Leistungspuls_Ch2+1000;       //Wert für DAC1 0-52500 Schritte = 0V bis 3,3V
//      Serial.println(Spg_Messpuls_Ch1);   // send Text
//      TestVar_1 = 1;
//      }                    //Kalibrationsschritt um 1 Hochzählen
//  else if (Switch2_in == 1) {LED_y_ontime = 3000; TestVar_1 = 0;}                                                   //Erst wenn Taster 2 gedrückt wurde kann weiter hochgezählt werden.
//  else {LED_y_ontime = 0;}
//




//  //Testcode, wenn Taster gedrückt, dann wird die jeweilige Stromquelle aktiv
//  if ((Switch1_in == 1)&&(Switch2_in == 1)) {LED_y_ontime = 6000; CH1_ENABLE_out = 0; CH2_ENABLE_out = 0;}
//  else if (Switch1_in == 1) {LED_y_ontime = 3000; CH1_ENABLE_out = 0;}
//  else if (Switch2_in == 1) {LED_y_ontime = 3000; CH2_ENABLE_out = 0;}
//  else {LED_y_ontime = 0; CH1_ENABLE_out = 1; CH2_ENABLE_out = 1;}

//  //Serial.println(REG_PWM_CCNT0);
//  DutyCycle1 = 1000;
//  DutyCycle3 = 1000;
//  REG_PWM_CDTY1 = DutyCycle1 + MessDauer;       //Duty Cycle des Leistungspuls übergeben Kanal1
//  REG_PWM_CDTY3 = DutyCycle3 + MessDauer;       //Duty Cycle des Leistungspuls übergeben Kanal2
//
//  //Testcode für SMAPOC.EXE   BuiltInLED wird über PC gesteuert.
//   if (Serial.available()) {
//             datenpaket = Serial.read(); //liest die Daten
//
//             if (datenpaket == 1) { digitalWrite(13, HIGH); Serial.write(50);}
//             if (datenpaket == 0) { digitalWrite(13, LOW);  Serial.write(51);}
//
//             Serial.flush(); //seriellen Puffer löschen
//
//
//   }
//
