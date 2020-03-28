#include "mbed.h"
#include "DebounceIn.h"
#include "Servo.h"
#include "ssd1306.h"

Servo servo1(D6);
Servo servo2(D9);
DigitalOut led3(PB_3);
DigitalIn InDectected(A7);
DigitalIn OutDectected(A6);
DigitalOut CarParkStatus(A5);
DigitalIn park1(A2);
DigitalIn park2(A1);
EventQueue queue;
Thread thr_queue;
Timeout flipper;
volatile int temp;

void sw2_closed_differ(void) {
    printf("Door2 Closed\n");
}

void sw2_closed(void) {
    servo2 = 0;
    queue.call(sw2_closed_differ);
}

void sw2_opened_defer(void) {
    printf("Door2 Opened\n");
}

void sw2_opened(void) {
    servo2 = 180;
    queue.call(sw2_opened_defer);
}

void sw1_closed_differ(void) {
    printf("Door Closed\n");
}

void sw1_closed(void) {
    servo1 = 0;
    queue.call(sw1_closed_differ);
}

void sw1_opened_defer(void) {
    printf("Door Opened\n");
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
    servo2 = 0;
    temp = 1;
    char buf[20];
    printf("STM32 started...\n");
    slave.address(0xA0); // actual address = 0x50 (last bit ignored)
    thr_queue.start(callback(&queue,&EventQueue::dispatch_forever));
    while(1)
    {
        if(InDectected == 0)
        {
            queue.call(sw1_closed);
        }
        else
        {
            queue.call(sw1_opened);
        }
        if(OutDectected == 0)
        {
            queue.call(sw2_closed);
        }
        else
        {
            queue.call(sw2_opened);
        }
        temp = park1 + park2;
        if(temp > 0)
        {
            CarParkStatus = 1;
        }
        else
        {
            CarParkStatus = 0;
        }
    }
}
