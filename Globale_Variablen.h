//Globale Variablen

//unsigned char SerialStart =0;



// These constants won't change. They're used to give names to the pins used:
const int analogInPin1 = A0;   // Analog input pin für die Spannungsmessungen Ch1
const int analogInPin2 = A1;   // Analog input pin für die Spannungsmessungen Ch2
const int analogInPin3 = A2;   // Analog input pin für die Spannungsmessungen Ch3
const int analogInPin4 = A3;   // Analog input pin für die Spannungsmessungen Ch4
const int analogInPin5 = A4;   // Analog input pin für die Spannungsmessungen Ch5
const int analogInPin6 = A5;   // Analog input pin für die Spannungsmessungen Ch6
const int analogInPin7 = A6;   // Analog input pin für die Sensormessung Sensor 1  (Strommessung 4 bis 20mA übersetzt durch 160Ohm Widerstand )
const int analogInPin8 = A7;   // Analog input pin für die Sensormessung Sensor 2  (Strommessung 4 bis 20mA übersetzt durch 160Ohm Widerstand )
const int analogInPin9 = A8;   // Analog input pin für die Sensormessung Sensor 3  (Strommessung 4 bis 20mA übersetzt durch 160Ohm Widerstand )
const int analogInPin10 = A9;  // Analog input pin für die Sensormessung Sensor 4  (Strommessung 4 bis 20mA übersetzt durch 160Ohm Widerstand )
const int analogInPin11 = A10; // Analog input pin für Temperatursensor
const int analogInPin12 = A11; // Analog input für Messung der Referenzspannung

const int analogOutPinDAC1 = 30;  //PWM_DAC_LEIS_BACKUP

unsigned int U_Ref_Bit = 0;
unsigned long U_Ref_Bit_sum = 0;



unsigned long sensorValue1[Anzahl_Messungen];  //Wertearray anlegen für Spannungsmessung Kanal 1
unsigned long sensorValue2[Anzahl_Messungen];  //Wertearray anlegen für Spannungsmessung Kanal 2
unsigned long sensorValue3[Anzahl_Messungen];  //Wertearray anlegen für Spannungsmessung Kanal 3
unsigned long sensorValue4[Anzahl_Messungen];  //Wertearray anlegen für Spannungsmessung Kanal 4
unsigned long sensorValue5[Anzahl_Messungen];  //Wertearray anlegen für Spannungsmessung Kanal 5
unsigned long sensorValue6[Anzahl_Messungen];  //Wertearray anlegen für Spannungsmessung Kanal 6

unsigned int Spg_Messpuls_1 = 0;       //Wert für DAC0 0-4095 Schritte = 0V bis 3,3V
unsigned int Spg_Leistungspuls_1 = 0;  //Wert für DAC1 0-4095 Schritte = 0V bis 3,3V
unsigned int Spg_Messpuls_2 = 0;       //Wert für DAC0 0-4095 Schritte = 0V bis 3,3V
unsigned int Spg_Leistungspuls_2 = 0;  //Wert für DAC1 0-4095 Schritte = 0V bis 3,3V


unsigned int LED_g_ontime = 0;  //Wert für LED Output 0-50200 Schritte = 0V bis 3,3V
unsigned int LED_y_ontime = 0;  //Wert für LED Output 0-50200 Schritte = 0V bis 3,3V
unsigned int LED_r_ontime = 0;  //Wert für LED Output 0-50200 Schritte = 0V bis 3,3V

unsigned char outBytes[Buffer_Laenge_out];  //Ausgangsbyte_Array für die serielle Datenkomunikation
// Byte 1 und 2 = Status
// Byte 3  = Mittelwert Kanal 1 lowbyte
// Byte 4  = Mittelwert Kanal 1 highbyte
// Byte 5  = Mittelwert Kanal 2 lowbyte
// Byte 6  = Mittelwert Kanal 2 highbyte
// Byte 7  = Sensor 1 lowbyte
// Byte 8  = Sensor 1 highbyte
// Byte 9  = Sensor 2 lowbyte
// Byte 10 = Sensor 2 highbyte
// Byte 11 = Sensor 3 lowbyte
// Byte 12 = Sensor 3 highbyte
// Byte 13 = Sensor 4 lowbyte
// Byte 14 = Sensor 4 highbyte

