
void Main_Stateflow() {

  switch (Step) {
    case 1:  //Spannungen erstes mal über SMA Draht Kanal 1 und 2 messen (im Messpuls)
      {
        //Serial.println("Step 1");   // send Text
        if (GLtime - T_mess_on > T_mess_on_Dauer) {
          digitalWrite(13, HIGH);  //Debugging SPG-Messung
          //Messung 1_1
          sensorValue1[Mess_Counter] = analogRead(analogInPin1);  //erste Spannungsmessung Draht 1
          //Messung 2_1
          sensorValue2[Mess_Counter] = analogRead(analogInPin2);  //erste Spannungsmessung Draht 2
          //Messung 3_1
          sensorValue3[Mess_Counter] = analogRead(analogInPin3);  //erste Spannungsmessung Draht 3
          //Messung 4_1
          sensorValue4[Mess_Counter] = analogRead(analogInPin4);  //erste Spannungsmessung Draht 4
          //Messung 5_1
          sensorValue5[Mess_Counter] = analogRead(analogInPin5);  //erste Spannungsmessung Draht 5
          //Messung 6_1
          sensorValue6[Mess_Counter] = analogRead(analogInPin6);  //erste Spannungsmessung Draht 6

          //Zeit Starten Messung 2
          digitalWrite(13, LOW);  //Debugging SPG-Messung
          T_mess = GLtime;
          //Messzähler hochzählen für nächsten Wert im Array
          Mess_Counter++;

          //          //Zweite Messung direkt im Anschluss
          //          digitalWrite(13, HIGH);       //Debugging SPG-Messung
          //          sensorValue1[Mess_Counter] = analogRead(analogInPin1);     //erste Spannungsmessung Draht 1
          //          //Messung 2_1
          //          sensorValue2[Mess_Counter] = analogRead(analogInPin2);     //erste Spannungsmessung Draht 2
          //          //Zeit Starten Messung 2
          //          T_mess = GLtime;
          //          //Messzähler hochzählen für nächsten Wert im Array
          //          Mess_Counter++;




          //Weiter zum nächsten Step
          Step++;
          //Serial.println("Case 1");
          digitalWrite(13, LOW);  //Debugging SPG-Messung
        }
      }
      break;
    case 2:  //Spannungen n-mal über SMA Draht Kanal 1 und 2 messen (im Messpuls) und Mittelwert berechnen
      {
        //Serial.println("Step 2");   // send Text
        if (GLtime - T_mess > T_mess_Dauer) {
          digitalWrite(13, HIGH);  //Debugging SPG-Messung
          //Messung 2 bis n
          sensorValue1[Mess_Counter] = analogRead(analogInPin1);  //Spannungsmessung Draht 1
          //Messung 2 bis n
          sensorValue2[Mess_Counter] = analogRead(analogInPin2);  //Spannungsmessung Draht 2
          //Messung 2 bis n
          sensorValue3[Mess_Counter] = analogRead(analogInPin3);  //Spannungsmessung Draht 3
          //Messung 2 bis n
          sensorValue4[Mess_Counter] = analogRead(analogInPin4);  //Spannungsmessung Draht 4
          //Messung 2 bis n
          sensorValue5[Mess_Counter] = analogRead(analogInPin5);  //Spannungsmessung Draht 5
          //Messung 2 bis n
          sensorValue6[Mess_Counter] = analogRead(analogInPin6);  //Spannungsmessung Draht 6
          //Zeit Starten nächste Messung
          T_mess = GLtime;
          //Messzähler hochzählen für nächsten Wert im Array
          Mess_Counter++;
          //Serial.println("Case 2");
          digitalWrite(13, LOW);  //Debugging SPG-Messung


          //Wenn max Anzahl an Werten erreicht, dann Mittelwert aus allen Werten berechnen
          if (Mess_Counter >= Anzahl_Messungen) {
            SensorAdd1 = 0;  //Vorherige Werte wieder löschen
            SensorAdd2 = 0;  //Vorherige Werte wieder löschen
            SensorAdd3 = 0;  //Vorherige Werte wieder löschen
            SensorAdd4 = 0;  //Vorherige Werte wieder löschen
            SensorAdd5 = 0;  //Vorherige Werte wieder löschen
            SensorAdd6 = 0;  //Vorherige Werte wieder löschen

            //Mittelwert berechnen Kanal 1 und 2
            for (byte i = 0; i < Anzahl_Messungen; i++) {
              SensorAdd1 += sensorValue1[i];  //Werte von Kanal 1 miteinander Addieren
              SensorAdd2 += sensorValue2[i];  //Werte von Kanal 2 miteinander Addieren
              SensorAdd3 += sensorValue3[i];  //Werte von Kanal 1 miteinander Addieren
              SensorAdd4 += sensorValue4[i];  //Werte von Kanal 2 miteinander Addieren
              SensorAdd5 += sensorValue5[i];  //Werte von Kanal 1 miteinander Addieren
              SensorAdd6 += sensorValue6[i];  //Werte von Kanal 2 miteinander Addieren
            }
            SensorMittelwert1 = SensorAdd1 >> 2;  //Addierte Werte des ersten Kanals durch 4 teilen -> Rightshift um 2
            SensorMittelwert2 = SensorAdd2 >> 2;  //Addierte Werte des ersten Kanals durch 4 teilen -> Rightshift um 2
            SensorMittelwert3 = SensorAdd3 >> 2;  //Addierte Werte des ersten Kanals durch 4 teilen -> Rightshift um 2
            SensorMittelwert4 = SensorAdd4 >> 2;  //Addierte Werte des ersten Kanals durch 4 teilen -> Rightshift um 2
            SensorMittelwert5 = SensorAdd5 >> 2;  //Addierte Werte des ersten Kanals durch 4 teilen -> Rightshift um 2
            SensorMittelwert6 = SensorAdd6 >> 2;  //Addierte Werte des ersten Kanals durch 4 teilen -> Rightshift um 2

            U_in[1] = SensorMittelwert1;
            U_in[2] = SensorMittelwert2;
            U_in[3] = SensorMittelwert3;
            U_in[4] = SensorMittelwert4;
            U_in[5] = SensorMittelwert5;
            U_in[6] = SensorMittelwert6;
            //digitalWrite(LED_y, HIGH);

            //Wenn Widerstandsmessung abgeschlossen dann weitere Sensorwerte einlesen
            Sensor_in1 = analogRead(analogInPin7);
            Sensor_in2 = analogRead(analogInPin8);
            Sensor_in3 = analogRead(analogInPin9);
            Sensor_in4 = analogRead(analogInPin10);

            //------------------------------------------------------------------------------
            //Hallo Neven, hier könnte dein Code stehen. Die Sensorwerte werden eingelesen (z.B. int Sensor_in1). Es wird direkt die Spannung am Eingang gemessen. Messauflösung 12Bit 0 bis 3V3
            //Umrechnung Stromsignal 4mA = 0 digit, 20mA = 4095 digit
            //Wenn du den Wert umrechnest diesen einfach wieder in die gleiche Variable schreiben. Diese wird anschließend in Case 3 an die Kommunikationsfunktion übergeben.


            //------------------------------------------------------------------------------

            Mess_Counter = 0;  //Messcounter zurücksetzen


            // Verzweigung mit Kalibration
            // Sollange die Kalibration durchgeführt wird werden die gemessene Spannungen aufsummiert.
            if (cali_flag == 1) {
              sum_U_in[Calib_Ch] += U_in[Calib_Ch];  //Gemessene Werte aufsummieren.
              countF++;
              //Serial.print("sum_U_in ");
              //Serial.println(sum_U_in[Calib_Ch]);
            }

            //Serial.println("Case 2 to 3");
            Step++;  //Weiter zum nächsten Schritt
          }
        }
      }
      break;
    case 3:  //Messungen übertragen und neuen DutyCycle Empfangen
      {
        //Serial.println("Step 3");   // send Text

        R_out1 = R_KAL(U_in[1], R_Multi[1], R_Add[1]);  //Widerstandswert aus gemessener Spannung berechnen.
        R_out2 = R_KAL(U_in[2], R_Multi[2], R_Add[2]);  //Widerstandswert aus gemessener Spannung berechnen.
        R_out3 = R_KAL(U_in[3], R_Multi[3], R_Add[3]);  //Widerstandswert aus gemessener Spannung berechnen.
        R_out4 = R_KAL(U_in[4], R_Multi[4], R_Add[4]);  //Widerstandswert aus gemessener Spannung berechnen.
        R_out5 = R_KAL(U_in[5], R_Multi[5], R_Add[5]);  //Widerstandswert aus gemessener Spannung berechnen.
        R_out6 = R_KAL(U_in[6], R_Multi[6], R_Add[6]);  //Widerstandswert aus gemessener Spannung berechnen.

        // DEBUGGING FESTE WERTE
        // 888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888
        //R_out_1 = UtoR(U_in[1], I_mess1); // Berechnung Widerstand 1
        //R_out1 = 3000;
        // R_out_2 = UtoR(U_in2,I_leis2); // Berechnung Widerstand 2
        //R_out2 = 3010;
        // R_out_3 = UtoR(U_in1, I_leis1); // Berechnung Widerstand 1
        //R_out3 = 3020;
        // R_out_4 = UtoR(U_in2,I_leis2); // Berechnung Widerstand 2
        //R_out4 = 3030;
        // R_out_5 = UtoR(U_in1, I_leis1); // Berechnung Widerstand 1
        //R_out5 = 3040;
        // R_out_6 = UtoR(U_in2,I_leis2); // Berechnung Widerstand 2
        //R_out6 = 3050;

        // DEBUGGING FESTE WERTE
        // 888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888

        /*--------------------------------------------------------------*/

        //Wenn in Loop dann Daten übertragen
        if (flag_loop >= 1) {
          Wert1out = 222;  //6 der 8 Ausgabebytes definieren für nächste Komunikaiton
          Wert2out = R_out1;
          Wert3out = R_out2;
          Wert4out = R_out3;
          Wert5out = R_out4;
          Wert6out = R_out5;
          Wert7out = R_out6;
          Wert8out = Sensor_in1;
          Wert9out = Sensor_in2;
          Wert10out = Sensor_in3;
          Wert11out = Sensor_in4;
          //Serial.print("R_out_1 ");

          /*//
          //Debuging
          R_out1_sum += R_out1;
          R_out2_sum += R_out2;
          R_out3_sum += R_out3;
          R_out4_sum += R_out4;
          R_out5_sum += R_out5;
          R_out6_sum += R_out6;

          if (Debug_i >= 64) {
            Debug_i = 0;

            Serial.print("  U_in1 ");
            Serial.print(U_in[1]);
            //Serial.print("  R_Multi1 ");
            //Serial.print(R_Multi[1]);
            //Serial.print("  R_Add1 ");
            //Serial.print(R_Add[1]);
            Serial.print("  R_out1 ");
            Serial.print(R_out1_sum / 64);
            Serial.print("  R_out2 ");
            Serial.print(R_out2_sum / 64);
            Serial.print("  R_out3 ");
            Serial.print(R_out3_sum / 64);
            Serial.print("  R_out4 ");
            Serial.print(R_out4_sum / 64);
            Serial.print("  R_out5 ");
            Serial.print(R_out5_sum / 64);
            Serial.print("  R_out6 ");
            Serial.println(R_out6_sum / 64);

            R_out1_sum = 0;
            R_out2_sum = 0;
            R_out3_sum = 0;
            R_out4_sum = 0;
            R_out5_sum = 0;
            R_out6_sum = 0;

          } else {
            Debug_i++;
          }
          */


          //Test --> manuelle R Calib
          //Wert2out = (U_in1);
          //Wert3out = (U_in2);


          kom_function();  //Komunikation durchführen. Diese MUSS in der Statemachine erfolgen und nicht im loop



          //Loop Steuerung
          if (StatusIn == 1) {
            flag_loop = 1;  //Lopp im Backup Modus durchführen
          } else if (StatusIn == 2) {
            flag_loop = 2;  //Loop mit Leistungsquelle
          } else if (StatusIn == 3) {
            flag_loop = 3;  //Loop mit Stromquelle
          } else            //Wenn keine Einstellung vorgenommen wird dann immer als Stromquelle arbeiten
          {
            flag_loop = 3;  //Loop mit Stromquelle
          }
          //Loop Steuerung ENDE

          P_in1 = Wert1;  //Leistungen übergeben
          P_in2 = Wert2;
          P_in3 = Wert3;
          P_in4 = Wert4;
          P_in5 = Wert5;
          P_in6 = Wert6;

          I_in1 = Wert1;  //Stromstärke übergeben
          I_in2 = Wert2;
          I_in3 = Wert3;
          I_in4 = Wert4;
          I_in5 = Wert5;
          I_in6 = Wert6;
        }

        //Wenn Kalibrierung durchgeführt wird direkt weiterspringen in nächsten Schritt
        if (cali_flag != 0) {
          Step++;
        }

        //Wichtige Funktionen nochmals aufrufen. Zeitkritisch
        SoftwarePWM();  //SoftwarePWM abarbeiten
        Test_Code();         //Testen/Debugging
        PWMout();  //SoftwarePWM Werte ausgeben (DAC0 bis 3)


        if (flag_loop == 1)  //Ansteuerung über Backuplösung für den DAC.
        {
          flag_com = 0;
          // P_in1 = 50; //mW
          // P_in2 = 150; //mW
          // P_in3 = 250; //mW

          T_duty_cycle1 = Duty_Calc(P_in1, R_out1, I_leis1);  //Im Loop finden hier die Leistungsregelung statt.
          T_duty_cycle2 = Duty_Calc(P_in2, R_out2, I_leis1);  //Alle mit gleichem Spitzenstrom
          T_duty_cycle3 = Duty_Calc(P_in3, R_out3, I_leis1);
          T_duty_cycle4 = Duty_Calc(P_in4, R_out4, I_leis1);
          T_duty_cycle5 = Duty_Calc(P_in5, R_out5, I_leis1);
          T_duty_cycle6 = Duty_Calc(P_in6, R_out6, I_leis1);
          Step++;
        } else if (flag_loop == 2)  //Ansteuerung mit DAC AD5064BRUZ-1 --> noch nicht implementiert
        {
          flag_com = 0;
          T_duty_cycle1 = Duty_Calc(P_in1, R_out1, I_leis1);  //Im Loop finden hier die Leistungsregelung statt.
          T_duty_cycle2 = Duty_Calc(P_in2, R_out2, I_leis1);  //Analogsignale werden über den DAC erzeugt (Dieser wird über den SPI angesteuert).
          T_duty_cycle3 = Duty_Calc(P_in3, R_out3, I_leis1);
          T_duty_cycle4 = Duty_Calc(P_in4, R_out4, I_leis1);
          T_duty_cycle5 = Duty_Calc(P_in5, R_out5, I_leis2);
          T_duty_cycle6 = Duty_Calc(P_in6, R_out6, I_leis2);
          Step++;
        } else if (flag_loop == 3)  //Ausgabe als Stromquelle nicht Leistungsquelle (open loop)
        {
          flag_com = 0;
          //Serial.println("loop 3");

          //I_in1 = 150; //mA
          //I_in2 = 50; //mA
          //I_in3 = 250; //mA
          T_duty_cycle1 = Duty_Calc_CurrentSource(I_in1, I_leis1);  //Im Loop finden hier die Stromsteuerung statt.
          T_duty_cycle2 = Duty_Calc_CurrentSource(I_in2, I_leis1);  //Analogsignale werden über den DAC erzeugt (Dieser wird über den SPI angesteuert).
          T_duty_cycle3 = Duty_Calc_CurrentSource(I_in3, I_leis1);
          T_duty_cycle4 = Duty_Calc_CurrentSource(I_in4, I_leis1);
          T_duty_cycle5 = Duty_Calc_CurrentSource(I_in5, I_leis2);  //Spitzenstrom Kann für Kanal 5 und 6 Separat eingestellt werden.
          T_duty_cycle6 = Duty_Calc_CurrentSource(I_in6, I_leis2);

          Step++;
        }

        else {
        }
      }



      break;
    case 4:  //DutyCycle einstellen
      {





        REG_PWM_CDTY0 = T_duty_cycle1 + MessDauer;  //Duty Cycle des Leistungspuls übergeben Kanal1
        REG_PWM_CDTY1 = T_duty_cycle2 + MessDauer;  //Duty Cycle des Leistungspuls übergeben Kanal2
        REG_PWM_CDTY2 = T_duty_cycle3 + MessDauer;  //Duty Cycle des Leistungspuls übergeben Kanal3
        REG_PWM_CDTY3 = T_duty_cycle4 + MessDauer;  //Duty Cycle des Leistungspuls übergeben Kanal4
        REG_PWM_CDTY4 = T_duty_cycle5 + MessDauer;  //Duty Cycle des Leistungspuls übergeben Kanal5
        REG_PWM_CDTY5 = T_duty_cycle6 + MessDauer;  //Duty Cycle des Leistungspuls übergeben Kanal6

        //Serial.println("Case 4");
        Step++;  //Statflow zurück auf Default
      }
    case 5:  //Gain einstellen
      {
        //Serial.println("Step 5");   // send Text

        Step = 0;                  //Statflow zurück auf Default
        digitalWrite(LED_r, LOW);  //rote LED aus am Ende des Stateflow
      }
      break;
    default:  //Auslesen wenn Periode neu startet
      {
        //Serial.println("default_in");   // send Text
        PWM_Status = REG_PWM_ISR1 &= 0x00000001;  //PWM Statusregister Bit 1 auslesen --> wird High bei Start der Periode
        if (PWM_Status == 1) {                    //Wenn Periode neu Startet weiter zu Step 1

          //digitalWrite(13, HIGH);                           //Board LED High setzten für Debbuging  --> Debugging SPG-Messung
          //digitalWrite(LED_r, HIGH);                        //rote LED aus am Ende des Stateflow    --> Debugging Statflow
          //Serial.println("Main_begin");   // send Text
          //Zeit starten bis zur ersten Messung
          T_mess_on = GLtime;
          //Weiter zu Step 1
          Step = 1;
        }
      }
  }  //Ende Statflow
}
