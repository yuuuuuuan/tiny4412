led.bin: start.o 
	arm-none-linux-gnueabi-ld -Ttext 0x0 -o led.elf $^
	arm-none-linux-gnueabi-objcopy -O binary led.elf u-boot.bin
	arm-none-linux-gnueabi-objdump -D led.elf > led_elf.dis	
	
%.o : %.S
	arm-none-linux-gnueabi-gcc -o $@ $< -c

%.o : %.c
	arm-none-linux-gnueabi-gcc -o $@ $< -c 

clean:
	rm *.o *.elf *.bin *.dis  -f