unsigned char inBytes[Buffer_Laenge_in];  //Eingangsbyte_Array für die serielle Datenkomunikation
// Byte 1 und 2 = Status
// Byte 3  = Mittelwert Kanal 1 lowbyte
// Byte 4  = Mittelwert Kanal 1 highbyte
// Byte 5  = Mittelwert Kanal 2 lowbyte
// Byte 6  = Mittelwert Kanal 2 highbyte
// Byte 7  = Sensor 1 lowbyte
// Byte 8  = Sensor 1 highbyte
// Byte 9  = Sensor 2 lowbyte
// Byte 10 = Sensor 2 highbyte
// Byte 11 = Sensor 3 lowbyte
// Byte 12 = Sensor 3 highbyte
// Byte 13 = Sensor 4 lowbyte
// Byte 14 = Sensor 4 highbyte

unsigned char merkerBytes[Buffer_Laenge_in];  //Eingangsbyte_Array für die serielle Datenkomunikation
// Byte 1 und 2 = Status
// Byte 3  = Mittelwert Kanal 1 lowbyte
// Byte 4  = Mittelwert Kanal 1 highbyte
// Byte 5  = Mittelwert Kanal 2 lowbyte
// Byte 6  = Mittelwert Kanal 2 highbyte
// Byte 7  = Sensor 1 lowbyte
// Byte 8  = Sensor 1 highbyte
// Byte 9  = Sensor 2 lowbyte
// Byte 10 = Sensor 2 highbyte
// Byte 11 = Sensor 3 lowbyte
// Byte 12 = Sensor 3 highbyte
// Byte 13 = Sensor 4 lowbyte
// Byte 14 = Sensor 4 highbyte


int outputMessung = 0;
int outputLeistung = 0;

unsigned char Step = 0;
unsigned char Serial_Step = 0;

long GLtime;

int PWMTime = 0;
const unsigned int PWMDauer = 40000u;  //Zykluslänge von 1ms --> Entspricht einer Frequenz von 1kHz

int MessTime = 0;  //Aktuelle MessTime

long MessDauer_PWM = 0;  //Generelle Messdauer
int PulsTime = 0;        //Aktuelle PulsTime
int PulsDauer = 0;       //Generelle Pulsdauer
long PulsDauer_PWM = 0;  //Generelle Pulsdauer
int MessTest = 0;
long DutyCycle1 = 0;     //Duty Cycle Leistungspuls Kanal 1
long DutyCycle2 = 0;     //Duty Cycle Leistungspuls Kanal 2
long DutyCycle3 = 0;     //Duty Cycle Leistungspuls Kanal 3
long DutyCycle4 = 0;     //Duty Cycle Leistungspuls Kanal 4
long DutyCycle5 = 0;     //Duty Cycle Leistungspuls Kanal 5
long DutyCycle6 = 0;     //Duty Cycle Leistungspuls Kanal 6
long T_duty_cycle1 = 0;  //Duty Cycle Leistungspuls Kanal 1
long T_duty_cycle2 = 0;  //Duty Cycle Leistungspuls Kanal 2
long T_duty_cycle3 = 0;  //Duty Cycle Leistungspuls Kanal 3
long T_duty_cycle4 = 0;  //Duty Cycle Leistungspuls Kanal 4
long T_duty_cycle5 = 0;  //Duty Cycle Leistungspuls Kanal 5
long T_duty_cycle6 = 0;  //Duty Cycle Leistungspuls Kanal 6

unsigned int DAC0out = 0;  //Output Merker DAC
unsigned int DAC1out = 0;
unsigned int DAC2out = 0;
unsigned int DAC3out = 0;
unsigned int DAC4out = 0;
/*unsigned int DAC5out = 0;
unsigned int DAC6out = 0;
unsigned int DAC7out = 0;
*/


