void TimerStart(Tc *tc, uint32_t channel, IRQn_Type irq)
{
   pmc_set_writeprotect(false);                                                                 //Power Management Controller Schreibschutz aus
   pmc_enable_periph_clk(irq);                                                                  //Aktivieren der peripheral clock von TC1 Kanal 0
   TC_Configure(tc, channel, TC_CMR_TCCLKS_TIMER_CLOCK1);                                       //...TIMER_CLOCK 1 = MCK/2   --> 42MHz                     TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC |
                                                                                                //...TIMER_CLOCK 2 = MCK/8   --> 10,5MHz
                                                                                                //...TIMER_CLOCK 3 = MCK/32  --> 2,652MHz
                                                                                                //...TIMER_CLOCK 4 = MCK/128 --> 0,65625MHz
                                                                                                //...TIMER_CLOCK 5 = SLCK    --> 32kHz
   
   TC_Start(tc, channel);                                                                       //erneutes Starten des timers
   
}
