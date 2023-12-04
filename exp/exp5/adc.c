#include "adc.h"

//ADC初始化
void adc_init(void)
{
    ADC_CFG &= ~(0x1 << 16);

    //ADC输入通道选择  AIN0
    //ADCMUX &= ~0xf;

    // 100M/(19 + 1)
    ADCCON &= ~(0xff << 6);
    ADCCON = ADCCON | (19 << 6) | (1 << 14) | (1 << 16);

    //正常模式
    ADCCON &= ~(1 << 2);

}

//启动ADC转化
void adc_start(void)
{
    ADCCON |= 0x1;

}

//获取结束标志
int adc_end(void)
{

    return (ADCCON >> 15) & 0x1;
}

//获取ADC转化的值
U32 adc_get(void)
{
    return ADCDAT & 0xfff;
}