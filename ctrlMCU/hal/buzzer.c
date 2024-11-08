#include "buzzer.h"

#include"../common/std_types.h"
#include "../mcal/gpio.h"
#include"lcd.h"
#include<avr/io.h>
void Buzzer_init() {

		GPIO_ARR_setPinDirection(BUZZER_PIN, PIN_OUTPUT);

}

void Buzzer_on() {
#ifdef BUZZER_POSTIVE_LOGIC
	LCD_displayStringRowColumn(0,0,"buzzer on");
	GPIO_ARR_setPinState(BUZZER_PIN, LOGIC_HIGH);
//	PORTC|=(1<<7);
#else
	GPIO_ARR_setPinState(BUZZER_PIN,LOGIC_LOW);
#endif

}

void Buzzer_off() {
#ifdef BUZZER_POSTIVE_LOGIC
	LCD_displayStringRowColumn(0,0,"buzzer off");

	GPIO_ARR_setPinState(BUZZER_PIN, LOGIC_LOW);
	//PORTC&=~(1<<7);
#else
	GPIO_ARR_setPinState(BUZZER_PIN,LOGIC_HIGH);
#endif

}
