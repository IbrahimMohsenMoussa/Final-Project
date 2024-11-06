#ifndef ATMEGA32_REGISTERS_H
#define ATMEGA32_REGISTERS_H

#include"../common/std_types.h"
// GPIO Ports
union PORTA_reg {
    uint8 byte;
    struct {
        uint8 pa0 :1;
        uint8 pa1 :1;
        uint8 pa2 :1;
        uint8 pa3 :1;
        uint8 pa4 :1;
        uint8 pa5 :1;
        uint8 pa6 :1;
        uint8 pa7 :1;
    } bits;
};
union DDRA_reg {
    uint8 byte;
    struct {
        uint8 dda0 :1;
        uint8 dda1 :1;
        uint8 dda2 :1;
        uint8 dda3 :1;
        uint8 dda4 :1;
        uint8 dda5 :1;
        uint8 dda6 :1;
        uint8 dda7 :1;
    } bits;
};
union PINA_reg {
    uint8 byte;
    struct {
        uint8 pina0 :1;
        uint8 pina1 :1;
        uint8 pina2 :1;
        uint8 pina3 :1;
        uint8 pina4 :1;
        uint8 pina5 :1;
        uint8 pina6 :1;
        uint8 pina7 :1;
    } bits;
};

union PORTB_reg {
    uint8 byte;
    struct {
        uint8 pb0 :1;
        uint8 pb1 :1;
        uint8 pb2 :1;
        uint8 pb3 :1;
        uint8 pb4 :1;
        uint8 pb5 :1;
        uint8 pb6 :1;
        uint8 pb7 :1;
    } bits;
};
union DDRB_reg {
    uint8 byte;
    struct {
        uint8 ddb0 :1;
        uint8 ddb1 :1;
        uint8 ddb2 :1;
        uint8 ddb3 :1;
        uint8 ddb4 :1;
        uint8 ddb5 :1;
        uint8 ddb6 :1;
        uint8 ddb7 :1;
    } bits;
};
union PINB_reg {
    uint8 byte;
    struct {
        uint8 pinb0 :1;
        uint8 pinb1 :1;
        uint8 pinb2 :1;
        uint8 pinb3 :1;
        uint8 pinb4 :1;
        uint8 pinb5 :1;
        uint8 pinb6 :1;
        uint8 pinb7 :1;
    } bits;
};

union PORTC_reg {
    uint8 byte;
    struct {
        uint8 pc0 :1;
        uint8 pc1 :1;
        uint8 pc2 :1;
        uint8 pc3 :1;
        uint8 pc4 :1;
        uint8 pc5 :1;
        uint8 pc6 :1;
        uint8 pc7 :1;
    } bits;
};
union DDRC_reg {
    uint8 byte;
    struct {
        uint8 ddc0 :1;
        uint8 ddc1 :1;
        uint8 ddc2 :1;
        uint8 ddc3 :1;
        uint8 ddc4 :1;
        uint8 ddc5 :1;
        uint8 ddc6 :1;
        uint8 ddc7 :1;
    } bits;
};
union PINC_reg {
    uint8 byte;
    struct {
        uint8 pinc0 :1;
        uint8 pinc1 :1;
        uint8 pinc2 :1;
        uint8 pinc3 :1;
        uint8 pinc4 :1;
        uint8 pinc5 :1;
        uint8 pinc6 :1;
        uint8 pinc7 :1;
    } bits;
};

union PORTD_reg {
    uint8 byte;
    struct {
        uint8 pd0 :1;
        uint8 pd1 :1;
        uint8 pd2 :1;
        uint8 pd3 :1;
        uint8 pd4 :1;
        uint8 pd5 :1;
        uint8 pd6 :1;
        uint8 pd7 :1;
    } bits;
};
union DDRD_reg {
    uint8 byte;
    struct {
        uint8 ddd0 :1;
        uint8 ddd1 :1;
        uint8 ddd2 :1;
        uint8 ddd3 :1;
        uint8 ddd4 :1;
        uint8 ddd5 :1;
        uint8 ddd6 :1;
        uint8 ddd7 :1;
    } bits;
};
union PIND_reg {
    uint8 byte;
    struct {
        uint8 pind0 :1;
        uint8 pind1 :1;
        uint8 pind2 :1;
        uint8 pind3 :1;
        uint8 pind4 :1;
        uint8 pind5 :1;
        uint8 pind6 :1;
        uint8 pind7 :1;
    } bits;
};

