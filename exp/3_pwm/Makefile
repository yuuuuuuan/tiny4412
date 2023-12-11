pwm.bin: pwm.o 
	arm-linux-ld -Ttext 0x50000000 -v -o pwm.elf $^
	arm-linux-objcopy -O binary pwm.elf pwm.bin
	arm-linux-objdump -D pwm.elf > pwm_elf.dis
%.o : %.c
	arm-linux-gcc -v -o $@ $< -c
clean:
	rm *.o *.elf *.bin *.dis  -f
