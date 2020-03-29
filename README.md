01204322 Embedded Systems

Department of Computer Engineering Faculty of Engineering Kasetsart University

Group : แก้ไขทีหลังได้

Project Name : Smart Car Park

Developer :
- Chinnawach Chaidech 6010500095
- Sakditach Supatanon 6010500125
- Arthit Photong 6010500141
- Chanawat Lohachala 6010504678

Hardware :
- 1 STM32 WROOM32 Board
- 3 ESP32 Nucleo32 Boards
- 2 OLEDs with SSD1306 Driver
- 2 KY-016 RGB LED
- 2 SG90 Servo Motors
- 1 KY-022 Infrared Receiver
- 3 Micro Switches

Software :
- Arduino IDE
- Mbed
- Thonny

Library list in STM32 :
- mbed.h [URL : https://github.com/ARMmbed/mbed-os]
- DebounceIn.h [URL : https://github.com/pilotak/DebounceIn]
- Servo.h [URL : https://pennosuke@os.mbed.com/users/simon/code/Servo/]
- ssd1306.h [URL : https://pennosuke@os.mbed.com/users/Germaint/code/ssd1306_library/]

Library list in ESP32 :
- time
- Pin
- I2C
- SSD1306_I2C
- Wire.h
- Adafruit_GFX.h [URL : https://github.com/adafruit/Adafruit-GFX-Library]
- Adafruit_SSD1306.h [URL : https://github.com/adafruit/Adafruit_SSD1306]
- FirebaseESP32.h [URL : https://github.com/mobizt/Firebase-ESP32]
- FirebaseESP32HTTPClient.h [URL : https://github.com/mobizt/Firebase-ESP32]
- FirebaseJson.h [URL : https://github.com/mobizt/Firebase-ESP32]
- jsmn.h [URL : https://github.com/zserge/jsmn]
- WiFi.h 
- Arduino.h
- IRremoteESP8266.h [URL : https://github.com/crankyoldgit/IRremoteESP8266]
- IRrecv.h
- IRutils.h

Source Code : 
- Board A : Automatic Gate.cpp
- Board B : Car Park Status.py
- Board C : IR and fee OLED.ino
- Board D : Fee Calculator.ino

Schematic Directory :
- Smart-Car-Park-schematic.png