// Timer 0
union TCCR0_reg {
    uint8 byte;
    struct {
        uint8 cs00 :1;
        uint8 cs01 :1;
        uint8 cs02 :1;
        uint8 wgm01 :1;
        uint8 com00 :1;
        uint8 com01 :1;
        uint8 wgm00 :1;
        uint8 foc0 :1;
    } bits;
};

union TCNT0_reg {
    uint8 byte;
};

union OCR0_reg {
    uint8 byte;
};

// Timer 1
union TCCR1A_reg {
    uint8 byte;
    struct {
        uint8 wgm10 :1;
        uint8 wgm11 :1;
        uint8 foc1b :1;
        uint8 foc1a :1;
        uint8 com1b0 :1;
        uint8 com1b1 :1;
        uint8 com1a0 :1;
        uint8 com1a1 :1;
    } bits;
};

union TCCR1B_reg {
    uint8 byte;
    struct {
        uint8 cs10 :1;
        uint8 cs11 :1;
        uint8 cs12 :1;
        uint8 wgm12 :1;
        uint8 wgm13 :1;
        uint8 ices1 :1;
        uint8 icnc1 :1;
        uint8 :1;
    } bits;
};

union TCNT1_reg {
    struct {
        uint8 tcnt1l;
        uint8 tcnt1h;
    } bytes;
    uint16 word;
};

union OCR1A_reg {
    struct {
        uint8 ocr1al;
        uint8 ocr1ah;
    } bytes;
    uint16 word;
};

union OCR1B_reg {
    struct {
        uint8 ocr1bl;
        uint8 ocr1bh;
    } bytes;
    uint16 word;
};

union ICR1_reg {
    struct {
        uint8 icr1l;
        uint8 icr1h;
    } bytes;
    uint16 word;
};

// Timer/Counter 2
union TCCR2_reg {
    uint8 byte;
    struct {
        uint8 cs20 :1;
        uint8 cs21 :1;
        uint8 cs22 :1;
        uint8 wgm21 :1;
        uint8 com20 :1;
        uint8 com21 :1;
        uint8 wgm20 :1;
        uint8 foc2 :1;
    } bits;
};

union TCNT2_reg {
    uint8 byte;
};

union OCR2_reg {
    uint8 byte;
};

// Interrupt Registers
union SREG_reg {
    uint8 byte;
    struct {
        uint8 c :1;
        uint8 z :1;
        uint8 n :1;
        uint8 v :1;
        uint8 s :1;
        uint8 h :1;
        uint8 t :1;
        uint8 i :1;
    } bits;
};

union TIMSK_reg {
    uint8 byte;
    struct {
        uint8 toie0 :1;
        uint8 ocie0 :1;
        uint8 toie1 :1;
        uint8 ocie1b :1;
        uint8 ocie1a :1;
        uint8 ticie1 :1;
        uint8 toie2 :1;
        uint8 ocie2 :1;
    } bits;
};

union TIFR_reg {
    uint8 byte;
    struct {
        uint8 tov0 :1;
        uint8 ocf0 :1;
        uint8 tov1 :1;
        uint8 ocf1b :1;
        uint8 ocf1a :1;
        uint8 icf1 :1;
        uint8 tov2 :1;
        uint8 ocf2 :1;
    } bits;
};

// ADC Registers
union ADMUX_reg {
    uint8 byte;
    struct {
        uint8 mux0 :1;
        uint8 mux1 :1;
        uint8 mux2 :1;
        uint8 mux3 :1;
        uint8 mux4 :1;
        uint8 adlar :1;
        uint8 refs0 :1;
        uint8 refs1 :1;
    } bits;
};

union ADCSRA_reg {
    uint8 byte;
    struct {
        uint8 adps0 :1;
        uint8 adps1 :1;
        uint8 adps2 :1;
        uint8 adie :1;
        uint8 adif :1;
        uint8 adate :1;
        uint8 adsc :1;
        uint8 aden :1;
    } bits;
};

union ADC_reg {

    uint16 value;
};

// EEPROM Registers
union EEAR_reg {
    struct {
        uint8 eearl;
        uint8 eearh;
    } bytes;
    uint16 word;
};

union EEDR_reg {
    uint8 byte;
};

union EECR_reg {
    uint8 byte;
    struct {
        uint8 eere :1;
        uint8 eewe :1;
        uint8 eemwe :1;
        uint8 eerie :1;
        uint8 :4;
    } bits;
};

// SPI Registers
union SPCR_reg {
    uint8 byte;
    struct {
        uint8 spr0 :1;
        uint8 spr1 :1;
        uint8 cpha :1;
        uint8 cpol :1;
        uint8 mstr :1;
        uint8 dord :1;
        uint8 spe :1;
        uint8 spie :1;
    } bits;
};

