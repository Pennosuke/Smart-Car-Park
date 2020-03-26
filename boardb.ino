#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIDTH 128
#define HEIGHT 64
#define p1 23
#define p2 32
#define green1 15
#define red1 2
#define red2 13
#define green2 12
Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, -1);
void showText(char str[], int horz, int vert)
{
  display.clearDisplay();
  display.clearDisplay();
  display.setCursor(horz,vert);     
  display.println(str);
  display.display(); 
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
      Serial.println(F("SSD1306 allocation failed"));
      for(;;);
  }
  pinMode(p1,INPUT_PULLUP);
  pinMode(p2,INPUT_PULLUP);
  pinMode(green1,OUTPUT);
  pinMode(red1,OUTPUT);
  pinMode(green2,OUTPUT);
  pinMode(red2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int p1_val = digitalRead(p1);
  int p2_val = digitalRead(p2);
  int tot = p1_val+p2_val;
  digitalWrite(red1,!p1_val);
  digitalWrite(green1,p1_val);
  digitalWrite(red2,!p2_val);
  digitalWrite(green2,p2_val);
  if(p1_val+p2_val > 0){
    showText(""+(String)tot+" park(s) left",8,24)
  }
  else{
    showText("FULL",8,24);
  }
  Wire.beginTransmission(0x50);
  Wire.write(p1_val+p2_val);
  Wire.endTransmission();
  delay(100);
}
