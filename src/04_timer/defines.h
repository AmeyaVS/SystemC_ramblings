#ifndef __DEFINES_H
#define __DEFINES_H

#define ADDR_WIDTH 4
#define DATA_WIDTH 8
#define MAX 255

// Bit positions for the Timer Control Register
#define TMR_CNTRL_EN	0
#define TMR_CNTRL_CMP	1
#define TMR_CNTRL_OV	2

// Bit positions for the Timer Interrupt Register
#define TMR_INTR_CMP	0
#define TMR_INTR_OV	1

#endif /* __DEFINES_H */
