void PWMsetup()
{
  //Hier noch Pin 35, 37, 39 und 41 Einfügen
  //PWM Setup on Pin´s 34 36 38 40
  REG_PWM_WPCR = 0x50574DFC; //Schreibschutz aufheben
  PMC->PMC_PCER1 |= PMC_PCER1_PID36;                  // PWM on

  //Pin 34 (Arduino) PWM_LEIS_CH1
  // PWML0 on PC2, peripheral type B
  PIOC->PIO_PDR |= PIO_PDR_P2;                        // Set PWM pin to peripheral
  PIOC->PIO_ABSR |= PIO_PC2B_PWML0;

  //Pin 36 (Arduino) PWM_LEIS_CH2
  // PWML1 on PC4 ; Peripheral type B
  PIOC->PIO_PDR |= PIO_PDR_P4;                      
  PIOC->PIO_ABSR |= PIO_PC4B_PWML1;              


  //Pin 38 (Arduino) PWM_LEIS_CH3
  // PWML2 on PC6 ; Perpipheral type B
  PIOC->PIO_PDR |= PIO_PDR_P6;
  PIOC->PIO_ABSR |= PIO_PC6B_PWML2;

  //Pin 40 (Arduino) PWM_LEIS_CH4
  // PWML3 on PC8 ; Perpipheral type B
  PIOC->PIO_PDR |= PIO_PDR_P8;
  PIOC->PIO_ABSR |= PIO_PC8B_PWML3;

  
  //Pin 6 (Arduino) PWM_DAC_MESS_BACKUP -->Analog Output des Messpuls Backup
  // PWML7 on PC24 ; Perpipheral type B
  PIOC->PIO_PDR |= PIO_PDR_P24;
  PIOC->PIO_ABSR |= PIO_PC24B_PWML7;

  //Pin 7 (Arduino) PWM_Mess --> Länge des Messpulses für alle 6 Kanäle
  // PWML6 on PC23 ; Perpipheral type B
  PIOC->PIO_PDR |= PIO_PDR_P23;
  PIOC->PIO_ABSR |= PIO_PC23B_PWML6;

  //Pin 8 (Arduino) PWM_LEIS_CH5
  // PWML5 on PC22 ; Perpipheral type B
  PIOC->PIO_PDR |= PIO_PDR_P22;
  PIOC->PIO_ABSR |= PIO_PC22B_PWML5;

  //Pin 9 (Arduino) PWM_LEIS_CH6
  // PWML4 on PC21 ; Perpipheral type B
  PIOC->PIO_PDR |= PIO_PDR_P21;
  PIOC->PIO_ABSR |= PIO_PC21B_PWML4;

  //Archivcode stand hier
  

  // Set synchro channels list : Ch1 bis CH8
  //Disable all channels
  PWM->PWM_DIS = PWM_DIS_CHID0 | PWM_DIS_CHID1 | PWM_DIS_CHID2 | PWM_DIS_CHID3 | PWM_DIS_CHID4 | PWM_DIS_CHID5 | PWM_DIS_CHID6 | PWM_DIS_CHID7;

  PWM->PWM_SCM  = PWM_SCM_SYNC0                                     // Add SYNCx accordingly, at least SYNC0, plus SYNC1 & SYNC2 & SYNC3
                  | PWM_SCM_SYNC1
                  | PWM_SCM_SYNC2
                  | PWM_SCM_SYNC3
                  | PWM_SCM_SYNC4
                  | PWM_SCM_SYNC5
                  | PWM_SCM_SYNC6
                  | PWM_SCM_SYNC7
                  | PWM_SCM_UPDM_MODE1;                             //Automatic write of duty-cycle an period


  // Set duty cycle update period
  //PWM->PWM_SCUP = PWM_SCUP_UPR(UpdatePeriod);                     //???????????????????????????????????
  PWM->PWM_SCUP = PWM_SCUP_UPR(0b0000);

  // Set the PWM Reference channel 0 i.e. : Clock/Frequency/Alignment
  PWM->PWM_CLK = PWM_CLK_PREA(0b0000) | PWM_CLK_DIVA(16);            // Set the PWM clock rate for 84 MHz/8 or 84 MHz/16
  PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_CLKA | PWM_CMR_DTE;     // The period is left aligned, clock source as CLKA on channel 0,
  //PWM->PWM_CH_NUM[0].PWM_CPRD = 10500;                              // Set the PWM frequency  to 1kHz (84 MHz / 8 / 10500 = 1kHz)
  PWM->PWM_CH_NUM[0].PWM_CPRD = 52500;                              // Set the PWM frequency  to 100Hz (84 MHz / 16 / 52500 = 100Hz)
                                                                     

  PWM->PWM_ENA = PWM_ENA_CHID0;                                     // Enable PWM for all channels, channel 0 Enable is sufficient

  
  //REG_PWM_WPSR;   // Write Protect Status Register auslesen um dieses zu clearn

  //Totzeiten in allen Leistungskanäle Kanälen erlauben.
  REG_PWM_CMR0 |= PWM_CMR_DTE;                  
  REG_PWM_CMR1 |= PWM_CMR_DTE;
  REG_PWM_CMR2 |= PWM_CMR_DTE;
  REG_PWM_CMR3 |= PWM_CMR_DTE;
  REG_PWM_CMR4 |= PWM_CMR_DTE;
  REG_PWM_CMR5 |= PWM_CMR_DTE;
  REG_PWM_CMR6 |= PWM_CMR_DTE;                  
  REG_PWM_CMR7 |= PWM_CMR_DTE;

  //PWM Polarität umdrehen
  REG_PWM_CMR0 |= PWM_CMR_CPOL;                  
  REG_PWM_CMR1 |= PWM_CMR_CPOL;
  REG_PWM_CMR2 |= PWM_CMR_CPOL;
  REG_PWM_CMR3 |= PWM_CMR_CPOL;
  REG_PWM_CMR4 |= PWM_CMR_CPOL;
  REG_PWM_CMR5 |= PWM_CMR_CPOL;
  REG_PWM_CMR6 |= PWM_CMR_CPOL;                  
  //REG_PWM_CMR7 |= PWM_CMR_CPOL;

  
/*
  //Totzeit PWML Output Inverted
  REG_PWM_CMR0 |= PWM_CMR_DTLI;                  
  REG_PWM_CMR1 |= PWM_CMR_DTLI;
  REG_PWM_CMR2 |= PWM_CMR_DTLI;
  REG_PWM_CMR3 |= PWM_CMR_DTLI;
  REG_PWM_CMR4 |= PWM_CMR_DTLI;
  REG_PWM_CMR5 |= PWM_CMR_DTLI;
*/
  //DutyCycle definieren
  REG_PWM_CDTY0 = 0x0FFF;
  REG_PWM_CDTY1 = 52500/2;                      //Totzeit verkürzt den eigentlichen Duty Cycle und verschbiebt diesen nicht. Diese muss zu kompensation dann immer aufaddiert werden                  
  REG_PWM_CDTY2 = 52500/2;
  REG_PWM_CDTY3 = 52500/2;
  REG_PWM_CDTY4 = 52500/2;
  REG_PWM_CDTY5 = 52500/2;
  REG_PWM_CDTY6 = 52500/4;                      //DutyCydle bei der Initialisierung
  REG_PWM_CDTY7 = 52500/8;
  
  //DeadTime definieren                         //Wichtig!!: Obere 12 von 16 Bit sind für die Einschaltzeitverzögerung vorgesehen die unteren 12 Bit für die Ausschaltzeitverzögerung
  REG_PWM_DT0 = 0xFFFF0000;                              //Für eine korrekte Treppenfunktion, muss die Totzeit immer dem Duty Cycle des Messpulses entsprechen.
  REG_PWM_DT1 = 0xFFFF0000;
  REG_PWM_DT2 = 0xFFFF0000;
  REG_PWM_DT3 = 0xFFFF0000;
  REG_PWM_DT4 = 0xFFFF0000;                             
  REG_PWM_DT5 = 0xFFFF0000;
  REG_PWM_DT6 = 0;                  //Messpuls
  REG_PWM_DT7 = 0;                  //DAC Messpuls

  REG_PWM_SCUC |= PWM_SCUC_UPDULOCK;            //Update der neuen Werte

  REG_PWM_IER1 = 0x0000000F;                    //Interrupt Kanal 0-3 erlauben 


//MessDauer_PWM = sensorValue<<16;              //Analoge Messwerte in den Totzeit-Merker schreiben
  //PWM voreinstellen
  REG_PWM_CDTY6 = MessDauer;                    //Duty Cycle des Messpuls übergeben
  REG_PWM_DTUPD0 = MessDauer<<16;               //Totzeit des Leistungspuls 1 auf gleiche länge wie Messpuls stellen  !! Für einschaltverzögerung muss geschifftet werden.
  REG_PWM_DTUPD1 = MessDauer<<16;               //Totzeit des Leistungspuls 2 auf gleiche länge wie Messpuls stellen  !! Für einschaltverzögerung muss geschifftet werden.
  REG_PWM_DTUPD2 = MessDauer<<16;               //Totzeit des Leistungspuls 3 auf gleiche länge wie Messpuls stellen  !! Für einschaltverzögerung muss geschifftet werden.
  REG_PWM_DTUPD3 = MessDauer<<16;               //Totzeit des Leistungspuls 4 auf gleiche länge wie Messpuls stellen  !! Für einschaltverzögerung muss geschifftet werden.
  REG_PWM_DTUPD4 = MessDauer<<16;               //Totzeit des Leistungspuls 5 auf gleiche länge wie Messpuls stellen  !! Für einschaltverzögerung muss geschifftet werden.
  REG_PWM_DTUPD5 = MessDauer<<16;               //Totzeit des Leistungspuls 6 auf gleiche länge wie Messpuls stellen  !! Für einschaltverzögerung muss geschifftet werden.
  REG_PWM_SCUC |= PWM_SCUC_UPDULOCK;            //Update der neuen Werte
  REG_PWM_CDTY0 = 0;          //Duty Cycle des Leistungspuls übergeben
  REG_PWM_CDTY1 = 0;          //Duty Cycle des Leistungspuls übergeben
  REG_PWM_CDTY2 = 0;          //Duty Cycle des Leistungspuls übergeben
  REG_PWM_CDTY3 = 0;          //Duty Cycle des Leistungspuls übergeben
  REG_PWM_CDTY4 = 0;          //Duty Cycle des Leistungspuls übergeben
  REG_PWM_CDTY5 = 0;          //Duty Cycle des Leistungspuls übergeben
  
}



