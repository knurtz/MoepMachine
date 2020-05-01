#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ws2812/light/light_ws2812.h"

#define NUM_LEDS	8



/*

LED-Layout:

6>		<7


|5|		|0|

|4|		|1|

|3|		|2|


*/

struct cRGB ledFrame[NUM_LEDS];


void clearFrame() {
	for (int i = 0; i < NUM_LEDS; i++) ledFrame[i].r = ledFrame[i].g = ledFrame[i].b = 0;
}


void playStartAnimation() {
	
	//frame 1: bottom red
	ledFrame[2].r = ledFrame[3].r = 50;
	
	ws2812_setleds(ledFrame, NUM_LEDS);
	_delay_ms(500);
	
	//frame2: bottom yellow, middle red
	ledFrame[1].r = ledFrame[4].r = 50;
	ledFrame[2].g = ledFrame[3].g = 50;
	
	ws2812_setleds(ledFrame, NUM_LEDS);
	_delay_ms(500);
	
	//frame3: bottom green, middle yellow, top red
	ledFrame[0].r = ledFrame[5].r = 50;
	ledFrame[1].g = ledFrame[4].g = 50;
	ledFrame[2].r = ledFrame[3].r = 0;
	
	ws2812_setleds(ledFrame, NUM_LEDS);
	_delay_ms(1000);
	
	//frame4: same as frame3, but text blue
	ledFrame[6].b = ledFrame[7].b = 250;
	
	ws2812_setleds(ledFrame, NUM_LEDS);

}


void pulseVibration() {

	PORTB |= (1<<PORTB4);
	
	_delay_ms(200);
	
	PORTB &= ~(1<<PORTB4);

}

void pulseVibrationShort() {

	PORTB |= (1<<PORTB4);
	
	_delay_ms(100);
	
	PORTB &= ~(1<<PORTB4);

}


void turnOff() {

	PORTB |= (1<<PORTB3);
	
	//we should never reach this point in the real application because device should be turned off  now!
	_delay_ms(250);
	
	PORTB &= ~(1<<PORTB3);

}

void flashWarning() {

	
	PORTB |= (1<<PORTB4);
	
	_delay_ms(500);
	
	PORTB &= ~(1<<PORTB4);
	
	_delay_ms(500);


}



int main(void)
{

	//set b3 and b4 as outputs (mosfets)
	DDRB |= (1<<DDB3 | 1<<DDB4);

	//set b3 and b4 low
	PORTB &= ~(1<<PORTB3 | 1<<PORTB4);
	
	//set frame variable to all zero
	clearFrame();
	
	pulseVibrationShort();
	_delay_ms(100);
	pulseVibrationShort();
	
	playStartAnimation();
	
	pulseVibration();
	_delay_ms(200);
	pulseVibration();
	
	_delay_ms(500);
	
	turnOff();
	
	
	while(1) flashWarning();

}
  