union SPSR_reg {
    uint8 byte;
    struct {
        uint8 spi2x :1;
        uint8 :5;
        uint8 wcol :1;
        uint8 spif :1;
    } bits;
};

union SPDR_reg {
    uint8 byte;
};

// USART Registers
union UBRRH_reg {
    uint8 byte;
    struct {
        uint8 ubrr8 :1;
        uint8 ubrr9 :1;
        uint8 ubrr10 :1;
        uint8 ubrr11 :1;
        uint8 :3;
        uint8 ursel :1;
    } bits;
};

union UBRRL_reg {
    uint8 byte;
};

union UCSRA_reg {
    uint8 byte;
    struct {
        uint8 mpcm :1;
        uint8 u2x :1;
        uint8 pe :1;
        uint8 dor :1;
        uint8 fe :1;
        uint8 udre :1;
        uint8 txc :1;
        uint8 rxc :1;
    } bits;
};

union UCSRB_reg {
    uint8 byte;
    struct {
        uint8 txb8 :1;
        uint8 rxb8 :1;
        uint8 ucsz2 :1;
        uint8 txen :1;
        uint8 rxen :1;
        uint8 udrie :1;
        uint8 txcie :1;
        uint8 rxcie :1;
    } bits;
};

union UCSRC_reg {
    uint8 byte;
    struct {
        uint8 ucpol :1;
        uint8 ucsz0 :1;
        uint8 ucsz1 :1;
        uint8 usbs :1;
        uint8 upm0 :1;
        uint8 upm1 :1;
        uint8 umsel :1;
        uint8 ursel :1;
    } bits;
};

union UDR_reg {
    uint8 byte;
};

// TWI Registers
union TWBR_reg {
    uint8 byte;
};

union TWSR_reg {
    uint8 byte;
    struct {
        uint8 twps0 :1;
        uint8 twps1 :1;
        uint8 :1;
        uint8 tws3 :1;
        uint8 tws4 :1;
        uint8 tws5 :1;
        uint8 tws6 :1;
        uint8 tws7 :1;
    } bits;
};

union TWAR_reg {
    uint8 byte;
    struct {
        uint8 twgce :1;
        uint8 twa0 :1;
        uint8 twa1 :1;
        uint8 twa2 :1;
        uint8 twa3 :1;
        uint8 twa4 :1;
        uint8 twa5 :1;
        uint8 twa6 :1;
    } bits;
};

union TWDR_reg {
    uint8 byte;
};

union TWCR_reg {
    uint8 byte;
    struct {
        uint8 twie :1;
        uint8 twen :1;
        uint8 twwc :1;
        uint8 twsto :1;
        uint8 twsta :1;
        uint8 twea :1;
        uint8 twint :1;
        uint8 :1;
    } bits;
};

// Watchdog Timer
union WDTCR_reg {
    uint8 byte;
    struct {
        uint8 wdp0 :1;
        uint8 wdp1 :1;
        uint8 wdp2 :1;
        uint8 wde :1;
        uint8 wdtoe :1;
        uint8 :3;
    } bits;
};

// Power Management, Oscillators, and Miscellaneous
union OSCCAL_reg {
    uint8 byte;
};

union SFIOR_reg {
    uint8 byte;
    struct {
        uint8 psr10 :1;
        uint8 psr2 :1;
        uint8 pud :1;
        uint8 acme :1;
        uint8 adts0 :1;
        uint8 adts1 :1;
        uint8 adts2 :1;
        uint8 :1;
    } bits;
};

union MCUCSR_reg {
    uint8 byte;
    struct {
        uint8 porf :1;
        uint8 extrf :1;
        uint8 borf :1;
        uint8 wdrf :1;
        uint8 jtrf :1;
        uint8 :3;
    } bits;
};

union MCUCR_reg {
    uint8 byte;
    struct {
        uint8 isc00 :1;
        uint8 isc01 :1;
        uint8 isc10 :1;
        uint8 isc11 :1;
        uint8 sm0 :1;
        uint8 sm1 :1;
        uint8 sm2 :1;
        uint8 se :1;
    } bits;
};

union SPMCR_reg {
    uint8 byte;
    struct {
        uint8 spmen :1;
        uint8 pgers :1;
        uint8 pgwrt :1;
        uint8 blbset :1;
        uint8 rwwsre :1;
        uint8 rwwsb :1;
        uint8 spmie :1;
        uint8 :1;
    } bits;
};

