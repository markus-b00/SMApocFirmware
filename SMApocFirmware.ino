/*
  SMAPOC_PCdirect_V03_6Ch_02

  SMAPOC -> SMA POwer Controller
  Firmware für den Betrieb des SMAPOC 3.0.
  Der SMAPOC ist 6 Kanalig aufgebaut, um zwei SMA-Drähte ansteuern zu können.
  Die Ansteuerung ist als Stromquelle realisiert. 
  Die Ansteuerung ist aufgeteilt in einen Messpuls (geringe Leistung) und einen Leistungspuls (hohe Leistung).
  Die Widerstandsmessung der SMA-Drähte erfolgt lediglich wärend der Messpulse.
  
  Der Duty-Cycle des Leistungspuls wird über die UART Schnittstelle übertragen.
  Es werden 13 Bytes übertragen. 1 Statusbyte und jeweils 6 x 2 Bytes für den Duty-Cycle von Kanal 1 bis 6.
  Zurückgegeben wird der Widerstand über den SMA-Draht von allen sechs Kanälen (6 x 2 Bytes). 
  Für die Widerstandsbestimmung werden 8 Werte gemessen und deren Mittelwert gebildet.

  Für die Ansteuerung der Stromquelle werden mind. 2 Analogspannungen benötigt. Diese kann über zwei unterschiedliche Weisen erzeugt werden. 
  Variante A: Digital Analogwandler AD6065BRUZ-1. Ausgang 4 Analogspannungen (2x Messspannung, 2x Leistungsspannung).
              Die Kanäle sind wir folgt aufgeteilt (SPG_MESS und SPG_LEIS = CH1 bsi CH4 | SPG_MESS_2 und SPG_LEIS_2 = CH5 bsi CH6)
  Variante B: PT1 Glied mit 2 Analogspannungen am Ausgang (SPG_MESS_BACKUP, SPG_LEIS_BACKUP)

  Es gibt zwei verschiedene Einstellmodi für den SMAPOC
  Modus A = Funktion des SMAPOCS als Leistungsquelle (Closed Loop) --> Input Leistung in mW
  Modus A = flag_loop == 1 oder 2 --> StatusIn = 1 oder 2 übertragen
  Modus B = Funktion des SMAPOCS als Stromquelle (Open Loop) --> Input Strom in mA
  Modus B = flag:loop == 3 --> StatusIn = 3 übertragen

  Anmerkung 18.02.2025 zunächst wird mit Variante B gearbeitet, da der DA Wandler noch nicht angekommen ist.
            Weiterhin muss auch noch die SPI Kommunikation initalisiert werden, um auch mit 24 Bit Messauflsung arbeiten zu können. 

  Zeit wird über den internen Timer (TC1 Channel 0) realisiert und nicht über die Arduino Funktion micros()

  !!!!!    100Hz Version    !!!!!
  !!!!!    neuer DAC        !!!!!
  
  created 20 August   2019
  modifed 18 Februar  2025
  by Philip Frenzel
  mechatronic factory GmbH

*/

#include "defines.h"
#include "Globale_Variablen.h"
#include "Timer_Start.h"
#include "calibration.h"
#include <SPI.h>

void Test_Code();
void SoftwarePWM();
void Main_Stateflow();
void SoftReset();
void PWMout();
void PowerRoutingOut();
void SETUP_all();
void calibration_flow();
void PWMsetup();
void function_R();

//Testvar
int datenpaket;
unsigned char Calib_Ch = 1;  //Für Kalibrierung direkt mit Kanal 1 Starten
unsigned char Debug_i = 0;
unsigned long R_out1_sum = 0;
unsigned long R_out2_sum = 0;
unsigned long R_out3_sum = 0;
unsigned long R_out4_sum = 0;
unsigned long R_out5_sum = 0;
unsigned long R_out6_sum = 0;

        

void setup() {

  SETUP_all();  //Setup durchfüheren
  calibration_direct(); //Kalibrierung durchführen Startwerte
  cali_flag = 1; //Kalibrierung durchführen
  
  

  T_duty_cycle1 = 0;  //Duty Cycle Leistungspuls Kanal 1
  T_duty_cycle2 = 0;  //Duty Cycle Leistungspuls Kanal 2
  T_duty_cycle3 = 0;  //Duty Cycle Leistungspuls Kanal 3
  T_duty_cycle4 = 0;  //Duty Cycle Leistungspuls Kanal 4
  T_duty_cycle5 = 0;  //Duty Cycle Leistungspuls Kanal 5
  T_duty_cycle6 = 0;  //Duty Cycle Leistungspuls Kanal 6
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {

  //Serial.println("Loop");

  //flag_loop = 1;


  //Eingänge einlesen
  GLtime = TC1->TC_CHANNEL[0].TC_CV;  //Globale Zeit pro Zyklus definieren         --> 42000 Schritte = 1ms

  //Taster Einlesen
  Switch1_in = digitalRead(Switch1);
  Switch2_in = digitalRead(Switch2);


  Test_Code();  //Testen/Debugging
                //digitalWrite(13, HIGH);        //Debugging SPG-Messung
  //Funktionsaufrufe---------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------
  calibration_flow(); //Kalibrierung durchführen zu beginn

  SoftwarePWM();  //SoftwarePWM abarbeiten
  
  Main_Stateflow();  //Hauptprogramm abarbeiten

  SoftReset();  //Sicherheitsfunktion falls bei einer Stromquelle die Regelung aussteigt
  //CH_Access();  //Kanal nur aktivieren wenn er auch benötigt wird. 
  //digitalWrite(13, LOW);        //Debugging SPG-Messung

  //Ausgaben-----------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------
  
  //Ausgabe ansteuerung Stromquelle wird parallel mit PWM Modul verarbeitet.
  PWMout();  //SoftwarePWM Werte ausgeben (DAC0 bis 3)
  PowerRoutingOut();

  //Serial.println("Loop");   // send Text for debuging

  digitalWrite(CH1_ENABLE, CHx_ENABLE_out[1]);  //Enablestatus Ch1 Ausgeben
  digitalWrite(CH2_ENABLE, CHx_ENABLE_out[2]);  //Enablestatus Ch2 Ausgeben
  digitalWrite(CH3_ENABLE, CHx_ENABLE_out[3]);  //Enablestatus Ch3 Ausgeben
  digitalWrite(CH4_ENABLE, CHx_ENABLE_out[4]);  //Enablestatus Ch4 Ausgeben
  digitalWrite(CH5_ENABLE, CHx_ENABLE_out[5]);  //Enablestatus Ch5 Ausgeben
  digitalWrite(CH6_ENABLE, CHx_ENABLE_out[6]);  //Enablestatus Ch6 Ausgeben


  //digitalWrite(LED_r, HIGH);

}  //Ende loop
