#include <FirebaseESP32.h>
#include <FirebaseESP32HTTPClient.h>
#include <FirebaseJson.h>
#include <jsmn.h>
#include <WiFi.h>

FirebaseData firebaseData;

#define SSID "minions"
#define PASSWORD "hahahahahamama"

#define FIREBASE_HOST "https://not-a-smart-car-park.firebaseio.com/"
#define FIREBASE_AUTH "7YTYpvvz4S3yxcifVJgCpRTVXRZNllqYcpILq8u9"

#define InterruptPin 23

int users[4];

void time_reduce()
{
  int user, time;
  Firebase.getInt(firebaseData, "/reduce/user");
  if(firebaseData.intData == -1) {
    return;
  }
  user = firebaseData.intData();
  Firebase.getInt(firebaseData, "/reduce/hour");
  time = firebaseData.intData();

  users[user] += time;

  Firebase.setInt(firebaseData, "/reduce/user", -1);
  Firebase.setInt(firebaseData, "/reduce/hour", -1);
} 

void calculateFee(int user, double time_Out)
{
  int parking_fee = 20;
  Firebase.getDouble(firebaseData, "/" + String(user) + "Timestamp_In");
  double time_In = firebaseData.doubleData();
  double totaltime = time_Out - time_In;
  totaltime -= users[user];
  if(totaltime <0) totaltime = 0;
  double fee = totaltime*parking_fee;
  Firebase.setDouble(firebaseData, "/fee", fee);
  Firebase.setDouble(firebaseData, "/" + String(user) + "Timestamp_In", -1);
  Firebase.setDouble(firebaseData, "/" + String(user) + "Timestamp_Out", -1);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);

  pinMode(InterruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(InterruptPin), time_reduce, FALLING);

  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Try to connect Wifi");
    }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:
  Firebase.getDouble(firebaseData, "Set/Timestamp");
  double first = firebaseData.doubleData();
  Serial.print("First : ");
  printf("%.0lf\n", first);
  delay(2000);
  Firebase.getDouble(firebaseData, "Set/Timestamp");
  double second = firebaseData.doubleData();

  Serial.print("Second : ");
  Serial.println(second);

  for(int i=0 ;i<2 ;i++) {
    if(Firebase.getdouble(firebaseData, "/" + String(i) + "/Timestamp_Out") {
      calculateFee(i, firebaseData.doubleData());
    }
  }
}
