// Einheiten in der rechteckigen Klammer [] beziehen sich auf die Einheit nach der Umrechnung
/********************************************/
// Ablauf der Kalibration


void calibration_flow() {

  //Sollange cali_flag ungleich 0 soll die Kalibrierung durchgeführt werden
  //Wenn die Kalibrierung beendet ist soll dieses auf 0 gesetzt werden.
  if (cali_flag != 0) {
        

    switch (StepC) {
      //Auswahl des Kalibrationskanals
      case 1:
        {
          //Serial.println("Case 1");

          digitalWrite(LED_g, HIGH);
          digitalWrite(LED_y, HIGH);
          //Array neu beschreiben zur Sicherheit, dass mehrere Kanäle nicht gleichzeitig kalibrieren
          //Ein und Ausschalten der Kalibrierwiderstände
          Calib_CHx_ON_OFF[1] = 1;
          Calib_CHx_ON_OFF[2] = 1;
          Calib_CHx_ON_OFF[3] = 1;
          Calib_CHx_ON_OFF[4] = 1;
          Calib_CHx_ON_OFF[5] = 1;
          Calib_CHx_ON_OFF[6] = 1;
          //Jeweiligen Kanal aktivieren der Kalibriert werden soll. Wenn wert auf 0 wird der Stromfluss auf die Kalibrierwiderstände geleitet
          Calib_CHx_ON_OFF[Calib_Ch] = 0;

          //Nur zu Kalibrierenden Kanal enabeln
          CHx_ENABLE_out[1] = 0;  //CHx  0 = einschalten, 1 = ausschalten
          CHx_ENABLE_out[2] = 0;  //CHx  0 = einschalten, 1 = ausschalten
          CHx_ENABLE_out[3] = 0;  //CHx  0 = einschalten, 1 = ausschalten
          CHx_ENABLE_out[4] = 0;  //CHx  0 = einschalten, 1 = ausschalten
          CHx_ENABLE_out[5] = 0;  //CHx  0 = einschalten, 1 = ausschalten
          CHx_ENABLE_out[6] = 0;  //CHx  0 = einschalten, 1 = ausschalten
          CHx_ENABLE_out[Calib_Ch] = 0;

          StepC++;
          countF = 0;  //Zählung der Messung zurücksetzen für Case 2
        }

      //Kleinern Kalbirationswiderstand messen
      case 2:
        {
          //Serial.println("Case 2");
          //Kleiner Widerstand einstellen
          Calib_R1_ON_OFF = ON;
          Calib_R2_ON_OFF = OFF;
          

          if (StepC == 2) {
            //Serial.print("Main Step ");
            //Serial.println(Step);
                    
            // Mittelwert Bit-U berechnen
            if (countF >= AnzMessungenCalib) {
              sum_U_in[Calib_Ch] = sum_U_in[Calib_Ch] / (countF);  //Mittelwert des Summierten Spannungswerte bilden

              Bit_min = sum_U_in[Calib_Ch];  //gemessener Mittelwert übergeben
              sum_U_in[Calib_Ch] = 0;
              StepC++;  //Weiter zu nächsten Schritt
              digitalWrite(LED_g, LOW);

              //Serial.print("Bit_min ");
              //Serial.println(Bit_min);

              countF = 0;  //Zählung der Messung zurücksetzen für Case 3
            }
          }
        }

        break;

      //Großen Kalbirationswiderstand messen
      case 3:
        {
          //Serial.println("Case 3");
          //Großer Kalibrationswiderstand einstellen
          Calib_R1_ON_OFF = OFF;
          Calib_R2_ON_OFF = ON;
          
          if (StepC == 3) { 

            // Mittelwert Bit-U berechnen
            if (countF >= AnzMessungenCalib) {
              sum_U_in[Calib_Ch] = sum_U_in[Calib_Ch] / (countF);  //Mittelwert des Summierten Spannungswerte bilden

              Bit_max = sum_U_in[Calib_Ch];  //gemessener Mittelwert übergeben
              sum_U_in[Calib_Ch] = 0;
              StepC = 4;  //Weiter zu nächsten Schritt
              //Serial.print("Bit_max ");
              //Serial.println(Bit_max);
            }
          }
        }
        break;
      case 4:
        {
          //Serial.println("Case 4");
          function_R();  //Widerstandsmessung CH1 und Ch2 linearisieren.
          //Kalibrierung wieder von vorne beginnen bis alle 6 Kanäle fertig sind.
          StepC = 0;   //zurück zu default
          Calib_Ch++;  //nächster Kanal
        }
        break;
      default:
        

        if (Calib_Ch <= 6)  //Sollange Kalibrieren bis alle 6 Kanäle abgearbeitet sind.
        {
          //Serial.print("Kalib_Ch ");
        //Serial.println(Calib_Ch);
          digitalWrite(LED_y, HIGH);  
          StepC = 1;  //In Step 1 springen
        } else if (Calib_Ch >= 7) {
          cali_flag = 0;  //Wenn alle Kanäle Kalibriert wurden, dann Kalibration beenden und in Loop springen
          //Serial.println("Kalib_END ");
          //Alle Kalibrierkanäle ausschalten
          Calib_CHx_ON_OFF[1] = 1;
          Calib_CHx_ON_OFF[2] = 1;
          Calib_CHx_ON_OFF[3] = 1;
          Calib_CHx_ON_OFF[4] = 1;
          Calib_CHx_ON_OFF[5] = 1;
          Calib_CHx_ON_OFF[6] = 1;

          //LED durchlauf als Kalibrierung abgeschlossen
          digitalWrite(LED_g, HIGH);
          delay(500);
          digitalWrite(LED_g, LOW);
          digitalWrite(LED_y, HIGH);
          delay(500);
          digitalWrite(LED_y, LOW);
          digitalWrite(LED_r, HIGH);
          delay(500);
          digitalWrite(LED_r, LOW);
          
          flag_loop = 3; //Loop aktivieren zu Beginn lediglich mit der Stromquelle starten. flag_loop = 1 --> Leistungsquelle
          LED_y_ontime = 0;

        } else {
          Calib_Ch = 0;
        }


        break;
    }
  }
}

