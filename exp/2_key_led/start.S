.globl _start

_start:
	// ����GPM4CON��bit[0:3]������GPM4_0/1/2/3����Ϊ�������
	ldr r1, =0x110002E0 					
	ldr r0, =0x00001111
	str r0, [r1]
	// ����GPX3CON��bit[2:5]������GPX3_2/3/4/5����Ϊ���빦��
	ldr r1, =0x11000C60 					
	ldr r0, =0x0
	str r0, [r1]
	
Key_led:
	// ����GPM4DAT��bit[0:3]��ʹGPM4_0/1/2/3��������͵�ƽ��LED��
	ldr r1, =0x11000C64		// GPX3DAT��ַ
	ldr r2, =0x110002E4	    // GPM4DAT��ַ	
	ldr r3, =0xFFFFFFC2	    
	ldr r0, [r1]
	orr r0, r0, r3
	mov r0, r0, ROR #2
	str r0, [r2]

	// ��ʱ
	bl Key_led							




