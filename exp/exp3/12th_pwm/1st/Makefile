default:
	arm-linux-gcc -c test.c  -o test.o
	arm-linux-ld  -Ttext=0x70003000  test.o  -o test
	arm-linux-objcopy  -O binary  test  test.bin
clean:
	rm -f test.o  test  test.bin   *~ 
