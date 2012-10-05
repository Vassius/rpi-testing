#define GPIO_CTRL_ADDR 0x20200000
#define PIN16_ENBL 1<<18
#define PIN16_OFF 1<<16

int kmain(void) {
    volatile unsigned int *gpio_ctrl = (volatile unsigned int*)(GPIO_CTRL_ADDR + 4);
    *gpio_ctrl = PIN16_ENBL;
    gpio_ctrl = (volatile unsigned int*)(GPIO_CTRL_ADDR + 40);
    *gpio_ctrl = PIN16_OFF;    
    return 0;
}

