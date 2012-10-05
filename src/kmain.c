#define GPIO_CTRL_ADDR 0x20200000
#define PIN16_ENBL 1<<18
#define PIN16_OFF 1<<16

#define TIMER_COUNTER 0x20003004

volatile unsigned int *gpio_ctrl = (volatile unsigned int*)(GPIO_CTRL_ADDR + 4);

void toggle_led(int on) {
    if (on) {
        gpio_ctrl = (volatile unsigned int*)(GPIO_CTRL_ADDR + 28);
    }
    else {
        gpio_ctrl = (volatile unsigned int*)(GPIO_CTRL_ADDR + 40);
    }
    *gpio_ctrl ^= PIN16_OFF;    
}

int kmain(void) {
    volatile unsigned int *counter = (volatile unsigned int*)(TIMER_COUNTER);
    volatile unsigned int value = *counter;
    int status = 0;
    *gpio_ctrl = PIN16_ENBL;
    while (1) {
        if (*counter - value >= 1000000) {
            value = *counter;
            toggle_led(status);
            status ^= 1;
        }
    }

    return 0;
}