// Memory-mapped register macros
#define PORTA_REG   (*((volatile union PORTA_reg *)0x3B))
#define DDRA_REG    (*((volatile union DDRA_reg *)0x3A))
#define PINA_REG    (*((volatile union PINA_reg *)0x39))

#define PORTB_REG   (*((volatile union PORTB_reg *)0x38))
#define DDRB_REG    (*((volatile union DDRB_reg *)0x37))
#define PINB_REG    (*((volatile union PINB_reg *)0x36))

#define PORTC_REG   (*((volatile union PORTC_reg *)0x35))
#define DDRC_REG    (*((volatile union DDRC_reg *)0x34))
#define PINC_REG    (*((volatile union PINC_reg *)0x33))

#define PORTD_REG   (*((volatile union PORTD_reg *)0x32))
#define DDRD_REG    (*((volatile union DDRD_reg *)0x31))
#define PIND_REG    (*((volatile union PIND_reg *)0x30))

// Timer/Counter 0

#define TCCR0_REG   (*((volatile union TCCR0_reg *)0x53))
#define TCNT0_REG   (*((volatile union TCNT0_reg *)0x52))
#define OCR0_REG    (*((volatile union OCR0_reg *)0x5C))
// Timer/Counter 1
#define TCCR1A_REG  (*((volatile union TCCR1A_reg *)0x4F))
#define TCCR1B_REG  (*((volatile union TCCR1B_reg *)0x4E))
#define TCNT1_REG   (*((volatile union TCNT1_reg *)0x4C))
#define OCR1A_REG   (*((volatile union OCR1A_reg *)0x4A))
#define OCR1B_REG   (*((volatile union OCR1B_reg *)0x48))
#define ICR1_REG    (*((volatile union ICR1_reg *)0x46))

// Timer/Counter 2
#define TCCR2_REG   (*((volatile union TCCR2_reg *)0x45))
#define TCNT2_REG   (*((volatile union TCNT2_reg *)0x44))
#define OCR2_REG    (*((volatile union OCR2_reg *)0x43))

// Interrupt Registers
#define SREG_REG    (*((volatile union SREG_reg *)0x5F))
#define TIMSK_REG   (*((volatile union TIMSK_reg *)0x59))
#define TIFR_REG    (*((volatile union TIFR_reg *)0x58))

// ADC Registers
#define ADMUX_REG   (*((volatile union ADMUX_reg *)0x27))
#define ADCSRA_REG  (*((volatile union ADCSRA_reg *)0x26))
#define ADC_REG     (*((volatile union ADC_reg *)0x24))

// EEPROM Registers
#define EEAR_REG    (*((volatile union EEAR_reg *)0x3E))
#define EEDR_REG    (*((volatile union EEDR_reg *)0x3D))
#define EECR_REG    (*((volatile union EECR_reg *)0x3C))

// SPI Registers
#define SPCR_REG    (*((volatile union SPCR_reg *)0x2D))
#define SPSR_REG    (*((volatile union SPSR_reg *)0x2E))
#define SPDR_REG    (*((volatile union SPDR_reg *)0x2F))

// USART Registers
#define UBRRH_REG   (*((volatile union UBRRH_reg *)0x40))
#define UBRRL_REG   (*((volatile union UBRRL_reg *)0x29))
#define UCSRA_REG   (*((volatile union UCSRA_reg *)0x2B))
#define UCSRB_REG   (*((volatile union UCSRB_reg *)0x2A))
#define UCSRC_REG   (*((volatile union UCSRC_reg *)0x40))
#define UDR_REG     (*((volatile union UDR_reg *)0x2C))

// TWI Registers
#define TWBR_REG    (*((volatile union TWBR_reg *)0x20))
#define TWSR_REG    (*((volatile union TWSR_reg *)0x21))
#define TWAR_REG    (*((volatile union TWAR_reg *)0x22))
#define TWDR_REG    (*((volatile union TWDR_reg *)0x23))
#define TWCR_REG    (*((volatile union TWCR_reg *)0x56))

// Watchdog Timer
#define WDTCR_REG   (*((volatile union WDTCR_reg *)0x41))

// Oscillator and Power Management
#define OSCCAL_REG  (*((volatile union OSCCAL_reg *)0x51))
#define SFIOR_REG   (*((volatile union SFIOR_reg *)0x50))
#define MCUCSR_REG  (*((volatile union MCUCSR_reg *)0x54))
#define MCUCR_REG   (*((volatile union MCUCR_reg *)0x55))
#define SPMCR_REG   (*((volatile union SPMCR_reg *)0x57))

#endif // ATMEGA32_REGISTERS_H
