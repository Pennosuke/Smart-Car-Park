//Hardware : STM32 Nucleo32
//Platform : Mbed
//Language : C
//Note : 1. If there are any errors happened to i2c between Board A and Board B, just boot the file from Mbed to board A and rerun code from board B again.
//       2. Now still use button(sw3) instead of IR.(while final product needs to uses IR)
//       3. Still didnt write code for servo2 since the limited of button.
#include "mbed.h"
#include "DebounceIn.h"
#include "Servo.h"
#include "ssd1306.h"

Servo servo1(D6);
Servo servo2(D9);

DebounceIn sw1(D3, PullUp);
I2CSlave slave(D4,D5);
DigitalOut led3(PB_3);
EventQueue queue;
Thread thr_queue;
Timeout flipper;
volatile int temp;

void sw1_closed_differ(void) {
    printf("Door Closed\n");
}

void flip(void) {
    servo1 = 0;
    queue.call(sw1_closed_differ);
}

void sw1_closed(void) {
    flipper.attach(&flip, 1);
}

void sw1_opened_defer(void) {
    printf("Door Opened\n");
    flipper.detach();
}

void sw1_opened(void) {
    if(temp != 0)
    {
        servo1 = 180;
        queue.call(sw1_opened_defer);
    }
}

int main(void) {
    servo1 = 0;
    char buf[20];
    printf("STM32 started...\n");
    slave.address(0xA0); // actual address = 0x50 (last bit ignored)
    thr_queue.start(callback(&queue,&EventQueue::dispatch_forever));
    while(1)
    {
        int i = slave.receive();
        for(int i = 0; i < sizeof(buf); i++) buf[i] = 0; // Clear buffer
        switch (i) {
            case I2CSlave::ReadAddressed:
                break;
            case I2CSlave::WriteAddressed:
                slave.read(buf,1);
                printf("Read: %s\n", buf);
                temp = buf[0];
                break;
        }
        //temp = 1;
        sw1.rise(sw1_closed);
        sw1.fall(sw1_opened);
    }
}