// Funktion für Software PWM von Pin 35 37 39 41
// Pin 35 und 39 wurden mit Pin 6 und 7 gebrückt, da die SoftwarePWM nicht genau genug für den Messpuls ist --> Timingprobleme
// Aus diesem Grund wurde hierfür die beiden Hardware PWM Pins 6 und 7 verwendet 

void SoftwarePWM()
{
  
 
  //Serial.println(REG_PWM_CCNT0);
  
  //Periode Abfragen mit PWM Channel Counter Register 0. Diesr ist bereits auf 100 Hz eingestellt --> 52500 = 100%

  //PWM Messpuls CH1
  //if (REG_PWM_CCNT0 <= Spg_Messpuls_Ch1) {DAC0out = 1; }
  //else {DAC0out = 0;}
  DAC0out =  Spg_Messpuls_1;

  
  //PWM DAC Leistungspuls
  if (REG_PWM_CCNT0 <= Spg_Leistungspuls_1) {DAC1out = 1;}
  else {DAC1out = 0;}
  //Serial.println(REG_PWM_CCNT0);
  //Serial.println(DAC1out);
/*
  //PWM Messpuls CH2
  //if (REG_PWM_CCNT0 <= Spg_Messpuls_Ch2) {DAC2out = 1;}
  //else {DAC2out = 0;}
  DAC2out =  Spg_Messpuls_2;

  //PWM Leistungspuls CH1
  if (REG_PWM_CCNT0 <= Spg_Leistungspuls_2) {DAC3out = 1;}
  else {DAC3out = 0;}

*/

  //PWM LEDs
  if (REG_PWM_CCNT0 <= LED_g_ontime) {LED_g_out = 1;}
  else {LED_g_out = 0;}
  if (REG_PWM_CCNT0 <= LED_y_ontime) {LED_y_out = 1;}
  else {LED_y_out = 0;}
  if (REG_PWM_CCNT0 <= LED_r_ontime) {LED_r_out = 1;}
  else {LED_r_out = 0;}

  

  
}

