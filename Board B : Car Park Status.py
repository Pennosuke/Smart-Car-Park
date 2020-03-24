#Hardware : ESP32 WROOM32
#Platform : Thonny
#Language : Python
#Note : If there are any errors happened to i2c between Board A and Board B, just boot the file from Mbed to board A and rerun code from board B again.
import time
from machine import Pin, I2C
from ssd1306 import SSD1306_I2C

i2c = I2C(scl=Pin(22),sda=Pin(21),freq=100000)
button1 = Pin(23, Pin.IN, Pin.PULL_UP)
button2 = Pin(32, Pin.IN, Pin.PULL_UP)
red1 = Pin(2, Pin.OUT)
green1 = Pin(15, Pin.OUT)
red2 = Pin(13, Pin.OUT)
green2 = Pin(12, Pin.OUT)
oled = SSD1306_I2C(128,64,i2c)

print("Scanning I2C bus... found",i2c.scan())
time.sleep(0.5)
print("Send data to STM32...")
while True:
    #print(button1.value())
    #print(button2.value())
    red1.value(not button1.value())
    green1.value(button1.value())
    red2.value(not button2.value())
    green2.value(button2.value())
    oled.fill(0)
    oled.text("Car Park Status",0,0)
    oled.text(": ",0,24)
    total = button1.value() + button2.value()
    if button1.value() + button2.value() > 0:
        oled.text(str(total) + " park(s) left",8,24)
    else:
        oled.text("FULL",8,24)
    oled.show()
    i2c.writeto(0x50,bytearray([total]))
    time.sleep(0.1)
