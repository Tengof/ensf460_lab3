#include "Timer.h"

/* newClk(500) -> timers count at 250 kHz
 * Timer 2: prescaler 1:8   -> 1 count = 32 us
 * Timer 3: prescaler 1:256 -> 1 count = 1.024 ms
 */

void TimerInit(void) {
    
    //T2CON config (100 ms wait after a button change)
    T2CONbits.T32 = 0; // operate timer 2 as 16 bit timer
    T2CONbits.TCKPS = 1; // set prescaler to 1:8
    T2CONbits.TCS = 0; // use internal clock
    T2CONbits.TSIDL = 0; //operate in idle mode
    IPC1bits.T2IP = 5; //7 is highest and 1 is lowest priority.
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1; //enable timer interrupt
    PR2 = 3125; // set the count value for 0.1 s (or 100 ms)
    TMR2 = 0;
    // timer 2 is turned on by the CN interrupt
    
    //T3CON config (LED blink)
    T3CONbits.TCKPS = 3; // set prescaler to 1:256
    T3CONbits.TCS = 0; // use internal clock
    T3CONbits.TSIDL = 0; //operate in idle mode
    IPC2bits.T3IP = 2; //7 is highest and 1 is lowest pri.
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 1; //enable timer interrupt
    TMR3 = 0;
    // timer 3 is turned on by IOcheck()
}

// pr3 = 244 (0.25 s), 977 (1 s) or 2930 (3 s)
void Timer3_Start(uint16_t pr3) {
    T3CONbits.TON = 0;
    TMR3 = 0;
    PR3 = pr3;
    T3CONbits.TON = 1;
}

void Timer3_Stop(void) {
    T3CONbits.TON = 0;
}