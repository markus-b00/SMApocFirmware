// Einheiten in der rechteckigen Klammer [] beziehen sich auf die Einheit nach der Umrechnung


//Berechnung des Duty-Cycles
long Duty_Calc(int P_in,int R_out, float Isp)
{ long T_duty_cycle=0;
  float I_sp = Isp/1000 ; // Umrechnung int zu float [A]
  float Pr=0;
  Pr = (float) P_in;
  Pr=Pr/1000; // Umrechnung mW in W
  
  if (P_in==0){
    T_duty_cycle= 0 ;
    return T_duty_cycle;
  }
  else{
    
    float R_is=0.0;
    float dutyProzent=0.0;
    R_is=((float)R_out)/1000; // Umrechnung int zu float [Ohm]
    dutyProzent=(Pr/(R_is*(I_sp*I_sp)));
    testDuty = dutyProzent;
    T_duty_cycle = (long) (dutyProzent*Conversion_Duty_to_Bit_Ch1); // Umrechnung in 16 Bitwert
    return  T_duty_cycle ;
  }
 
}




//-------------------------------------------------------------------------------------------
// Kontrolle des Aktuellen Duty_Cycles
void check_Power(float P_is, int U_in, float R_is)
{
  P_is=T_duty_cycle1*R_is*(U_in^2);
}
//Berechnung des Widerstandes aus gemessener Spannung
// und dem Spitzenstrom
float UtoR(long Uin,float I_is)
{ float Uis = 0;
  float R_is=0;
  Uis = (float) Uin;
  R_is=Uis/I_is;
  return R_is;
}

int R_KAL(int Rin ,float Multi, float Add)     //Widerstand berechnen für beide Kanäle 
{ 
  float R_is=0;
  R_is=Rin*Multi+Add;
  //R_is=R_is*1000;       //Ausgabe umrechnen von Ohm in mOhm
  R_is=(int) R_is;      //Nachkommastellen abschneiden
  return R_is;
}


//--------------------------------------------------------------------------------------------
//Funktion für die Ausgabe als Stromquelle
//Konstantstrom wird vorgegeben
//Input I_soll in mA, I_sp in mA
long Duty_Calc_CurrentSource(int I_soll, float I_sp)
{
  long T_duty_Cycle = 0;
  float dutyProzent = 0;

  dutyProzent = I_soll/I_sp;
  T_duty_Cycle = (long) (dutyProzent*Conversion_Duty_to_Bit_Ch1); // Umrechnung in 16 Bitwert
  return T_duty_Cycle;
}









