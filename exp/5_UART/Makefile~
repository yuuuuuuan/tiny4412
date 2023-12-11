uart.bin: uart.o 
	arm-linux-ld -Ttext 0x50000000 -v -o uart.elf $^
	arm-linux-objcopy -O binary uart.elf uart.bin
	arm-linux-objdump -D uart.elf > uart_elf.dis
%.o : %.c
	arm-linux-gcc -v -o $@ $< -c
clean:
	rm *.o *.elf *.bin *.dis  -f
