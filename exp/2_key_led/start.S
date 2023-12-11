.globl _start

_start:
	// 设置GPM4CON的bit[0:3]，配置GPM4_0/1/2/3引脚为输出功能
	ldr r1, =0x110002E0 					
	ldr r0, =0x00001111
	str r0, [r1]
	// 设置GPX3CON的bit[2:5]，配置GPX3_2/3/4/5引脚为输入功能
	ldr r1, =0x11000C60 					
	ldr r0, =0x0
	str r0, [r1]
	
Key_led:
	// 设置GPM4DAT的bit[0:3]，使GPM4_0/1/2/3引脚输出低电平，LED亮
	ldr r1, =0x11000C64		// GPX3DAT地址
	ldr r2, =0x110002E4	    // GPM4DAT地址	
	ldr r3, =0xFFFFFFC2	    
	ldr r0, [r1]
	orr r0, r0, r3
	mov r0, r0, ROR #2
	str r0, [r2]

	// 延时
	bl Key_led							





