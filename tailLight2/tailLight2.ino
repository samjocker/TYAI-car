#include <FastLED.h>
#define LED_PIN     6
#define NUM_LEDS    200
CRGB leds[NUM_LEDS];
bool rightLightArrow2[20][10] = {{0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,1,1,0,0,0,0},
                                {0,0,0,1,1,1,1,0,0,0},
                                {0,0,1,1,0,0,1,1,0,0},
                                {0,1,1,0,0,0,0,1,1,0},
                                {0,0,0,0,1,1,0,0,0,0},
                                {0,0,0,1,1,1,1,0,0,0},
                                {0,0,1,1,0,0,1,1,0,0},
                                {0,1,1,0,0,0,0,1,1,0},
                                {0,0,0,0,1,1,0,0,0,0},
                                {0,0,0,1,1,1,1,0,0,0},
                                {0,0,1,1,0,0,1,1,0,0},
                                {0,1,1,0,0,0,0,1,1,0},
                                {0,0,0,0,1,1,0,0,0,0},
                                {0,0,0,1,1,1,1,0,0,0},
                                {0,0,1,1,0,0,1,1,0,0},
                                {0,1,1,0,0,0,0,1,1,0},
                                {0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0}};

int step = 0;
long siteLightTime = 0;
long siteLightBlingTime = 0;
// long zAxisDebounceTime = 0;
// bool zAxisDebounce = true;
bool siteLightBling = true;
bool lightOn = true;
bool lightDebounce = true;
bool lightOpenR = false;
bool lightOpenL = false;
void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  // 4 is right,and 5 is left.
  pinMode(7,INPUT);
}
void loop() {
  // ----- tailLightStepControl -----
  if (millis()-siteLightTime > 35){
    siteLightTime = millis();
    if (lightOpenR || lightOpenL){
      if (step < 19) step++;
      else{
        step = 0;
        delay(300);
        FastLED.clear();
      }
    }
  }
  // --------------------------------

  if (millis()-siteLightBlingTime > 500) {
    siteLightBlingTime = millis();
    siteLightBling = !siteLightBling;
  }

  // if (millis()-zAxisDebounceTime > 20) {
  //   zAxisDebounceTime = millis();
  //   Serial.println(digitalRead(7));
  //   if (!digitalRead(7) && zAxisDebounce) {
  //     zAxisDebounce = false;
  //     lightOn = !lightOn;
  //   } else if (digitalRead(7) && !zAxisDebounce) {
  //     zAxisDebounce = true;
  //   }
  // }

  if (analogRead(A3) > 700 && lightDebounce) {
    lightDebounce = false;
     if (lightOpenL) {
      lightOpenR = false;
      lightOpenL = false;
      FastLED.clear();
    } else {
      lightOpenR = true;
      lightOpenL = false;
    }
  } else if (analogRead(A3) < 300 && lightDebounce) {
    lightDebounce = false;
    if (lightOpenR) {
      lightOpenR = false;
      lightOpenL = false;
      FastLED.clear();
    } else {
      lightOpenR = false;
      lightOpenL = true;
    }
  } else if (analogRead(A3) <= 700 && analogRead(A3) >= 300 && !lightDebounce) {
    lightDebounce = true;
    FastLED.clear();
  }

  if (lightOpenR) {
    digitalWrite(4,siteLightBling);
    digitalWrite(5,LOW);
    //  ----- tailLight -----
    for (int j=0;j<10;j++){
      if (rightLightArrow2[19-step][j] == 1){
        leds[j+10*(step)] = CRGB ( 255, 80, 0);
      } 
    }
    if ((step-1)%4 == 0){
      FastLED.show();
    }
    //  ----- tailLight end -----
  } else if (lightOpenL) {
    digitalWrite(4,LOW);
    digitalWrite(5,siteLightBling);
    //  ----- tailLight -----
    for (int j=0;j<10;j++){
      if (rightLightArrow2[19-step][j] == 1){
        leds[j+10*(19-step)] = CRGB ( 255, 80, 0);
      } 
    }
    if ((step-1)%4 == 0){
      FastLED.show();
    }
    //  ----- tailLight end -----
  } else {
    if (lightOn) {
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
    } else {
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
    }
    FastLED.clearData();
    FastLED.show();
  }
  
  
}
