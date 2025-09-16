/*
//declare variables
 unsigned short duty0 = 15000;
 unsigned short duty1 = 30000;
 unsigned short duty2 = 45000;
 unsigned short duty3 = 60000;

void setup() {
  pwmc_setup();
}

void loop() {
 pwmc_duty(duty0, duty1, duty2, duty3); //set pwm duty cycle
}

void pwmc_setup()
{
  //Configure PWM channels 0,1,2,3 (PWML0,PWMH0,PWML1,PWMH1,PWML2,PWMH2,PWML3,PWMH3), (port C.2,C.3,C.4,C.5,C.6,C.7,C.8,C.9), (pins P34,P35,P36,P37,P38,P39,P40,P41)
  REG_PIOC_PDR = 0x3FC;  //B1111111100, PIO Disable Register
  REG_PIOC_ABSR = REG_PIOC_ABSR | 0x3FCu; //B1111111100, Peripheral AB Select Register

  REG_PMC_PCER1 = REG_PMC_PCER1 | 16; //Peripheral Clock Enable Register 1 (activate clock for PWM, id36, bit5 of PMC_PCSR1)
  REG_PWM_ENA = REG_PWM_SR | B1111; //PWM Enable Register | PWM Status Register (activate channels 0,1,2,3)

  REG_PWM_CMR0 = 0x10000; //Channe0 Mode Register: Dead Time Enable DTE=1
  REG_PWM_CMR1 = 0x10000; //Channe1 Mode Register: Dead Time Enable DTE=1
  REG_PWM_CMR2 = 0x10000; //Channe2 Mode Register: Dead Time Enable DTE=1
  REG_PWM_CMR3 = 0x10000; //Channe3 Mode Register: Dead Time Enable DTE=1

  REG_PWM_DT0 = 0xA800A8; //Channe0 Dead Time Register (168=2us for outputs PWML0,PWMH0)
  REG_PWM_DT1 = 0xA800A8; //Channe1 Dead Time Register (168=2us for outputs PWML1,PWMH1)
  REG_PWM_DT2 = 0xA800A8; //Channe2 Dead Time Register (168=2us for outputs PWML2,PWMH2)
  REG_PWM_DT3 = 0xA800A8; //Channe3 Dead Time Register (168=2us for outputs PWML3,PWMH3)

  REG_PWM_CPRD0 = 65535; //Channe0 Period Register (84mhz/65535=1.281khz=780.64us period)
  REG_PWM_CPRD1 = 65535; //Channe1 Period Register (84mhz/65535=1.281khz=780.64us period)
  REG_PWM_CPRD2 = 65535; //Channe2 Period Register (84mhz/65535=1.281khz=780.64us period)
  REG_PWM_CPRD3 = 65535; //Channe3 Period Register (84mhz/65535=1.281khz=780.64us period)
}

//Set the PWM duty-cycle
inline void pwmc_duty(unsigned short duty0, unsigned short duty1, unsigned short duty2, unsigned short duty3) {
  REG_PWM_CDTY0 = duty0;
  REG_PWM_CDTY1 = duty1;
  REG_PWM_CDTY2 = duty2;
  REG_PWM_CDTY3 = duty3;
}
*/
