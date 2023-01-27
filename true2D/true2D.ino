#include <NewPing.h>
#include <Adafruit_NeoPixel.h>

#define LEDPIN 8


#define SONAR_NUM 12
#define MAX_DIST 45
#define PING_INTERVAL 28 
// was 33 for stability


// set up sensors
NewPing sonar[SONAR_NUM] = {
  NewPing(30, 31, MAX_DIST),  //S1 
  NewPing(32, 33, MAX_DIST),  //S2
  NewPing(47, 46, MAX_DIST),  //S3
  NewPing(48, 49, MAX_DIST),  //S4
  NewPing(38, 39, MAX_DIST),  //S5
  NewPing(36, 37, MAX_DIST),  //S6
  NewPing(26, 27, MAX_DIST),  //S7
  NewPing(52, 53, MAX_DIST),  //S8
  NewPing(23, 22, MAX_DIST),  //S9
  NewPing(34, 35, MAX_DIST),  //S10
  NewPing(40, 41, MAX_DIST),  //S11
  NewPing(42, 43, MAX_DIST)   //S12
};


#define AV 6

// [...readings, index, total, oobCount] for each sensor
int avgs[SONAR_NUM][AV+3] = {{0}};



//int avg1[av] = {0};
//int avg2[av] = {0};
//int avg3[av] = {0};
//int avg4[av] = {0};


unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.

Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, LEDPIN, NEO_RGB + NEO_KHZ800);

//const int PIXEL_NUMS[12][2] = {
//  {0,1},
//  {23,22},
//  {24,25},
//  {47,46},
//  {48,49},
//  {71,70},
//  {72,73},
//  {95,94},
//  {96,97},
//  {119,118},
//  {120,121},
//  {143,142}
//};

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

const uint32_t BLUE = strip.Color(64,8,255);
const uint32_t GREEN = strip.Color(46,209,80);
const uint32_t RED = strip.Color(232,31,16);

uint32_t colors[3] = {BLUE, GREEN, RED};
int coldx = 0;

uint32_t getRandomColor(){
  uint8_t r = rand() % 256;
  uint8_t g = rand() % 256;
  uint8_t b = rand() % 256;
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

bool found = true;
int place[2] = {-99, -99};
const int FROM_EDGE = 0;

void setup() {
  Serial.begin(115200); 
  strip.begin();
  strip.setBrightness(100);
  strip.clear();
  // put your setup code here, to run once:
  //strip.setPixelColor(PIXEL_NUMS[4][0], strip.gamma32(getRandomColor()));
  //strip.setPixelColor(PIXEL_NUMS[4][1], strip.gamma32(getRandomColor()));
  strip.show();

  pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++){ // Set the starting time for each sensor.
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
  }
  turnOnRow(2, GREEN);
}

void loop() {

  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
    if (millis() >= pingTimer[i]) {         // Is it this sensor's time to ping?
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
        if (i == 0 && currentSensor == SONAR_NUM - 1) {// Sensor ping cycle complete, do something with the results.
          singlePixel(); 
//          oneSensorCycle();
      }
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      cm[currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
      
      avgs[currentSensor][avgs[currentSensor][AV]] = cm[currentSensor]; // Sorry 
    }
  }
  // Other code that *DOESN'T* analyze ping results can go here.


//  int sum1 = 0;
//  int sum2 = 0;
//  int sum3 = 0;
//  int sum4 = 0;
//  
//  for(int i = 0; i<av; i++){
//    sum1 += avg1[i];
//    sum2 += avg2[i];
//    sum3 += avg3[i];
//    sum4 += avg4[i];
//  }
  
}

void echoCheck() { // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle() { // Sensor ping cycle complete, do something with the results.
  // The following code would be replaced with your code that does something with the ping results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print("S");
    Serial.print(i+1);
    Serial.print(" = ");
    char buf[10];
    sprintf(buf, "%02d", cm[i]);
    Serial.print(buf);
    Serial.print("cm  ");
  }
  Serial.println();
}

void singlePixel(){
  int mindx_X = -1;
  int minv_X = 9999;

  int mindx_Y= -1;
  int minv_Y = 9999;

  #define HALF_NUM SONAR_NUM/2
  for (uint8_t i = 0; i < HALF_NUM / 2; i++) {
//    Serial.print(i);
//    Serial.print("=");
//    Serial.print(cm[i]);
//    Serial.print("cm ");
    if(cm[i] < minv_X && cm[i] != 0){
      minv_X = cm[i];
      mindx_X = i;
    }
    if(cm[i+HALF_NUM] < minv_Y && cm[i+HALF_NUM] != 0){
      minv_Y = cm[i+HALF_NUM];
      mindx_Y = i+HALF_NUM;
    }
  }
  strip.clear();
  if(mindx_X != -1 && mindx_Y != -1){
    Serial.print("Min Sensor X: S");
    Serial.print(mindx_X+1);
    Serial.print(" = ");
    Serial.print(cm[mindx_X]);
    Serial.println();
    Serial.print("Min Sensor Y: S");
    Serial.print(mindx_Y+1);
    Serial.print(" = ");
    Serial.print(cm[mindx_Y]);
    Serial.println();

    int pix_X = (cm[mindx_X] / 3.4);
    int pix_Y = 12 - (cm[mindx_Y] / 3.4);
    
    strip.setPixelColor(PIXEL_NUMS[pix_Y][pix_X], strip.gamma32(RED));
  }
  
  strip.show();
  
}

