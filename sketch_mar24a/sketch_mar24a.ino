#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <FirebaseESP32.h>
#include <FirebaseESP32HTTPClient.h>
#include <FirebaseJson.h>
#include <jsmn.h>

#include <WiFi.h>

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SSID "minions"
#define PASSWORD "hahahahahamama"

#define FIREBASE_HOST "https://not-a-smart-car-park.firebaseio.com/"
#define FIREBASE_AUTH "7YTYpvvz4S3yxcifVJgCpRTVXRZNllqYcpILq8u9"

#define Ago 23
#define Ago2 22
#define Ain 39

FirebaseData firebaseData;

const uint16_t kRecvPin = 36;
IRrecv irrecv(kRecvPin);
decode_results results;

unsigned long long int IRread;
bool users[4];
bool isAvail = false;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void UserMapping()      //Edit HEX by IR code you pre-read
{                       //This function is to map IR read from receiver into User ID
  if(IRread == 0x86C6807F) {
    UserStateChange(0);
  }
  else if(IRread == 0x4567) {
    UserStateChange(1);
  }
  else if(IRread == 0x1357) {
    UserStateChange(2);
  }

  IRread = 0;           //Clear IRread to prevent infinite function calling
}

void Arespond()         //Interrupt from A
{
  isAvail = true;
  stopAskAvail();       //Got available and stop
}

void askAvail()         //Interrupt to A for available parking lot
{
  digitalWrite(Ago, HIGH);
}

void stopAskAvail()     //Stop Interrupt to A
{
  digitalWrite(Ago, LOW);
}

void userIn(int user, int state)      //state is status of parking lot || 0 means full || 1 means available
{
  if(state == 0) {
    //show not available
    Serial.println("Lot full naja TwT");
  }
  else {
    //send time in and user ID to Database
    Serial.println("Get in loei jaaa");
    Firebase.setTimestamp(firebaseData, "/" +String(user) +"/Timestamp_In");
  }
}

void askOpenExit(int user)
{
  //send time out and user ID to Database
  Firebase.setTimestamp(firebaseData, "/" +String(user) +"/Timestamp_Out");
  while(Firebase.getInt(firebaseData, "/fee") == -1) {
    ;
  }
  int fee = firebaseData.intData();
  Firebase.setInt(firebaseData, "/fee", -1);
  //show parking fee to OLED
  while(1) {  //wait for user to pay
    break;
  }
  digitalWrite(Ago2, HIGH);
}

void UserStateChange(int user)
{
  if(users[user] == 0) {          //users[user] is to check if this user ID coming or going || 0 means coming
    askAvail();                   //Ask if it is available lot
    unsigned long now = millis();
    while(millis()-now<=100 && isAvail==false) {      //Wait for answer for 3 sec
      ;
    }
    if(isAvail == false) {        //Stop asking since timed out
      stopAskAvail();
    }

    if(isAvail) {                 //If is it available lot
      isAvail = false;
      userIn(user, 1);
      users[user] = 1;
    }
    else {
      userIn(user, 0);
    }
  }
  else {                          //User going out
    askOpenExit(user);
    users[user] = 0;
  }
}

void showText(char str[], int horz, int vert)
{
  display.clearDisplay();
  display.setCursor(horz,vert);     
  display.println(str);
  display.display(); 
}

void setup() {

  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);

  pinMode(Ago, OUTPUT);
  pinMode(Ago2, OUTPUT);
  pinMode(Ain, INPUT);
  attachInterrupt(digitalPinToInterrupt(Ain), Arespond, RISING);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  irrecv.enableIRIn();

  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Try to connect Wifi");
    }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  if (irrecv.decode(&results)) {
    IRread = results.value;
    irrecv.resume();
  }
  UserMapping();    //Since IRread is unsigned long, Mapping should help us handle this easier
  delay(100);
}