float R_out_1 = 0;
float R_out_2 = 0;
float R_out_3 = 0;
float R_out_4 = 0;
float R_out_5 = 0;
float R_out_6 = 0;


unsigned int LED_g_out = 0;  //Output Merker LED
unsigned int LED_y_out = 0;
unsigned int LED_r_out = 0;
unsigned char CH1_ENABLE_out = 1;
unsigned char CH2_ENABLE_out = 1;
unsigned char CH3_ENABLE_out = 1;
unsigned char CH4_ENABLE_out = 1;
unsigned char CH5_ENABLE_out = 1;
unsigned char CH6_ENABLE_out = 1;
unsigned char CHx_ENABLE_out[7] = {0, 0, 0, 0, 0, 0, 0};

unsigned char Switch1_in = 0;
unsigned char Switch2_in = 0;

int T_mess_on = 0;
int T_mess_on_Dauer = 0;  //42000 = 1ms ; 840 = 20µs ; 630 = 15µs ; 420 = 10µs
int T_mess = 0;
int T_mess_Dauer = 0;  //42000 = 1ms ; 2100 = 50µs
int T_serial_start = 0;
int T_serial_start_Dauer = 24;  //42000 = 1ms ; 24 = 0,5µs

//unsigned char Anzahl_Messungen = 4           //Anzahl der Spannungsmessungen

unsigned int Mess_Counter = 0;
unsigned int Serial_Start = 0;  //Zeitschritte von 0,5µs zählen

int SensorAdd1 = 0;
int SensorAdd2 = 0;
int SensorAdd3 = 0;
int SensorAdd4 = 0;
int SensorAdd5 = 0;
int SensorAdd6 = 0;
int SensorMittelwert1 = 0;
int SensorMittelwert2 = 0;
int SensorMittelwert3 = 0;
int SensorMittelwert4 = 0;
int SensorMittelwert5 = 0;
int SensorMittelwert6 = 0;

//long PWM_Status = 0;              //Stauts für PWM anlegen

unsigned char StatusOut = 0;
unsigned char StatusOut2 = 0;
unsigned char StatusIn = 0;
unsigned char StatusIn2 = 0;

int MessDauer = 2625;  //2100 Generelle Messdauer Darf nicht über 4095 (12Bit)

char LED_State = 0;



//Einstellbyte für die Gainsteuerung der PGA202/203 Instrumentenverstärker
unsigned int PGA_Shunt_1_Gain = 8;  //Gültige Werte sind 1, 2, 4, 8, 10, 100, 1000
unsigned int PGA_Shunt_2_Gain = PGA_Shunt_1_Gain;
unsigned int PGA_Shunt_3_Gain = PGA_Shunt_1_Gain;
unsigned int PGA_Shunt_4_Gain = PGA_Shunt_1_Gain;
unsigned int PGA_Shunt_5_Gain = PGA_Shunt_1_Gain;
unsigned int PGA_Shunt_6_Gain = PGA_Shunt_1_Gain;

unsigned int PGA_SMA_1_Gain = 1;
unsigned int PGA_SMA_2_Gain = 1;
unsigned int PGA_SMA_3_Gain = 1;
unsigned int PGA_SMA_4_Gain = 1;
unsigned int PGA_SMA_5_Gain = 1;
unsigned int PGA_SMA_6_Gain = 1;


/*unsigned char PGA_Shunt_1_A0 = 0;
unsigned char PGA_Shunt_1_A1 = 0;
unsigned char PGA_SMA_1_A0 = 0;
unsigned char PGA_SMA_1_A1 = 0;
unsigned char PGA_Shunt_2_A0 = 0;
unsigned char PGA_Shunt_2_A1 = 0;
unsigned char PGA_SMA_2_A0 = 0;
unsigned char PGA_SMA_2_A1 = 0;
*/

// Varialblen zur Leistungsberechnung

