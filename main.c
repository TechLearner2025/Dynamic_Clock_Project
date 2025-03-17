#include <xc.h>

// Define constants and macros
#define _XTAL_FREQ 4000000 // Define the oscillator frequency for delay functions

// Seven-segment display digit definitions
#define ZERO    0xE7
#define ONE     0x21
#define TWO     0xCB
#define THREE   0x6B
#define FOUR    0x2D
#define FIVE    0x6E
#define SIX     0xEE
#define SEVEN   0x23
#define EIGHT   0xEF
#define NINE    0x6F
#define DOT     0x10
#define BLANK   0x00
#define M_ONE   0x9D
#define MINUS   0xFD

// Arrays for digit display
const unsigned char digit[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
const unsigned char dig[1] = {BLANK};

// Global variables for timekeeping and display
volatile unsigned char hours = 0;
volatile unsigned char minutes = 0;
volatile unsigned char seconds = 0;
volatile unsigned char flagA = 1;
volatile unsigned char flagB = 1;
volatile unsigned char first = 1;
volatile unsigned char second = 1;
volatile unsigned char third = 1;
volatile unsigned char fourth = 1;

unsigned char ssd[4];

// Function declarations
void init_config(void);
void init_timer0(void);
void update_time(void);
void display1(void);
void display2(void);
void increment(void);
void decrement(void);

// Timer0 initialization for timing control
void init_timer0(void)
{
    T08BIT = 1;
    T0CS = 0;
    TMR0ON = 1;
    PSA = 1;
    TMR0 = 6;
    TMR0IF = 0;
    TMR0IE = 1;
}

// Interrupt service routine for Timer0
void __interrupt() isr(void)
{
    static unsigned short count = 0;

    if (TMR0IF)
    {
        TMR0 = TMR0 + 8;
        if (++count >= 20000)
        {
            if (flagA)
            {
                update_time();
            }
            count = 0;
        }
        TMR0IF = 0;
    }
}

// Update timekeeping variables
void update_time(void)
{
    seconds++;
    if (seconds == 60)
    {
        seconds = 0;
        minutes++;
        if (minutes == 60)
        {
            minutes = 0;
            hours++;
            if (hours == 24)
            {
                hours = 0;
            }
        }
    }
}

// Initialize configuration and setup
void init_config(void)
{
    PEIE = 1;
    TRISD = 0x00;
    TRISA = 0xF0;
    TRISC = 0xFF;
    PORTA = 0xF0;

    init_timer0();
    GIE = 1;
}

// Display time in normal mode
void display1(void)
{
    ssd[0] = digit[hours / 10];
    ssd[1] = (seconds % 2 == 0) ? digit[hours % 10] : digit[hours % 10] | DOT;
    ssd[2] = digit[minutes / 10];
    ssd[3] = digit[minutes % 10];

    for (int i = 0; i < 4; i++)
    {
        PORTD = ssd[i];
        PORTA = (PORTA & 0xF0) | (0x01 << i);
        for (int wait = 1000; wait--;);
    }
}

unsigned short delay = 0;

// Display time in configuration mode
void display2(void)
{
    if (flagB == 1)
    {
        ssd[2] = digit[minutes / 10];
        ssd[3] = digit[minutes % 10];
        if (delay++ == 50)
        {
            ssd[0] = dig[0];
            ssd[1] = dig[0];
        }
        else if (delay == 100)
        {
            ssd[0] = digit[hours / 10];
            ssd[1] = digit[hours % 10];
            delay = 0;
        }
    }
    else
    {
        ssd[0] = digit[hours / 10];
        ssd[1] = digit[hours % 10];
        if (delay++ == 50)
        {
            ssd[2] = dig[0];
            ssd[3] = dig[0];
        }
        else if (delay == 100)
        {
            ssd[2] = digit[minutes / 10];
            ssd[3] = digit[minutes % 10];
            delay = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        PORTD = ssd[i];
        PORTA = (PORTA & 0xF0) | (0x01 << i);
        for (int wait = 1000; wait--;);
    }
}
