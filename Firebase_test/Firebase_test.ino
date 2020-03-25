#include <FirebaseESP32.h>
#include <FirebaseESP32HTTPClient.h>
#include <FirebaseJson.h>
#include <jsmn.h>

#include <WiFi.h>

FirebaseData firebaseData;

const char* ssid     = "minions";
const char* password = "hahahahahamama";

#define FIREBASE_HOST "https://not-a-smart-car-park.firebaseio.com/"
#define FIREBASE_KEY "7YTYpvvz4S3yxcifVJgCpRTVXRZNllqYcpILq8u9"

void setup()
{
    Serial.begin(115200);
    
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
}

void loop()
{  
  Firebase.getInt(firebaseData, "/val1");
  int value = firebaseData.intData();
  Serial.print("Read : ");
  Serial.println(value);
  delay(2000);
  
  Firebase.setTimestamp(firebaseData, "/Set/Timestamp");
  Firebase.setInt(firebaseData, "/val3", 123);
}
