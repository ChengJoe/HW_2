#include "mbed.h"
#include "uLCD_4DGL.h"
using namespace std::chrono;

uLCD_4DGL uLCD(D1, D0, D2);
// DigitalOut button_1_send(D4);
InterruptIn button_up_count(D5);
InterruptIn button_down_count(D6);
InterruptIn button_confirm(D9);

Timer debounce;
Thread thread_uLCD(osPriorityNormal);
EventQueue queue_uLCD(32 * EVENTS_EVENT_SIZE);
int test_number[3] = {500, 868, 1000};
int i = 0;
bool IsConfirm = false;

void Display_to_uLCD(){
        uLCD.text_width(4); //4X size text
        uLCD.text_height(4);
        if(!IsConfirm)
            uLCD.color(BLUE);
        else 
            uLCD.color(GREEN);
        uLCD.locate(0,2);
        uLCD.printf("%4d\n",test_number[i]);
}

void Up_count(){
    if (duration_cast<milliseconds>(debounce.elapsed_time()).count() > 600){
        if (i < 2 && !IsConfirm){
            i += 1;
            queue_uLCD.call(Display_to_uLCD);
            debounce.reset();
        }
    }
}

void Down_count(){
    if (duration_cast<milliseconds>(debounce.elapsed_time()).count() > 600){
        if (i > 0 && !IsConfirm){
            i -= 1;
            queue_uLCD.call(Display_to_uLCD);
            debounce.reset();
        }
    }
}

void Output_wave(){

}

void Confirm(){
    if (duration_cast<milliseconds>(debounce.elapsed_time()).count() > 600){
        IsConfirm = !IsConfirm;
        queue_uLCD.call(Display_to_uLCD);
        debounce.reset();
    }    
}

int main()
{
    uLCD.color(RED);
    uLCD.locate(2,2);
    uLCD.printf("Current freq. is\n");
    uLCD.text_width(4); //4X size text
    uLCD.text_height(4);
    uLCD.color(BLUE);
    uLCD.locate(0,2);
    uLCD.printf("%4d\n",test_number[i]);
    debounce.start();
    thread_uLCD.start(callback(&queue_uLCD, &EventQueue::dispatch_forever));
    button_confirm.rise(queue_uLCD.event(Confirm));
    button_up_count.rise(queue_uLCD.event(Up_count));
    button_down_count.rise(queue_uLCD.event(Down_count));
}

// #include "mbed.h"
// #include "uLCD_4DGL.h"

// //InterruptIn down(D7);
// //InterruptIn select(D8);
// InterruptIn up(D9);
// uLCD_4DGL uLCD(D1, D0, D2);
// EventQueue queue(32 * EVENTS_EVENT_SIZE);
// Thread t;

// int i;

// void add()
// {   
//     i=i+1;
//     uLCD.printf("%d",i);
// }

// int main() 
// {   
//     i=3;
//     uLCD.text_width(4); //4X size text
//     uLCD.text_height(4);
//     uLCD.color(RED);
//     uLCD.printf("%d",i);
//     t.start(callback(&queue, &EventQueue::dispatch_forever));
//     up.rise(queue.event(add));      
//     //down.rise(&minus); 
// }