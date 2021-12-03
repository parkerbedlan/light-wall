#include <Adafruit_NeoPixel.h>

#define PIN 7

int pixelNums[12][12] = {
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
  {23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12},
  {24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
  {47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36},
  {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
  {71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60},
  {72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83},
  {95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84},
  {96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107},
  {119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108},
  {120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131},
  {143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132}
};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(144, PIN, NEO_RGB + NEO_KHZ800);

#define ECHO 11
#define TRIG 13

const int numReadings = 10;

int readings[numReadings];     
int readIndex = 0;             
int total = 0;                
int distance = 0;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pixels.begin();
  pixels.setBrightness(100);
  Serial.begin(9600);
}

long ts = millis();

void loop() {
  // put your main code here, to run repeatedly:

  //TODO: Rewrite this to not block the thread with delay()
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  total = total - readings[readIndex];
  readings[readIndex] = pulseIn(ECHO, HIGH)*0.034/2;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  distance = (total / numReadings) - 16.5;

  if (distance <= 40 && distance > 1) {
    int pix = distance/3.35;
    pixels.clear();
    Serial.println(distance);
    Serial.print(" ");
    for(int i = 0; i<12; i++){
      pixels.setPixelColor(pixelNums[pix][i], pixels.Color(255-(21*pix), (21*pix), (21*pix)));
    }
    pixels.show();
  }
//    else{
//      pixels.clear();
//      pixels.show();
//    }
}
