// testshapes demo for RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x64 RGB LED matrix.

// WILL NOT FIT on ARDUINO UNO -- requires a Mega, M0 or M4 board
#include <RGBmatrixPanel.h>
//#include "image.h"

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

//#define CLK  8   // USE THIS ON ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false,128);
//char example[2][10] = {"bla","bloo"};
//int ex[] = {255,255,255,255,255,0,0,0,255};

bool serial_toggle = false;
String inputString;
int inputArray[2];
int x_iter = 0;
int y_iter = 0;
int inc = 0;
int pixel_inc = 0;
int pixel_buffer[150];
int packet_size = 7;

//static getValue(int index){
//  int val =  pgm_read_word_near(img + index);
//  return val;
//}

//void renderTest(){
//  int inc = 0;
//  for(int i=0;i<32;i++){
//    int j;
//    for(j=0;j<128;j++){
//      int index = inc;
//      int r = getValue(index);
//      int g = getValue(index+1);
//      int b = getValue(index+2);
//      
//      matrix.drawPixel(j,i,matrix.Color888(r,g,b,true));
//      inc+=3;
//    }
//    j=0;
//  }
//}
//void renderTest2(){
//  for(int i=0;i<4096;i++){
//    int index = inc;
//    String r = String(getValue(index));
//    String g = String(getValue(index+1));
//    String b = String(getValue(index+2));
//    String mysting = String(r + "," + g + "," + b);
//    //drawPixel(mysting);
//    inc+=3;
//  }
//}

void serialTest(){
  //int inc = 0;
  for(int i=0;i<20;i++){
    delay(100);
//    Serial.print("255,0,0");
//    Serial.print('\n');
  }
}

void setup() {
  Serial.begin(9600);
  //delay(1000);
  matrix.begin();    
  //Serial.print(ex[0]);                             
  //renderTest();
  //delay(2000);
  //Serial.print("255,0,0");
  //delay(1000);
  //serialTest();
  //makeArray(ex); 
  //delay(1000);
  //renderTest2();
  //Serial.print("init");
  
}

void serialEvent() {
  //drawPixel("255,0,0"); 
  while (Serial.available()) {
    // get the new byte:
    //drawPixel("255,0,0"); 
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    
    //Serial.send(inChar + "|");
    //Serial.print("event");
    //Serial.print(inChar + "?");
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      serial_toggle = true;
    }
    //Serial.print(inputString);
  }
}
void coordIterate(){
  if(x_iter==127){
    x_iter=0;
    y_iter++;
  }else{
    x_iter++;
  }
  if(y_iter>=31 && x_iter>=127){
    y_iter=0;
    x_iter=0;
  }
    
}

//static drawPixel(String str){
//  char new_str[12];
//  str.toCharArray(new_str, 12);
//  char * pch;
//  int arr[3];
//  int iter = 0;
//  pch = strtok (new_str,",");
//  //arr[0] = pch;
//  while (pch != NULL)
//  {
//    int strInt = atoi(pch);
//    arr[iter] = strInt;
//    pch = strtok (NULL, ",");
//    iter++;
//  }
//  Serial.print(x_iter);
//   Serial.print("|");
//   Serial.print(y_iter);
//   Serial.print("\n");
//  matrix.drawPixel(x_iter,y_iter,matrix.Color888(arr[0],arr[1],arr[2],true));
//  coordIterate();
//}
//static drawPixel(){
//  
//}

void addPixelsToBuffer(String str){
  char new_str[66];
  str.toCharArray(new_str, 66);
  char * pch;
  //int arr[100];
  int iter = 0;
  pch = strtok (new_str,",");
  //arr[0] = pch;
  while (pch != NULL)
  {
    int strInt = atoi(pch);
    pixel_buffer[iter] = strInt;
    pch = strtok (NULL, ",");
    iter++;
  }
  //Serial.print(pixel_buffer[5]);
}

void drawPixels(){
  int local_inc = 0;
  for(int i=0;i<packet_size;i++){
    //Serial.print(local_inc);
    //Serial.print("\n");
    int index = local_inc;
    int r = pixel_buffer[index];
    int g = pixel_buffer[index+1];
    int b = pixel_buffer[index+2];
    //String mysting = String(r + "," + g + "," + b);
    matrix.drawPixel(x_iter,y_iter,matrix.Color888(r,g,b,true));
    coordIterate();
    local_inc+=3;
  }
  memset(pixel_buffer, 0, sizeof(pixel_buffer));
}

void loop() {
  if (serial_toggle) {
    //Serial.print(inputString);
    addPixelsToBuffer(inputString);
    delay(10);
    drawPixels();
    //drawPixel(inputString);
    //matrix.drawPixel(j,i,matrix.Color888(inputString,true));
    // clear the string:
    inputString = "";
    serial_toggle = false;
  }
  // put your main code here, to run repeatedly:

}
