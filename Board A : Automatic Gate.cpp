#include "mbed.h"
#include "DebounceIn.h"
#include "Servo.h"
 
Servo servo1(D6);
//Servo servo2(D9);

DigitalOut led3(PB_3);
DebounceIn sw1(D3, PullUp);
EventQueue queue;
Thread thr_queue;
Timeout flipper;

void sw1_released_differ(void) {
    printf("Door Closed\n");
}

void flip(void) {
    servo1 = 0;
    queue.call(sw1_released_differ);
}

void sw1_released(void) {
    flipper.attach(&flip, 1);
}

void sw1_pressed_defer(void) {
    printf("Door Opened\n");
    flipper.detach();
}

void sw1_pressed(void) {
    servo1 = 180;
    queue.call(sw1_pressed_defer);
}

int main(void) {
    printf("App started...\n");
    servo1 = 0;
    thr_queue.start(
    callback(&queue,&EventQueue::dispatch_forever));
    while(1)
    {
        sw1.rise(sw1_released);
        sw1.fall(sw1_pressed);
    }
}
