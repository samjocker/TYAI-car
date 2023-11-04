#include <Adafruit_NeoPixel.h>
#define LED_PIN    6
#define LED_COUNT 200

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

bool state = false;
long timeSet = millis();
int lightStep = 19;
long lightTime = millis();
bool lightOn = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(10,INPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(115200);
  strip.begin();
  strip.show();
  strip.setBrightness(100);
}
int i = 0;
void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(analogRead(A0));
  digitalWrite(5,LOW);
  if (millis() - timeSet > 200) {
    timeSet = millis();
    state = !state;
  }
  if (millis() - lightTime > 8) {
    lightTime = millis();
    if (lightStep > 0){
      lightStep -= 1;
    } else {
      lightStep = 20;
    }
  }
  if(analogRead(A0) > 700){
    lightOn = true;
    if (state) {
      digitalWrite(9,HIGH);
      digitalWrite(8,LOW);
    } else {
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
    }

     for(int i=0; i<strip.numPixels(); i++) { 
      if (i/10 >= 20-lightStep) {
        strip.setPixelColor(i, strip.Color(0,   0,  0));
      } else if (lightStep == 0){
        strip.setPixelColor(i, strip.Color(255,   80,  0));
      }
       else {
        strip.setPixelColor(i, strip.Color(255,   80,  0));
      }
    }
    strip.show();

  }else if(analogRead(A0) < 300){
    lightOn = true;
    if (state) {
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
    } else {
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
    }

     for(int i=0; i<strip.numPixels(); i++) { 
      if (i/10 >= lightStep) {
        strip.setPixelColor(i, strip.Color(255,   80,  0));
      } else if (lightStep == 0){
        strip.setPixelColor(i, strip.Color(255,   80,  0));
      }
       else {
        strip.setPixelColor(i, strip.Color(0,   0,  0));
      }
    }
    strip.show();

  } else {
    lightOn = false;
  }

  if (digitalRead(10) && !lightOn) {
    for(int i=0; i<strip.numPixels(); i++) { 
      strip.setPixelColor(i, strip.Color(255,   0,   0));
    }
    strip.show();
  } else {
    for(int i=0; i<strip.numPixels(); i++) { 
      strip.setPixelColor(i, strip.Color(0,   0,   0));
    }
    strip.show();
  }
  
}