void minSensorCycle() { // Sensor ping cycle complete, do something with the results.
  // The following code would be replaced with your code that does something with the ping results.
  int mindx = -1;
  int minv = 9999;
  
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
//    Serial.print(i);
//    Serial.print("=");
//    Serial.print(cm[i]);
//    Serial.print("cm ");
    if(cm[i] < minv && cm[i] != 0){
      minv = cm[i];
      mindx = i;
    }
  }
  if(mindx != -1){
    Serial.print("Min Sensor: S");
    Serial.print(mindx+1);
    Serial.print(" = ");
    Serial.print(cm[mindx]);
    Serial.println();
  }

  //0 -> 0, 1
  //1 -> 2, 3
  //2 -> 4, 5
  strip.clear();
  int pix = cm[mindx] / 3.4;
  pix = 12 - pix;
  strip.setPixelColor(PIXEL_NUMS[(mindx*2)][pix], strip.gamma32(GREEN));
  strip.setPixelColor(PIXEL_NUMS[(mindx*2)+1][pix], strip.gamma32(GREEN));
  strip.show();
  
}

void averageSensorReading(int sensorNum){
    int sum = 0;
    for(int i=0; i < AV; i++){
      sum += avgs[sensorNum][i];
    }
    avgs[sensorNum][AV+1] = sum;
}

void touchGame(){
  //avgd
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    avgs[i][avidx] = cm[i];    
  }
  avidx = (avidx++) % AV;
  for (uint8_t i = 0; i < SONAR_NUM; i++){
    int rtot = 0;
    for(uint8_t j = 0; j < AV; j++){
      rtot += avgs[i][j];
    }
    avgs[i][AV] = rtot / AV;
  }
  
  int mindx = -1;
  int minv = 9999;
  
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
//    Serial.print(i);
//    Serial.print("=");
//    Serial.print(cm[i]);
//    Serial.print("cm ");
    if(avgs[i][AV] < minv && avgs[i][AV] != 0){
      minv = avgs[i][AV];
      mindx = i;
    }
  }
  if(mindx != -1){
    Serial.print("Min Sensor: S");
    Serial.print(mindx+1);
    Serial.print(" = ");
    Serial.print(avgs[mindx][AV]);
    Serial.println();
  }
  
  if(found){
    strip.clear();
    place[0] = random(4, 35);
    place[1] = random(4, 35);
    Serial.print("New Target: ");
//    Serial.println(place);
    seekToRow(int(place[0]/3.4), BLUE); 
    found = false;
  }
//  else{
//    if(s1 > 0){
//      Serial.println();
//      Serial.print("Touch: ");
//      Serial.println(s1);
//      Serial.print("Difference: ");
//      Serial.println(abs(s1-place));
//      Serial.println();
////      Serial.print(int(s1/3.4));
////      Serial.println();
//      
//      if(abs(s1-place) < 4){
//        lightUpBoard(GREEN);
//        found = true;
//        delay(2000);
//        clearBoard();
//      }
//      else{
//        lightUpBoard(RED);
//        delay(1500);
//        turnOnRow(int(place/3.4), BLUE);
//      }
//    //  Serial.print("cm");
//    }
//  } 
}


void lightUpBoard(uint32_t c){
  strip.clear();
  for(int i = 0; i < 12; i++){
    for(int j = 0; j < 12; j++){
      strip.setPixelColor(PIXEL_NUMS[i][j], strip.gamma32(c));
    }
  }
  strip.show();
}

void seekToRow(int r, uint32_t c){
  int timing = 25;
  for(int i = 0; i < 12; i++){
    strip.clear();
    for(int j = 0; j < 12; j++){
      strip.setPixelColor(PIXEL_NUMS[i][j], strip.gamma32(c));
    }
    strip.show();
    delay(timing);
  }
  
  for(int i = 11; i >= 0; i--){
    strip.clear();
    for(int j = 0; j < 12; j++){
      strip.setPixelColor(PIXEL_NUMS[i][j], strip.gamma32(c));
    }
    strip.show();
    delay(timing);
  }

  for(int i = 0; i <= r; i++){
    strip.clear();
    for(int j = 0; j < 12; j++){
      strip.setPixelColor(PIXEL_NUMS[i][j], strip.gamma32(c));
    }
    strip.show();
    delay(timing);
  }
  strip.show();
}

void clearBoard(){
  strip.clear();
  strip.show();
}

void turnOnRow(int r, uint32_t c){
//  strip.clear();
  for(int i = 0; i<12; i++){
    strip.setPixelColor(PIXEL_NUMS[r][i], strip.gamma32(c));
  }
  strip.show();
}
