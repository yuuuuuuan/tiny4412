CROSS_COMPILE = arm-linux-
CC = $(CROSS_COMPILE)gcc
CC_FLAGS = -c -I ./
LD = $(CROSS_COMPILE)ld
LD_FLAGS = -T start.lds -Ttext 0x40000000
OBJCOPY = $(CROSS_COMPILE)objcopy
COPY_FLAGS = -O binary
OBJDUMP=$(CROSS_COMPILE)objdump
DUMP_FLAGS=-D
TARGET=test
OBJS=start.o led.o lib.o test.o bell.o

all: $(OBJS)
	$(LD) $(LD_FLAGS) $(OBJS) -o $(TARGET)
	$(OBJCOPY) $(COPY_FLAGS) $(TARGET) $(TARGET).bin
	$(OBJDUMP) $(DUMP_FLAGS) $(TARGET) > $(TARGET).dis
	rm -rf *.o

%.o:%.s
	$(CC) $(CC_FLAGS) $<
%.o:%.S
	$(CC) $(CC_FLAGS) $<
%.o:%.c
	$(CC) $(CC_FLAGS) $<

.PHONY:clean
clean:
	rm -rf *.o $(TARGET).bin $(TARGET).dis $(TARGET) 