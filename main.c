#include <stdio.h>
#include "pico/stdlib.h"

const uint LED = 25;
const uint IR = 22;

int cont = 0;

bool read_pulse_cb(struct repeating_timer *t){
    bool IR_READ = gpio_get(IR);
    if(IR_READ)
        cont = 0;
    else
        cont++;
    if(cont > 0)
        printf("%d\n", cont);
    return true;
}

int main(){
    stdio_init_all();
    gpio_init(LED);
    gpio_init(IR);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_set_dir(IR, GPIO_IN);
    gpio_put(LED, 1);
    struct repeating_timer read_timer;
    add_repeating_timer_us(-562, read_pulse_cb, NULL, &read_timer);
    while(true);
}