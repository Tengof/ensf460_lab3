#include "IOs.h"
#include "Timer.h"
#include "UART2.h"

volatile uint16_t TMR2flag = 0;


void IOinit(void) {
    
    AD1PCFG = 0xFFFF; // Turn all analog pins as digital
    
    /* LED */
    TRISBbits.TRISB9 = 0; // set to output
    LATBbits.LATB9 = 0; // set to be off initially
    
    /* PB1 = RB7 */
    TRISBbits.TRISB7 = 1; // set to input
    CNPU2bits.CN23PUE = 1; // set PB1 to pull-down
    CNEN2bits.CN23IE = 1; // flag for CN interrupt when PB1 is pressed
    
    /* PB2 = RB4 */
    TRISBbits.TRISB4 = 1; // set to input
    CNPU1bits.CN1PUE = 1; // set PB2 to pull-down
    CNEN1bits.CN1IE = 1; // flag for CN interrupt when PB2 is pressed
    
    /* PB3 = RA4 */
    TRISAbits.TRISA4 = 1; // set to input
    CNPU1bits.CN0PUE = 1; // set PB3 to pull-down
    CNEN1bits.CN0IE = 1; // flag for CN interrupt when PB3 is pressed
    
    /* CN interrupt */
    IPC4bits.CNIP = 6;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
}


void IOcheck(void) {
    
    // pressed button reads 0 because of the pull-ups
    uint16_t PB1_pressed = (PORTBbits.RB7 == 0);
    uint16_t PB2_pressed = (PORTBbits.RB4 == 0);
    uint16_t PB3_pressed = (PORTAbits.RA4 == 0);
    
    
    if (PB1_pressed && PB2_pressed && PB3_pressed) {
        Timer3_Stop();
        LATBbits.LATB9 = 1;
        Disp2String("\rAll PBs pressed          ");
    }
    else if (PB1_pressed && PB2_pressed) {
        Timer3_Stop();
        LATBbits.LATB9 = 1;
        Disp2String("\rPB1 and PB2 are pressed  ");
    }
    else if (PB1_pressed && PB3_pressed) {
        Timer3_Stop();
        LATBbits.LATB9 = 1;
        Disp2String("\rPB1 and PB3 are pressed  ");
    }
    else if (PB2_pressed && PB3_pressed) {
        Timer3_Stop();
        LATBbits.LATB9 = 1;
        Disp2String("\rPB2 and PB3 are pressed  ");
    }
    else if (PB1_pressed) {
        LATBbits.LATB9 = 1;
        Timer3_Start(244);  // 0.25 s
        Disp2String("\rPB1 is pressed           ");
    }
    else if (PB2_pressed) {
        LATBbits.LATB9 = 1;
        Timer3_Start(977);  // 1 s
        Disp2String("\rPB2 is pressed           ");
    }
    else if (PB3_pressed) {
        LATBbits.LATB9 = 1;
        Timer3_Start(2930); // 3 s
        Disp2String("\rPB3 is pressed           ");
    }
    else {
        Timer3_Stop();
        LATBbits.LATB9 = 0;
        Disp2String("\rNothing pressed          ");
    }
}
