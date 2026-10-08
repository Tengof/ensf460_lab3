#include "xc.h"
#include "IOs.h"
#include "UART2.h"

void IOinit(void){
    AD1PCFG = 0xFFFF; /* keep this line as it sets I/O pins that can also be analog to be digital */

    // LED -> RB9
    TRISBbits.TRISB9 = 0;
    LATBbits.LATB9 = 0;
    
    // PB3 -> RA4 / CN0
    TRISAbits.TRISA4 = 1;
    CNPU1bits.CN0PUE = 1;
    CNEN1bits.CN0IE = 1;
    
    // PB2 -> RB4 / CN1
    TRISBbits.TRISB4 = 1;
    CNPU1bits.CN1PUE = 1;
    CNEN1bits.CN1IE = 1;
    
    // PB1 -> RB7 / CN23
    TRISBbits.TRISB7 = 1;
    CNPU2bits.CN23PUE = 1;
    CNEN2bits.CN23IE = 1;
    
    // CN interrupt setup
    IPC4bits.CNIP = 6;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
}

void IOcheck(void){
    uint16_t PB1 = PORTBbits.RB7;
    uint16_t PB2 = PORTBbits.RB4;
    uint16_t PB3 = PORTAbits.RA4;
    
    if((PB1 == 0) && (PB2 == 0) && (PB3 == 0)){
        Disp2String("\033[2J\033[H");
        Disp2String("All PBs pressed");
        
        T3CONbits.TON = 0; // Stops Timer3
        LATBbits.LATB9 = 1; // Turns LED on
        
    } else if((PB1 == 0) && (PB2 == 0)){
        Disp2String("\033[2J\033[H");
        Disp2String("PB1 and PB2 are pressed");
        
        T3CONbits.TON = 0; // Stops Timer3
        LATBbits.LATB9 = 1; // Turns LED on
        
    } else if((PB1 == 0) && (PB3 == 0)){
        Disp2String("\033[2J\033[H");
        Disp2String("PB1 and PB3 are pressed");
        
        T3CONbits.TON = 0; // Stops Timer3
        LATBbits.LATB9 = 1; // Turns LED on
        
    } else if((PB2 == 0) && (PB3 == 0)){
        Disp2String("\033[2J\033[H");
        Disp2String("PB2 and PB3 are pressed");
        
        T3CONbits.TON = 0; // Stops Timer3
        LATBbits.LATB9 = 1; // Turns LED on
        
    } else if(PB1 == 0){
        Disp2String("\033[2J\033[H");
        Disp2String("PB1 is pressed");
        
        T3CONbits.TON = 0; // Stops Timer3
        LATBbits.LATB9 = 1; // Start with the LED on
        TMR3 = 0; // Reset the count of Timer3
        T3CONbits.TCKPS = 1; // Use 1:8 pre-scaler
        PR3 = 7812; // 0.25s count
        T3CONbits.TON = 1; // Start Timer3
        
    } else if(PB2 == 0){
        Disp2String("\033[2J\033[H");
        Disp2String("PB2 is pressed");
        
        T3CONbits.TON = 0; // Stops Timer3
        LATBbits.LATB9 = 1; // Start with the LED on
        TMR3 = 0; // Reset the count of Timer3
        T3CONbits.TCKPS = 1; // Use 1:8 pre-scaler
        PR3 = 31249; // 1s count
        T3CONbits.TON = 1; // Start Timer3
        
    } else if(PB3 == 0){
        Disp2String("\033[2J\033[H");
        Disp2String("PB3 is pressed");
        
        T3CONbits.TON = 0; // Stops Timer3
        LATBbits.LATB9 = 1; // Start with the LED on
        TMR3 = 0; // Reset the count of Timer3
        T3CONbits.TCKPS = 3; // Use 1:256 pre-scaler for 3 sec delay since greater than max
        PR3 = 2929; // 3s count
        T3CONbits.TON = 1; // Start Timer3
        
    } else {
        Disp2String("\033[2J\033[H");
        Disp2String("Nothing pressed");
        
        T3CONbits.TON = 0; // Stop Timer3
        LATBbits.LATB9 = 0; // Turn LED off
    }
}
