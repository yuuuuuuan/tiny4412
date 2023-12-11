adc.bin: adc.o 
	arm-linux-ld -Ttext 0x50000000 -v -o adc.elf $^
	arm-linux-objcopy -O binary adc.elf adc.bin
	arm-linux-objdump -D adc.elf > adc_elf.dis
%.o : %.c
	arm-linux-gcc -v -o $@ $< -c
clean:
	rm *.o *.elf *.bin *.dis  -f
