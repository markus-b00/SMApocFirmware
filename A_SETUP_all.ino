/*
  für SMAPOC_PreVersion_01
  SMAPOC -> SMA POwer Controller

  Allgemeine Setup Funktion für den SMAPOC

  
  created 29 November  2019
  modifed 12 Januar  2025
  by Philip Frenzel
  mechatronic factory GmbH

*/



void SETUP_all() {
  // initialize serial communication:

  //Serial1.begin(230400);      //Baudrate für 100Hz Taktrate

  Serial.begin(250000);   //Für Direkte ansteuerung über PC und USB verbindung an Arduino
  Serial.setTimeout(.5);  // Timeout 0.05 sec
  pinMode(RTS, OUTPUT);   //RTS Output

  //Serial.println("Setup");

  pinMode(19, INPUT);  //RX1 als Eingang definieren

  analogWriteResolution(12);  //Auflösung auf 12 Bit erhöhen
  analogReadResolution(12);   //auflösung auf 12 Bit erhöhen
  pinMode(RTS, OUTPUT);
  pinMode(CTS, OUTPUT);
  pinMode(13, OUTPUT);  //Üin für Arduino LED auf Ausgang stellen

  pinMode(LED_g, OUTPUT);  //grüne LED
  pinMode(LED_y, OUTPUT);  //gelbe LED
  pinMode(LED_r, OUTPUT);  //rote LED

  pinMode(CH1_ENABLE, OUTPUT);  //OPA548 E/S Kanal 1
  pinMode(CH2_ENABLE, OUTPUT);  //OPA548 E/S Kanal 2
  pinMode(CH3_ENABLE, OUTPUT);  //OPA548 E/S Kanal 3
  pinMode(CH4_ENABLE, OUTPUT);  //OPA548 E/S Kanal 4
  pinMode(CH5_ENABLE, OUTPUT);  //OPA548 E/S Kanal 5
  pinMode(CH6_ENABLE, OUTPUT);  //OPA548 E/S Kanal 6

  CHx_ENABLE_out[1] = 1;  //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[2] = 1;  //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[3] = 1;  //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[4] = 1;  //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[5] = 1;  //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[6] = 1;  //CHx  0 = einschalten, 1 = ausschalten
  digitalWrite(CH1_ENABLE, CHx_ENABLE_out[1]);
  digitalWrite(CH2_ENABLE, CHx_ENABLE_out[2]);
  digitalWrite(CH3_ENABLE, CHx_ENABLE_out[3]);
  digitalWrite(CH4_ENABLE, CHx_ENABLE_out[4]);
  digitalWrite(CH5_ENABLE, CHx_ENABLE_out[5]);
  digitalWrite(CH6_ENABLE, CHx_ENABLE_out[6]);

  pinMode(Calib_CH1_PIN, OUTPUT);  //Kalibrierpin Ch1
  pinMode(Calib_CH2_PIN, OUTPUT);  //Kalibrierpin Ch2
  pinMode(Calib_CH3_PIN, OUTPUT);  //Kalibrierpin Ch3
  pinMode(Calib_CH4_PIN, OUTPUT);  //Kalibrierpin Ch4
  pinMode(Calib_CH5_PIN, OUTPUT);  //Kalibrierpin Ch5
  pinMode(Calib_CH6_PIN, OUTPUT);  //Kalibrierpin Ch6
  pinMode(Calib_R1_PIN, OUTPUT);   //Kalibrierpin Widerstand 1
  pinMode(Calib_R2_PIN, OUTPUT);   //Kalibrierpin Widerstand 2

  //
  digitalWrite(Calib_CH1_PIN, Calib_CHx_ON_OFF[1]);
  digitalWrite(Calib_CH2_PIN, Calib_CHx_ON_OFF[2]);
  digitalWrite(Calib_CH3_PIN, Calib_CHx_ON_OFF[3]);
  digitalWrite(Calib_CH4_PIN, Calib_CHx_ON_OFF[4]);
  digitalWrite(Calib_CH5_PIN, Calib_CHx_ON_OFF[5]);
  digitalWrite(Calib_CH6_PIN, Calib_CHx_ON_OFF[6]);
  digitalWrite(Calib_R1_PIN, Calib_R1_ON_OFF);
  digitalWrite(Calib_R2_PIN, Calib_R2_ON_OFF);




  pinMode(Switch1, INPUT);  //Taster 1
  pinMode(Switch2, INPUT);  //Taster 2




  //Handshake Com
  digitalWrite(RTS, HIGH);
  digitalWrite(CTS, HIGH);


  //Softwarseitige PWM Ausgabe
  pinMode(analogOutPinDAC1, OUTPUT);  //Software PWM DAC0    PEM_DAC_LEIS_BACKUP
  //pinMode(analogOutPinDAC1, OUTPUT);    //Software PWM DAC1
  //pinMode(analogOutPinDAC2, INPUT);    //Software PWM DAC2    --> Auf Input umgestellt, da nun die "echte" PWM von Pin 7 verwendet wurde
  //pinMode(analogOutPinDAC3, OUTPUT);    //Software PWM DAC3

  digitalWrite(analogOutPinDAC1, LOW);
  //digitalWrite(analogOutPinDAC1, LOW);
  //digitalWrite(analogOutPinDAC2, LOW);
  //digitalWrite(analogOutPinDAC3, LOW);

  //---------------------------------------------------------------------
  //Prüfen ob eine externe Spannungsquelle angeschlossen ist.
  Mess_Counter = 0;
  U_Ref_Bit = 1000;
  while (1) {
    
    delay(1);
    Mess_Counter++;
    U_Ref_Bit_sum += analogRead(analogInPin12);  //Referenzspannung messen

    if (Mess_Counter <= 200) digitalWrite(LED_r, HIGH);
    else digitalWrite(LED_r, LOW);

    if (Mess_Counter >= 400) {
      U_Ref_Bit = U_Ref_Bit_sum / 400;
      U_Ref_Bit_sum = 0;
      Mess_Counter = 0;
      //Serial.print("Ref Messung ");
      //Serial.println(U_Ref_Bit);
      Switch2_in = digitalRead(Switch2); //Falls Störungen auftreten weiter mit Taster
    }

    //Wenn die gemessene Spannung über 0,6V liegt dann ist eine Externe Spannungsquelle angeschlossen
    if (U_Ref_Bit <= 420) {
      digitalWrite(LED_g, HIGH);
      delay(1000);  //Eine Sekunde warten bis die Spannung sich stabilisiert hat
      break;
    }
    else if (Switch2_in == 1) {
      break;
    }
  }
  Mess_Counter = 0;
  digitalWrite(LED_g, LOW);
  digitalWrite(LED_r, LOW);
  //--------------------------------------------------------------------------

  //Enablesignale Ausgeben bevor LOOP beginnt

  CHx_ENABLE_out[1] = 0;                        //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[2] = 0;                        //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[3] = 0;                        //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[4] = 0;                        //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[5] = 0;                        //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[6] = 0;                        //CHx  0 = einschalten, 1 = ausschalten
  digitalWrite(CH1_ENABLE, CHx_ENABLE_out[1]);  //Enablestatus Ch1 Ausgeben --> Beim Hochfahren die Stromquellen immer abschalten, damit des SMA-Draht nicht beschädigt wird.
  digitalWrite(CH2_ENABLE, CHx_ENABLE_out[2]);  //Enablestatus Ch2 Ausgeben --> Wenn CHx_ENABLE_out = 1 dann sind die Stromquellen deaktiviert.
  digitalWrite(CH3_ENABLE, CHx_ENABLE_out[3]);  //Enablestatus Ch3 Ausgeben --> Beim Hochfahren die Stromquellen immer abschalten, damit des SMA-Draht nicht beschädigt wird.
  digitalWrite(CH4_ENABLE, CHx_ENABLE_out[4]);  //Enablestatus Ch4 Ausgeben --> Wenn CHx_ENABLE_out = 1 dann sind die Stromquellen deaktiviert.
  digitalWrite(CH5_ENABLE, CHx_ENABLE_out[5]);  //Enablestatus Ch5 Ausgeben --> Beim Hochfahren die Stromquellen immer abschalten, damit des SMA-Draht nicht beschädigt wird.
  digitalWrite(CH6_ENABLE, CHx_ENABLE_out[6]);  //Enablestatus Ch6 Ausgeben --> Wenn CHx_ENABLE_out = 1 dann sind die Stromquellen deaktiviert.


  //PGAsetup();                 //Instrumentenverstärker konfigurieren

  TimerStart(TC1, 0, TC3_IRQn);  //Timer Starten (Timer 1, Kanal 0, Interrupt Handler aus Tabelle
  PWMsetup();                    //PWM Modul init

/*
  //SPI SETUP
  pinMode(CS_DAC_AD5064, OUTPUT);     //CS für DAC
  digitalWrite(CS_DAC_AD5064, HIGH);  //CS auf HIGH
  pinMode(LDAC_AD5064, OUTPUT);
  digitalWrite(LDAC_AD5064, LOW);

  // SPI-Schnittstelle initialisieren
  SPI.begin();  // Standard SPI Pins werden genutzt
  SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE1));
  SPI.transfer(0xAA);
  SPI.transfer(0xAA);
  SPI.transfer(0xAA);
  SPI.transfer(0xAA);
  SPI.transfer(0xAA);
  SPI.transfer(0xAA);
  SPI.transfer(0xAA);
  SPI.transfer(0xAA);
  SPI.transfer(0xFF);
  SPI.transfer(0xAA);
  SPI.transfer(0x01);
  SPI.transfer(0xAA);
  SPI.transfer(0xAA);
  // DAC Ausgänge einmalig einstellen:
  writeDAC(0, 32768);  // Kanal A (50% der Referenzspannung)
  writeDAC(1, 16384);  // Kanal B (25% der Referenzspannung)
  writeDAC(2, 49152);  // Kanal C (75% der Referenzspannung)
  writeDAC(3, 65535);  // Kanal D (100% der Referenzspannung)

  SPI.endTransaction();  // SPI Transaktion abschließen
*/

  //----------------------------------------------------------------------------------
  //Hier sollen die Einstellungen vom dSpace System eingelesen werden.

  //Einstellung für 76µm Draht 150 mm --> 1130 = 71mA --> 0,071V ; 800 = 516mA --> 0,516V
  Spg_Messpuls_1 = 100;       //Wert für DAC0 0-52500 Schritte = 0V bis 3,3V --> ISp = 71mA
  Spg_Leistungspuls_1 = 200;  //Wert für DAC1 0-52500 Schritte = 0V bis 3,3V --> ISp = 516mA
  Spg_Messpuls_2 = 100;       //Wert für DAC0 0-52500 Schritte = 0V bis 3,3V
  Spg_Leistungspuls_2 = 200;  //Wert für DAC1 0-52500 Schritte = 0V bis 3,3V
  T_mess_on_Dauer = 10;       //42000 = 1ms ; 840 = 20µs  ; 420 = 10µs --> Zeit bis erste Messung im Messpuls ausgeführt wird.
  T_mess_Dauer = 0;           //42000 = 1ms ; 2100 = 50µs ; --> Zeit zwischen den einzelnen Messungen im Messpuls. 0 = so schnell wie möglich Messen.
  //Anzahl_Messungen = 4;               //Anzahl der Spannungsmessungen

  MessDauer = 2625;  //Generelle Messdauer 2100 = 4% bei 100Hz = 400µs
                     //Generelle Messdauer 2625 = 5% bei 100Hz = 500µs
  DutyCycle1 = 0;    //Duty Cycle Leistungspuls Kanal 1
  DutyCycle3 = 0;    //Duty Cycle Leistungspuls Kanal 2

  //----------------------------------------------------------------------------------
  //Platz für Setup Testcode

  //DutyCycle1 = 42000;                     //Duty Cycle Leistungspuls Kanal 1 80%
  //DutyCycle3 = 42000;                     //Duty Cycle Leistungspuls Kanal 2 80%


  //----------------------------------------------------------------------------------
  SoftwarePWM();
  PWMout();  //SoftwarePWM Werte ausgeben (DAC0 bis 3)



  //LED durchlauf als Uploadkontrolle
  digitalWrite(LED_g, HIGH);
  delay(500);
  digitalWrite(LED_g, LOW);
  digitalWrite(LED_y, HIGH);
  delay(500);
  digitalWrite(LED_y, LOW);
  digitalWrite(LED_r, HIGH);
  delay(500);
  digitalWrite(LED_r, LOW);

  //Grüne LED Dauerhaft an für Messung
  digitalWrite(LED_g, HIGH);
  digitalWrite(LED_y, HIGH);
  LED_g_ontime = 6000;  //LED grün gedimmt an
  LED_y_ontime = 6000;
  //LED_r_ontime = 0;
  delay(2000);
  //LED_y_ontime = 0;
  digitalWrite(LED_y, LOW);

  Wert1out = 0;  //6 der 8 Ausgabebytes definieren für nächste Komunikaiton
  Wert2out = 0;
  Wert3out = 0;

  //Hier soll die Calibration durchgeführt werden

  //calibration_flow();           //Kalibrierung durchführen

  //Nach Time x Ch1 bis Ch6 aktivieren
  CHx_ENABLE_out[1] = 0;  //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[2] = 0;  //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[3] = 0;  //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[4] = 0;  //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[5] = 0;  //CHx  0 = einschalten, 1 = ausschalten
  CHx_ENABLE_out[6] = 0;  //CHx  0 = einschalten, 1 = ausschalten
}


// DAC Command Codes
#define CMD_WRITE_AND_UPDATE 0x3  // sofort Ausgabe aktualisieren

// Funktion zum Schreiben eines 16-Bit Werts auf einen DAC-Kanal
void writeDAC(uint8_t channel, uint16_t value) {
  long command_byte = (CMD_WRITE_AND_UPDATE << 24) | ((channel & 0x0F) << 20) | (value << 4);  //COMMAND Bits 0b0010, Adress Bits 0b1111 --> Alle DACs



  digitalWrite(CS_DAC_AD5064, LOW);
  SPI.transfer(0xAA);
  digitalWrite(CS_DAC_AD5064, HIGH);
}