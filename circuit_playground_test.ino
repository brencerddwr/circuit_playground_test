#include <Adafruit_SleepyDog.h>
#include <FastLED.h>
#include <Adafruit_CircuitPlayground.h>

#define NUM_LEDS 10
#define DATA_PIN 17

unsigned long last_start;
unsigned int new_led_delay = 6500/NUM_LEDS;
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
	while (!CircuitPlayground.slideSwitch()) {
		// Turn off the pixels, then go into deep sleep for a second.
		FastLED.clear();
		FastLED.show();
		Watchdog.sleep(1000);
	}

	fadeToBlackBy( leds, NUM_LEDS, 10);
	if (millis()-last_start > new_led_delay)
	{
		FastLED.setBrightness(constrain(map (CircuitPlayground.lightSensor(),0,1023,0,255),10,255));
		byte x = random16(NUM_LEDS);
		if (!leds[x])
		{
			leds[ x ] += CHSV( random8(), random8( 128, 255), 255);
			last_start = millis();
		}
	}
	FastLED.show();
	FastLED.delay(fade_delay);
	
}
