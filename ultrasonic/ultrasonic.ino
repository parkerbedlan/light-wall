#include <Adafruit_NeoPixel.h>

#define PIN 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(150, PIN, NEO_RGB + NEO_KHZ800);

#define ECHO 9
#define TRIG 8

long duration;
long distance;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pixels.begin();
  pixels.setBrightness(100);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = duration*0.034/2;

  if(distance < 35){
    int pix = distance/3.35;
    pixels.clear();
    Serial.println(distance);
    Serial.print(" ");
    for(int i = 0; i<distance; i++){
      pixels.setPixelColor(pix, pixels.Color((27*pix), 255-(27*pix), (27*pix)));
    }
    pixels.show();
  }
  else{
//    pixels.clear();
    pixels.show();
  }
}