float Pmax = 0.4323;
int I_sp1 = 0;  // Spitzenstrom Kanal1 bis 4 [mA]
int I_sp2 = 0;  // Spitzenstrom Kanal5 bis 6 [mA]
int U_in[7];    // Gemessene Spannung am Draht in Bit Kanal 1 bis 6 (Kanal 0 wird frei gehalten für einfachere Lesbarkeit)

float R_Multi[7] = { 0, 0.0060618307, 0.0060618307, 0.0060618307, 0.0060618307, 0.0060618307, 0.0060618307 };  //Steigung Bit-Widerstand-Geraden
float R_Add[7] = { 0, 0.1468983633, 0.1468983633, 0.1468983633, 0.1468983633, 0.1468983633, 0.1468983633 };



int P_in1 = 0;   // Eingehende Leistung Kanal1
int P_in2 = 0;   // Eingehende Leistung Kanal2
int P_in3 = 0;   // Eingehende Leistung Kanal3
int P_in4 = 0;   // Eingehende Leistung Kanal4
int P_in5 = 0;   // Eingehende Leistung Kanal5
int P_in6 = 0;   // Eingehende Leistung Kanal6
int I_in1 = 0;   // Eingehender Storm Kanal1
int I_in2 = 0;   // Eingehender Storm Kanal2
int I_in3 = 0;   // Eingehender Storm Kanal3
int I_in4 = 0;   // Eingehender Storm Kanal4
int I_in5 = 0;   // Eingehender Storm Kanal5
int I_in6 = 0;   // Eingehender Storm Kanal6
int R_out1 = 0;  // Gemessener Widerstand in Bit Kanal1
int R_out2 = 0;  // Gemessener Widerstand in Bit Kanal2
int R_out3 = 0;  // Gemessener Widerstand in Bit Kanal3
int R_out4 = 0;  // Gemessener Widerstand in Bit Kanal4
int R_out5 = 0;  // Gemessener Widerstand in Bit Kanal5
int R_out6 = 0;  // Gemessener Widerstand in Bit Kanal6

//unsigned int Conversion_Duty_to_Bit_Ch1 = 52428;       //Umrechnungsfaktor um aus dem Dutycycle ein Bitwert zu machen.
//unsigned int Conversion_Duty_to_Bit_Ch2 = 52428;
unsigned int Conversion_Duty_to_Bit_Ch1 = 52500;  //Umrechnungsfaktor um aus dem Dutycycle ein Bitwert zu machen.
unsigned int Conversion_Duty_to_Bit_Ch2 = 52500;
unsigned int Conversion_Duty_to_Bit_Ch3 = 52500;  //Umrechnungsfaktor um aus dem Dutycycle ein Bitwert zu machen.
unsigned int Conversion_Duty_to_Bit_Ch4 = 52500;
unsigned int Conversion_Duty_to_Bit_Ch5 = 52500;  //Umrechnungsfaktor um aus dem Dutycycle ein Bitwert zu machen.
unsigned int Conversion_Duty_to_Bit_Ch6 = 52500;

//float I_leis1 = 0;
float P_max1 = 0;  // Maximale Leisutng Leistungspuls
float P_max2 = 0;  // Maximale Leistung Leistungspuls



int flag_loop = 0;
int countF = 0;
unsigned long sum_U_in[7];  //Gemessene und summierte Spannung am Draht in Bit Kanal 1 bis 6 (Kanal 0 wird frei gehalten für einfachere Lesbarkeit) Variable für Kalibirierung







int Wert1;
int Wert2;
int Wert3;
int Wert4;
int Wert5;
int Wert6;
int Wert1out;
int Wert2out;
int Wert3out;
int Wert4out;
int Wert5out;
int Wert6out;
int Wert7out;
int Wert8out;
int Wert9out;
int Wert10out;
int Wert11out;

int cali_flag = 1;  //0 = keine Kalibrierung // 1 = mit Kalibrierung beginnen

int Sensor_in1;
int Sensor_in2;
int Sensor_in3;
int Sensor_in4;


//Testvariablen
float testDuty = 0.0;
int countTest = 0;
int count = 0;
int Testmerker = 0;

unsigned char TestVar_1 = 0;
