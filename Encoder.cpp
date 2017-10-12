#include "mbed.h"

DigitalIn input(PTE2);
DigitalOut led(LED1);
Serial ser(USBTX, USBRX);

Timer t,t_in;

int main() {
    t.start();
    t_in.start();
    ser.baud(9600);
    int counter = 0;
    float rad = 2.5 * 2 * 3.141;
    float s = rad/20;
    while(1) {
        led = input;

        if (!input.read()){ //////////  อ่านค่าจากpinและนำจำนวนครั้ง
            t_in.reset();
            counter += 1;
            while (!input.read()){
                if (t_in.read_ms() >= 1000){
                    counter = 0;
                    led = !led;
                    break;
                }
            }
        }

        if (t.read_ms() >= 1000){ /////////// จับเวลา ทุกๆ 1 วินาที
            counter = 0;
            led = !led;
            t.reset();
        }

    }
}