void PWMout()
{
  //PIN 6
  //Ausgabe Spg des Messpuls 
  //digitalWrite(analogOutPinDAC0, DAC0out);
  REG_PWM_CDTY7 = DAC0out;          //PWM an Ausgaberegister PWML7 übergeben (siehe Arduino Due Pinout Diagram)

  //Ausgabe Leistungspuls Backup
  digitalWrite(analogOutPinDAC1, DAC1out);


  //PIN 7
  //Ausgabe länge des Messpuls
  //digitalWrite(analogOutPinDAC2, DAC2out);
  //REG_PWM_CDTY6 = DAC2out;        //PWM an Ausgaberegister PWML6 übergeben (siehe Arduino Due Pinout Diagram)

  //Ausgabe Leistungspuls Ch2
  //digitalWrite(analogOutPinDAC3, DAC3out);




  //Ausgabe LEDs
  digitalWrite(LED_g, LED_g_out);                         
  digitalWrite(LED_y, LED_y_out); 
  digitalWrite(LED_r, LED_r_out);
                     
   
}

/* Unabhängige PWM von Pin 35 37 39 41 nicht möglich, da diese mit Pin 34 36 38 und 40 gekoppelt sind. 
 *  Lösung ist eine Software PWM, um auf das PWM Modul des Arduino nicht mehr zurück greifen zu müssen. 
  //Pin 35 (Arduino)
  // PWMH0 on PC3, peripheral type B
  PIOC->PIO_PDR |= PIO_PDR_P3;                        // Set PWM pin to peripheral
  PIOC->PIO_ABSR |= PIO_PC3B_PWMH0;

  //Pin 37 (Arduino)
  // PWMH1 on PC5 ; Peripheral type B
  PIOC->PIO_PDR |= PIO_PDR_P5;                      
  PIOC->PIO_ABSR |= PIO_PC5B_PWMH1;              

  //Pin 39 (Arduino)
  // PWMH2 on PC7 ; Perpipheral type B
  PIOC->PIO_PDR |= PIO_PDR_P7;
  PIOC->PIO_ABSR |= PIO_PC7B_PWMH2;

  //Pin 41 (Arduino)
  // PWMH3 on PC9 ; Perpipheral type B
  PIOC->PIO_PDR |= PIO_PDR_P9;
  PIOC->PIO_ABSR |= PIO_PC9B_PWMH3;
*/
