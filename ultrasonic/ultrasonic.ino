#include <Adafruit_NeoPixel.h>

#define PIN 2

const int numReadings = 10;

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

int total = 0;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pixels.begin();
  pixels.setBrightness(100);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //TODO: Rewrite this to not block the thread with delay()
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = pulseIn(ECHO, HIGH);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  distance = (total / numReadings)*0.034/2;

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