void calibration_direct() {

  //Einstellbyte für die Gainsteuerung der PGA202/203 Instrumentenverstärker
  //Werte übernehmen die auf der Platine manuell eingestellt wurden
  //Gültige Werte sind 1, 2, 4, 8, 10, 100, 1000
  PGA_Shunt_1_Gain = 8;
  PGA_Shunt_2_Gain = PGA_Shunt_1_Gain;
  PGA_Shunt_3_Gain = PGA_Shunt_1_Gain;
  PGA_Shunt_4_Gain = PGA_Shunt_1_Gain;
  PGA_Shunt_5_Gain = PGA_Shunt_1_Gain;
  PGA_Shunt_6_Gain = PGA_Shunt_1_Gain;

  PGA_SMA_1_Gain = 1;
  PGA_SMA_2_Gain = PGA_SMA_1_Gain;
  PGA_SMA_3_Gain = PGA_SMA_1_Gain;
  PGA_SMA_4_Gain = PGA_SMA_1_Gain;
  PGA_SMA_5_Gain = PGA_SMA_1_Gain;
  PGA_SMA_6_Gain = PGA_SMA_1_Gain;
  //PGAcontrol();
  //PGAout();

  //Werte in mA
  //I_sp1 = 500;
  //I_sp2 = 500;
  //I_leis1 = I_Calc_Leis(I_sp1);  // Kompensation von Isp um die Länge des Messpulses
  //I_leis2 = I_Calc_Leis(I_sp2);
  //I_mess1 = I_Calc_Mess(I_leis1);  // Berechnung von Isp des Messpulses --> Kann auch direkt vorgegeben werden.
  //I_mess2 = I_Calc_Mess(I_leis2);

  I_mess1 = 65;  //mA
  I_leis1 = 300;  //mA
  I_leis2 = I_leis1;

  int bitDAC0;
  int bitDAC1;
  int bitDAC2;
  int bitDAC3;

  float R_Shunt = 0.1;
  //Berechnung der Bit-U anhand der Stromstärke und des Gain
  //Der Shuntgain beschreibt in diesem Fall eine Art Übersetzungsfaktor zwischen Analoge Ausgangsspannung des Arduino und der Stromspitze der Stromquelle.
  //Shuntwiderstand 0.1 Ohm.
  //Bei Gain 1 ist die Übersetzung bei 0.1. Das heist, wenn der Arduino 0.1V Ausgibt dann gibt die Stromquelle auch 1A aus.
  //Bei Gain 8 ist die Übersetzung bei 0.8 Das heist, wenn der Arduino 0.8V Ausgibt dann gibt die Stromquelle auch 1A aus usw.
  //D Arduino DUE kann maximal 3,3V ausgeben.

  //Backup Lösung über PT1 Glied auf der PCB --> Analogwert generierung über 2x 10µF Kondensatoren
  bitDAC0 = Bit_DAC0_Calc(I_mess1 * PGA_Shunt_1_Gain * R_Shunt);
  bitDAC1 = Bit_DAC1_Calc(I_leis1 * PGA_Shunt_1_Gain * R_Shunt);
  //Serial.print("DAC0 ");
  //Serial.println(bitDAC0);
  //Serial.print("DAC1 ");
  //Serial.println(bitDAC1);

  //Analogwerte für die Stromspitzen einstellen und ausgeben
  Spg_Messpuls_1 = bitDAC0;       //Wert für DAC0 0-52500 Schritte = 0V bis 3,3V
  Spg_Leistungspuls_1 = bitDAC1;  //Wert für DAC1 0-52500 Schritte = 0V bis 3,3V
  Spg_Messpuls_2 = bitDAC2;       //Wert für DAC0 0-52500 Schritte = 0V bis 3,3V
  Spg_Leistungspuls_2 = bitDAC3;  //Wert für DAC1 0-52500 Schritte = 0V bis 3,3V
                                  /*
      R_Multi_1 = 0.0060618307;  // Steigung Bit-Widerstand-Geraden Kanal1
      R_Multi_2 = 0.0093023256;  // Steigung Bit-Widerstand-Geraden Kanal2
      R_Add_1 = 0.1468983633;    // Y-Achsenabschnite Bit-Widerstand-Geraden Kanal1
      R_Add_2 = 0.3153488372;    // Y-Achsenabschnite Bit-Widerstand-Geraden Kanal2
      */

  SoftwarePWM();  //SoftwarePWM abarbeiten
  PWMout();       //SoftwarePWM Werte ausgeben (DAC0 bis 3)
}




