
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define TIMERPIN       10
#define SCOREPIN       12
#define SWITCHPIN      8
#define OBSTACLEPIN    11
#define NUMPIXELS      30
#define NUMPIXELS_SCORE  50

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, TIMERPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS_SCORE, SCOREPIN, NEO_GRB + NEO_KHZ800);
int delayval = 2000; // delay for half a second
int blinkdelay = 500;
int pixel_counter = 0;
int pixel1_counter = 0;
int switchState = 0;
int timeInterval = 1000;
int incremental = 0;


void blinking(int num_blinks, int num_pixels) {
  for (int j = 0; j < num_blinks ; j++) {
    if (j % 2 == 0) {
      for (int k = 0 ; k < num_pixels ; k++) {
        pixels1.setPixelColor(k, pixels1.Color(150, 150, 35));
        pixels.setPixelColor(k, pixels.Color(150, 150, 35));
      }
      delay(blinkdelay);
      pixels1.show();
      pixels.show();
    }
    else {
      for (int k = 0 ; k < num_pixels ; k++) {
        pixels1.setPixelColor(k, pixels1.Color(0, 0, 0));
        pixels.setPixelColor(k, pixels.Color(0, 0, 0));
      }
      delay(blinkdelay);
      pixels1.show();
      pixels.show();
    }
  }
}

void setup() {

  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);

  // End of trinket special code
  Serial.begin(9600);
  pinMode(SWITCHPIN, INPUT_PULLUP);
  pixels.begin();
  pixels1.begin();// This initializes the NeoPixel library.
}

void loop() {

  const unsigned long startTime = millis(); //50
  int num_seconds = (millis() - startTime) / 1000;
  if (pixel1_counter == 15 || pixel_counter == 30){
      blinking(6,30);
      while (1){
        // Do nothing until reset button is pressed
      }
  }
  
  
  if (actAfterDelay(startTime, 2000)) {
    countUpLED();
    Serial.println("HI");
  }
  else {

    if (actAfterDelay2(startTime, 50)) {
      if (digitalRead(SWITCHPIN) == LOW && switchState == 0) {
        if (pixel1_counter == 15) {
          blinking(6, 30);
          pixel1_counter = 0;
          
        }
        if (pixel1_counter % 3 == 0) {
          pixels1.setPixelColor(pixel1_counter, pixels1.Color(35, 150, 35)); 
        }        
        if (pixel1_counter % 3 == 1) {
          pixels1.setPixelColor(pixel1_counter, pixels1.Color(150, 35, 35)); 
        }
        if (pixel1_counter % 3 == 2) {
          pixels1.setPixelColor(pixel1_counter, pixels1.Color(35, 35, 150)); 
        }
        pixel1_counter ++;
        switchState = 1;
        Serial.println(pixel1_counter);
        pixels1.show();
      }
    }
    else if (digitalRead(SWITCHPIN) == HIGH && switchState == 1) {
      switchState = 0;
    }
  }
}

bool actAfterDelay(unsigned long startTime, int timeInterval) {
  static unsigned long prevTime = startTime;
  unsigned long currentTime = millis();
  if ((currentTime - prevTime) >= timeInterval) {
    prevTime = currentTime;
    return true;
  }
  else {
    return false;
  }
}


bool actAfterDelay2(unsigned long startTime, int timeInterval) {
  static unsigned long prevTime = startTime;
  unsigned long currentTime = millis();
  if ((currentTime - prevTime) >= timeInterval) {
    prevTime = currentTime;
    return true;
  }
  else {
    return false;
  }
}

void countUpLED() {
  if (pixel_counter == 30) {
    blinking(6, 30);
    pixel_counter ++;
  }
  if (pixel_counter % 3 == 0) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(pixel_counter, pixels.Color(35, 150, 35)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

\
  }
  if (pixel_counter % 3 == 1) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(pixel_counter, pixels.Color(150, 35, 35)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  }
  if (pixel_counter % 3 == 2) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(pixel_counter, pixels.Color(35, 35, 150)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  }
  pixel_counter ++;
}


