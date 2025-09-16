

/* Variablen Kalibration*****************************************************/
// Strom beim Leistungspuls Kanal1
float I_leis1 = 0; // Strom beim Leistungspuls Kanal 1 bis 4
float I_mess1 = 0;// Strom beim Messpuls Kanal 1 bis 4
float I_leis2 = 0; // Strom beim Leistungspuls Kanal 5 bis 6
float I_mess2 = 0; // Strom beim Messpuls Kanal2
float t_mess = 0.5; // [ms] Messzeit
float t_duty = 10; // [ms] Duty_Zeit
float x_leis = 0.1/100; // Leistungsfaktor x
float R1_Calib=2000*0.877;//*0.828;  // unterer Kalibrationswiderstand in mOhm
float R2_Calib=10000*0.957;//*0.8; // oberer Kalibrationswiderstand in mOhm



unsigned char Calib_CHx_ON_OFF[7] = {0, 1, 1, 1, 1, 1, 1};    //1 = Kalibrierung off; 0 = Kalibreirung ON //Wert [0] wird nie verwendet

unsigned char Calib_R1_ON_OFF     = 0;     //0 = Kalibrierwiderstand 1 off; 1 = Kalibrierwiderstand 1 ON
unsigned char Calib_R2_ON_OFF     = 0;     //0 = Kalibrierwiderstand 2 off; 1 = Kalibrierwiderstand 2 ON


int Bit_max=0; // gemessener Bitwert bei Rmax Kanalx
int Bit_min=0; // gemessener Bitwert bei Rmin Kanalx



long PWM_Status = 0;              //Stauts für PWM anlegen
int StepC = 0;
uint8_t  save[4];
int flag_com =0;
unsigned char outBytesC[Buffer_Laenge_out];          //Ausgangsbyte_Array für die serielle Datenkomunikation
unsigned char inBytesC[Buffer_Laenge_in];           //Eingangsbyte_Array für die serielle Datenkomunikation
unsigned char merkerBytesC[Buffer_Laenge_in];       //Eingangsbyte_Array für die serielle Datenkomunikation
int cal = 0;
