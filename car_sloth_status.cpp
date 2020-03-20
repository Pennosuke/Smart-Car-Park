#include "mbed.h"
 
DigitalOut myled(A3);
DigitalOut green(A0);
DigitalOut red2(A6);
DigitalOut green2(A5);
DigitalIn pb(D3);
DigitalIn st2(D10);

int main() {
    pb.mode(PullUp);
    st2.mode(PullUp);
    while(1) {
        myled = !pb;
        green = pb;
        red2 = !st2;
        green2 =st2;
    }
}
