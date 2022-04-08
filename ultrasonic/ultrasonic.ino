#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define LEDPIN 7

#define ECHO 11
#define TRIG 13

//magic numbers
const int LED_BEGINNING = 1; //dead space between sensors and LEDs (cm)
const int LED_END = 40; //end of LED board (cm)
const int OOB_TOLERANCE = 20; //how many out-of-bounds readings before the LEDs turn off
const int CM_TO_PIX = 3.35; //spacing of LEDs
const int WIDTH = 12; //and length

const int NUM_READINGS = 6;
const int NUM_SENSORS = 1;

int sensorReadings[NUM_SENSORS][NUM_READINGS + 3] = {0}; 
// [...readings, index, total, oobCount] for each sensor

enum SENS {
  SENS_idx = NUM_READINGS,
  SENS_tot = NUM_READINGS + 1,
  SENS_oob = NUM_READINGS + 2
};

const int PIXEL_NUMS[12][12] = {
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

Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, LEDPIN, NEO_RGB + NEO_KHZ800);

bool isInBounds(int distance){
  return true;
  //return distance > LED_BEGINNING && distance <= LED_END;
}

/**
 * @brief After reading a new value from the ultrasonic sensor, 
 * if it is in bounds, adds it to the buffer and recalculates the 
 * smoothed distance for that sensor. If all sensors are out of bounds, turns off the 
 * LEDs
 * 
 * @param newReading the reading, in cm, most recently taken from the sensor
 * @param sensor which sensor took the reading
 * @return the smoothed distance, in cm, from the sensor, or -1 if out of bounds
 */
int smoothReading(int newReading, int sensor){ //newReading, sensor
  if(isInBounds(newReading)){
    int* data = sensorReadings[sensor];
  //  for(int i = 0; i < NUM_READINGS + 3; i++){
  //    Serial.print("index : ");
  //    Serial.print(i);
  //    Serial.print("  value: ");
  //    Serial.println(data[i]);
  //  }
    #define readIndex data[SENS_idx]

    data[SENS_oob] = 0; //reset out of bounds count

    data[SENS_tot] -= data[readIndex]; //subtract last from total
    data[readIndex] = newReading; //replace with new
    data[SENS_tot] += data[readIndex];
    
    readIndex++;
    if(readIndex >= NUM_READINGS) {
      readIndex = 0;
    }

    return data[SENS_tot] / NUM_READINGS;

  }
  else { //cur reading out of bounds
    sensorReadings[sensor][SENS_oob]++;
    bool inBounds = false;
    //check if all sensors out of bounds
    for(int i = 0; i < NUM_SENSORS; i++) { 
      if(sensorReadings[i][SENS_oob] < OOB_TOLERANCE) {
        inBounds = true;
      }
    }
    if(!inBounds) {
      turnOffLeds();
    }
    return -1;
  }
}

uint32_t getRandomColor(){
  uint8_t r = rand() % 256;
  uint8_t g = rand() % 256;
  uint8_t b = rand() % 256;
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

void turnOnLEDs(int pixel) {
  if(pixel >= WIDTH) return;
  strip.clear();
  for(int i = 0; i < WIDTH; i++) {
    strip.setPixelColor(PIXEL_NUMS[pixel][i], strip.gamma32(getRandomColor()));
  }
  strip.show();
}

void turnOffLeds() {
  strip.clear();
  strip.show();
}

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  strip.begin();
  strip.setBrightness(100);
  Serial.begin(9600);
}

int outOfBoundsCount = 0;

void loop() {
  // put your main code here, to run repeatedly:

  //TODO: Rewrite this to not block the thread with delay()
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  int newestReading = pulseIn(ECHO, HIGH);
  
  int distance = smoothReading(newestReading, 0)*0.034/2 - 16.5;
  Serial.println(distance);
  if(isInBounds(distance)){
    int pix = distance/CM_TO_PIX;
    turnOnLEDs(pix);
  }
}
