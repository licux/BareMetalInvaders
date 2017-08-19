CROSS= arm-none-eabi-

CC= $(CROSS)gcc
LD= $(CROSS)ld
OBJCOPY= $(CROSS)objcopy

# libgcc.a
LIBS = -L/home/user/MyBakingPi/gcc-arm-none-eabi/lib/gcc/arm-none-eabi/6.3.1
# newlib
LIBS += -L/home/user/MyBakingPi/gcc-arm-none-eabi/arm-none-eabi/lib

STARTUP= startup.o
OBJS= main.o

# RaspberryPi library
OBJS+= rpi_lib/rpi_init.o rpi_lib/bss/clearbss.o
OBJS+= rpi_lib/gpio.o
OBJS+= rpi_lib/mailbox.o rpi_lib/framebuffer.o rpi_lib/drawing.o
OBJS+= rpi_lib/i2c.o
OBJS+= rpi_lib/systemtimer.o
OBJS+= rpi_lib/uart.o
OBJS+= rpi_lib/image.o
OBJS+= rpi_lib/dma.o

OBJS+= syscalls.o
OBJS+= alien.o
OBJS+= alienbullet.o
OBJS+= ufo.o
OBJS+= bunker.o
OBJS+= cannon.o
OBJS+= bullet.o
OBJS+= status.o
OBJS+= title.o
OBJS+= game.o

CFLAGS = -mfloat-abi=soft -mlittle-endian
#CFLAGS+= -nostdinc -fno-builtin
CFLAGS+= -O2

########################
all:	kernel.img

kernel.elf:	$(STARTUP) $(OBJS)
	$(LD) -static -T kernel.lds $^ `$(CC) -print-libgcc-file-name` -o $@ $(LIBS) -lc -lgcc -lc

.SUFFIXES: .elf .img

.elf.img:
	$(OBJCOPY) -O binary $< $@
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
.S.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean::
	$(RM) -f *.o *.img *.elf */*.o */*/*.o 
	$(RM) -f tags *~

tags::
	ctags *.[chS]
