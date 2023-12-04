#include <string.h>
#include <adc.h>

    

void (*udelay)(unsigned int) = (void*)0x43e26480;
int (*print)(const char *format, ...) = (void*)0x43e11a2c;

int main(void)
{
    //ADC初始化
    adc_init();

    print("main start\n");

    adc_start(); 

    while(1)
    {

        if (adc_end())
        {
            print("val = %d\n", adc_get());
        
            adc_start();    
        }
        
        delay(200000);
        
    }

    print("main end\n");

    return 0;
}