#include "mbed.h"
#include "uLCD_4DGL.h"
using namespace std::chrono;

uLCD_4DGL uLCD(D1, D0, D2); // UART4 tx, UART4 rx, reset pin;
DigitalOut button_1_send(D4);
// DigitalIn button_1_receive(D5);
InterruptIn button_1_receive(D5);
DigitalOut myled(LED1);

Timer t;
Thread thread_1;

int test_number = 0;

EventQueue queue(32 * EVENTS_EVENT_SIZE);

void Display_to_uLCD(){
    uLCD.cls();
    uLCD.locate(2,2);
    uLCD.printf("Current number is %d",test_number);
    ThisThread::sleep_for(2s);
}

void toggle(){
    if(duration_cast<milliseconds>(t.elapsed_time()).count()> 500){
        myled = !myled;
        test_number++;
        t.reset();
        queue.call(Display_to_uLCD);
    }        
}

int main()
{
    thread_1.start(callback(&queue, &EventQueue::dispatch_forever));
    t.start();
    button_1_send = 1;
    button_1_receive.rise(&toggle);
    myled = 1;
    while (1) { 
        printf("test_number is %d\n",test_number);
        ThisThread::sleep_for(1s);
    }
    // uLCD.printf("\nByebye uLCD World\n"); //Default Green on black text
}
