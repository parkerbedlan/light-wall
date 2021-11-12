#include <Adafruit_NeoPixel.h>

#define PIN 2

int pixelNums[9][9] = {
  {0, 1, 2, 3, 4, 5, 6, 7, 8}, 
  {10, 11, 12, 13, 14, 15, 16, 17, 18}, 
  {19, 20, 21, 22, 23, 24, 25, 26, 27}, 
  {29, 30, 31, 32, 33, 34, 35, 36, 37},
  {39, 40, 41, 42, 43, 44, 45, 46, 47},
  {49, 50, 51, 52, 53, 54, 55, 56, 57},
  {59, 60, 61, 62, 63, 64, 65, 66, 67},
  {69, 70, 71, 72, 73, 74, 75, 76, 77},
  {79, 80, 81, 82, 83, 84, 85, 86, 87}
};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(150, PIN, NEO_RGB + NEO_KHZ800);

#define ECHO 11
#define TRIG 13

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

  if(distance < 29){
    int pix = distance/3.35;
    pixels.clear();
    Serial.println(distance);
    Serial.print(" ");
    for(int i = 0; i<9; i++){
      pixels.setPixelColor(pixelNums[pix][i], pixels.Color(255-(27*pix), (27*pix), (27*pix)));
    }
    pixels.show();
  }
  else{
//    pixels.clear();
    pixels.show();
  }
}