//---------------------------------------------------------------------------------------------------------------------------------------------
// Berechnung der Mess- und Leistungsstromsärke -->  Isp_Max des Drahtes wird übermittlet. Da wir jedoch einen Messpuls verwenden kann die Isp erhöht werden, um im Mittel wieder auf die eigenliche Isp_max des Drahtes zu kommen.
float I_Calc_Leis(float I_sp) {
  float isp = ((float(I_sp)) / 1000);  // Umrechnung int in float [mA]
  float t_leis = (t_duty - t_mess);
  float I_leis = 0.0;
  I_leis = isp / (t_leis / t_duty);
  return I_leis;
}
float I_Calc_Mess(float I_leis)  // Berechnung von Isp des Messpulses --> Kann auch direkt vorgegeben werden.
{
  float t_leis = (t_duty - t_mess);
  float I_mess = 0.0;
  I_mess = sqrt((x_leis / (1 - x_leis)) * I_leis * I_leis * (t_leis / t_mess));
  return I_mess;
}


// Berechnung der Bitwerte Stromstärke Messpuls Kanal 1
int Bit_DAC0_Calc(float iBit) {
  float bit_calc;
  bit_calc = iBit * 15.91;  //Neu Kalibriert auf Software PWM bei einer Baudrate von 234000. Werte kleiner 0,266V bzw. 4000Bit dürfen wegen Timingproblemen nicht verwendet werden.
  bit_calc = round(bit_calc);
  int bitI = bit_calc;
  return bitI;
}
// Berechnung der Bitwerte Stromstärke Leistungspuls Kanal 1
int Bit_DAC1_Calc(float iBit) {
  float bit_calc;
  //bit_calc=iBit*1253.3+4.238;
  //bit_calc=iBit*1251.9+3.4377; 16155 - 241
  bit_calc = iBit * 15.91;  //Neu Kalibriert auf Software PWM bei einer Baudrate von 234000. Werte kleiner 0,266V bzw. 4000Bit dürfen wegen Timingproblemen nicht verwendet werden.
  bit_calc = round(bit_calc);
  int bitI = bit_calc;
  return bitI;
}





// Berechnung der c
void function_R() {
  R_Multi[Calib_Ch] = ((R2_Calib - R1_Calib) / (Bit_max - Bit_min));
  R_Add[Calib_Ch] = (R2_Calib - (R_Multi[Calib_Ch] * Bit_max));
  R_Multi[Calib_Ch] = R_Multi[Calib_Ch]; //*0.88;
  R_Add[Calib_Ch] = R_Add[Calib_Ch]; //+130;
  //Serial.print("R_Multi ");
  //Serial.print(R_Multi[Calib_Ch]);
  //Serial.print("  R_ADD ");
  //Serial.println(R_Add[Calib_Ch]);
}

/*
float calc_PmaxLeis(float iLeis, float rMax) {
  float t_leis = (t_duty - t_mess);
  float pLeis = 0;
  pLeis = (rMax * (iLeis * iLeis) * t_leis) / t_duty;
  return pLeis;
}
*/


/*
Ein und Ausschalten der Kalibirerwiderstände
Es dürfen nie 2 Kanäle gleichzeitig auf einen Kalibrierwiderstand geschaltet werden. 
*/
void PowerRoutingOut() {

  digitalWrite(Calib_CH1_PIN, Calib_CHx_ON_OFF[1]);
  digitalWrite(Calib_CH2_PIN, Calib_CHx_ON_OFF[2]);
  digitalWrite(Calib_CH3_PIN, Calib_CHx_ON_OFF[3]);
  digitalWrite(Calib_CH4_PIN, Calib_CHx_ON_OFF[4]);
  digitalWrite(Calib_CH5_PIN, Calib_CHx_ON_OFF[5]);
  digitalWrite(Calib_CH6_PIN, Calib_CHx_ON_OFF[6]);
  digitalWrite(Calib_R1_PIN, Calib_R1_ON_OFF);
  digitalWrite(Calib_R2_PIN, Calib_R2_ON_OFF);
}
