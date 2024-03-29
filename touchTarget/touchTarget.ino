#include <NewPing.h>
#include <Adafruit_NeoPixel.h>

#define LEDPIN 7

// set up sensors
NewPing sensor = NewPing(2,3,39);
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

struct pixel{ int x; int y; int r; int g; int b; };


const int NUM_LINES = 79;
struct pixel ttt[NUM_LINES] = {{0, 0, 0, 255, 83},
{0, 1, 0, 255, 83},
{0, 2, 0, 255, 83},
{0, 3, 255, 255, 255},
{0, 8, 255, 255, 255},
{0, 9, 188, 5, 255},
{0, 11, 188, 5, 255},
{1, 0, 0, 255, 83},
{1, 2, 0, 255, 83},
{1, 3, 255, 255, 255},
{1, 8, 255, 255, 255},
{1, 10, 188, 5, 255},
{2, 0, 0, 255, 83},
{2, 1, 0, 255, 83},
{2, 2, 0, 255, 83},
{2, 3, 255, 255, 255},
{2, 8, 255, 255, 255},
{2, 9, 188, 5, 255},
{2, 11, 188, 5, 255},
{3, 0, 255, 255, 255},
{3, 1, 255, 255, 255},
{3, 2, 255, 255, 255},
{3, 3, 255, 255, 255},
{3, 4, 255, 255, 255},
{3, 5, 255, 255, 255},
{3, 6, 255, 255, 255},
{3, 7, 255, 255, 255},
{3, 8, 255, 255, 255},
{3, 9, 255, 255, 255},
{3, 10, 255, 255, 255},
{3, 11, 255, 255, 255},
{4, 3, 255, 255, 255},
{4, 4, 0, 255, 83},
{4, 5, 0, 255, 83},
{4, 6, 0, 255, 83},
{4, 7, 0, 255, 83},
{4, 8, 255, 255, 255},
{5, 3, 255, 255, 255},
{5, 4, 0, 255, 83},
{5, 7, 0, 255, 83},
{5, 8, 255, 255, 255},
{6, 3, 255, 255, 255},
{6, 4, 0, 255, 83},
{6, 7, 0, 255, 83},
{6, 8, 255, 255, 255},
{7, 3, 255, 255, 255},
{7, 4, 0, 255, 83},
{7, 5, 0, 255, 83},
{7, 6, 0, 255, 83},
{7, 7, 0, 255, 83},
{7, 8, 255, 255, 255},
{8, 0, 255, 255, 255},
{8, 1, 255, 255, 255},
{8, 2, 255, 255, 255},
{8, 3, 255, 255, 255},
{8, 4, 255, 255, 255},
{8, 5, 255, 255, 255},
{8, 6, 255, 255, 255},
{8, 7, 255, 255, 255},
{8, 8, 255, 255, 255},
{8, 9, 255, 255, 255},
{8, 10, 255, 255, 255},
{8, 11, 255, 255, 255},
{9, 0, 188, 5, 255},
{9, 2, 188, 5, 255},
{9, 3, 255, 255, 255},
{9, 8, 255, 255, 255},
{9, 9, 188, 5, 255},
{9, 11, 188, 5, 255},
{10, 1, 188, 5, 255},
{10, 3, 255, 255, 255},
{10, 8, 255, 255, 255},
{10, 10, 188, 5, 255},
{11, 0, 188, 5, 255},
{11, 2, 188, 5, 255},
{11, 3, 255, 255, 255},
{11, 8, 255, 255, 255},
{11, 9, 188, 5, 255},
{11, 11, 188, 5, 255},
};


const uint32_t BLUE = strip.Color(64,8,255);
const uint32_t GREEN = strip.Color(46,209,80);
const uint32_t RED = strip.Color(232,31,16);

uint32_t getRandomColor(){
  uint8_t r = rand() % 256;
  uint8_t g = rand() % 256;
  uint8_t b = rand() % 256;
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

bool found = true;
bool game = true;
int place = -99;
const int FROM_EDGE = 0;

void setup() {
  Serial.begin(9600); 
  strip.begin();
  strip.setBrightness(100);
  strip.clear();
  // put your setup code here, to run once:
  //strip.setPixelColor(PIXEL_NUMS[4][0], strip.gamma32(getRandomColor()));
  //strip.setPixelColor(PIXEL_NUMS[4][1], strip.gamma32(getRandomColor()));
  strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);
  //Serial.print("Sensor ");
  //Serial.print(1);
  //Serial.print(": ");
  int s1 = sensor.convert_cm(sensor.ping_median(5)) - FROM_EDGE;
  if(!game){
   for(int i = 0; i < NUM_LINES; i++){
     struct pixel cur = ttt[i];
     uint8_t r = cur.r;
     uint8_t g = cur.g;
     uint8_t b = cur.b;
     strip.setPixelColor(PIXEL_NUMS[cur.x][cur.y], strip.gamma32(strip.Color(r,g,b)));
    }
    strip.show();
    if(s1 > 0) game = true;
    return;
  }
  if(found){
    strip.clear();
    place = random(4, 35);
    Serial.print("New Target: ");
    Serial.println(place);
    seekToRow(int(place/3.4), BLUE); 
    found = false;
  }
  else{
    if(s1 > 0){
      Serial.println();
      Serial.print("Touch: ");
      Serial.println(s1);
      Serial.print("Difference: ");
      Serial.println(abs(s1-place));
      Serial.println();
//      Serial.print(int(s1/3.4));
//      Serial.println();
      
      if(abs(s1-place) < 4){
        lightUpBoard(GREEN);
        found = true;
        delay(2000);
        clearBoard();
      }
      else{
        lightUpBoard(RED);
        delay(1500);
        turnOnRow(int(place/3.4), BLUE);
      }
    //  Serial.print("cm");
    }
  }  
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

void lightUpBoard(uint32_t c){
  strip.clear();
  for(int i = 0; i < 12; i++){
    for(int j = 0; j < 12; j++){
      strip.setPixelColor(PIXEL_NUMS[i][j], strip.gamma32(c));
    }
  }
  strip.show();
}

void clearBoard(){
  strip.clear();
  strip.show();
}

void turnOnRow(int r, uint32_t c){
  strip.clear();
  for(int i = 0; i<12; i++){
    strip.setPixelColor(PIXEL_NUMS[r][i], strip.gamma32(c));
  }
  strip.show();
}
