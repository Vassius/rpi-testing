#define GPIO_CTRL_ADDR 0x20200000
#define PIN_ENBL_OUTPUT 1<<18
#define PIN_ENBL_INPUT 0

#define TIMER_COUNTER 0x20003004

volatile unsigned int *gpfsel1 = (volatile unsigned int*)(GPIO_CTRL_ADDR + 0x4);
volatile unsigned int *gpset0 = (volatile unsigned int*)(GPIO_CTRL_ADDR + 0x1C);
volatile unsigned int *gpclr0 = (volatile unsigned int*)(GPIO_CTRL_ADDR + 0x28);
volatile unsigned int *gplev0 = (volatile unsigned int*)(GPIO_CTRL_ADDR + 0x34);

void toggle_led() {
    unsigned int on;
    on = *gplev0 & 1<<16;
    if (on) {
        *gpclr0 = 1<<16;
    }
    else {
        *gpset0 = 1<<16;
    }
}

int kmain(void) {
    volatile unsigned int *counter = (volatile unsigned int*)(TIMER_COUNTER);
    volatile unsigned int value = *counter;
    //int status = 0;
    *gpfsel1 = PIN_ENBL_OUTPUT;
    while (1) {
        if (*counter - value >= 1000000) {
            value = *counter;
            toggle_led();
            //status ^= 1;
        }
    }

    return 0;
}

