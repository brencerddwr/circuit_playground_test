#include <Adafruit_CircuitPlayground.h>
#include <FastLED.h>

#define NUM_LEDS 10
#define DATA_PIN 17
unsigned long last_start;
unsigned int new_led_delay = 750;
unsigned int fade_delay = 50;

CRGB leds[NUM_LEDS];

void setup()
{

	CircuitPlayground.begin();
	

	// sanity check delay - allows reprogramming if accidentally blowing power w/leds
	delay(3000);


	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(0xB0FFFF);
	
	// set master brightness to enable FastLED dithering
	FastLED.setBrightness(64);
	last_start = millis();


}

void loop()
{

	fadeToBlackBy( leds, NUM_LEDS, 10);
	if (millis()-last_start > new_led_delay)
	{
		FastLED.setBrightness(constrain(map (CircuitPlayground.lightSensor(),0,1023,0,255),10,255));
		int x = random16(NUM_LEDS);
		if (!leds[x])
		{
			leds[ x ] += CHSV( random8(), random8( 192, 255), 255);
			last_start = millis();
		}
	}
	FastLED.show();
	FastLED.delay(fade_delay);
	
}
