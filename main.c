#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"

#define BIT_LENGTH 32
const uint LED = 25;
const uint IR = 22;

uint cont_zero = 0;
uint cont_one = 0;
int cont_decode = BIT_LENGTH - 1;
long decode = 0;
long last_result = 0;
bool flag_decode = 0;

bool read_pulse_cb(struct repeating_timer *t){
    bool IR_READ = gpio_get(IR);
    if(IR_READ){
        if(!flag_decode && cont_zero > 15 && cont_decode == BIT_LENGTH - 1) flag_decode = 1;
        cont_zero = 0;
        if(cont_one <= 21) cont_one++;
    }else{
        if(flag_decode){
            if(cont_one == 1){
                cont_decode--;
                printf("0");
            }else if(cont_one >= 2 && cont_decode != BIT_LENGTH - 1){
                if(decode == 0) cont_decode = 23;
                if(cont_decode < 24) decode += pow(2, cont_decode);
                printf("1");
                cont_decode--;
            }
            //printf("%d\n", cont_decode);
        }
        cont_zero++;
        cont_one = 0;
    }
    if(cont_decode < 0 || cont_one > 20 || cont_zero > 20){
        flag_decode = 0;
        cont_decode = BIT_LENGTH - 1;
        if(decode != 0){
            printf(" %X\n", decode);
        }
        last_result = decode;
        decode = 0;
        cont_zero = cont_one = 0;
    }
}

int main(){
    stdio_init_all();
    gpio_init(LED);
    gpio_init(IR);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_set_dir(IR, GPIO_IN);
    gpio_put(LED, 1);
    struct repeating_timer read_timer;
    add_repeating_timer_us(-526, read_pulse_cb, NULL, &read_timer);
    while(true);
}