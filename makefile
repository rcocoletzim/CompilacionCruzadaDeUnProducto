TARGET = app
LIB_NAME = share_BBB

CC = gcc
CROSS_TOOLCHAIN =

VPATH = cat
INCLUDE = -I cat
CFLAGS = -g3 -c -O0 -Wall $(INCLUDE)

DEP_LIB_SH = cat.c
OBJ = main.o 

all:$(TARGET)

$(TARGET): $(LIB_NAME) $(OBJ)
	$(CROSS_TOOLCHAIN)$(CC) $(OBJ) lib$(LIB_NAME).so -o $@

%.o : %.c
	$(CROSS_TOOLCHAIN)$(CC) $(CFLAGS) -o $@ $<

$(LIB_NAME):$(DEP_LIB_SH)
	$(CROSS_TOOLCHAIN)$(CC) -shared -fPIC -o lib$(LIB_NAME).so $<

.PHONY: all clean install 

install:
	

clean:
	rm -rf *.o *.so $(TARGET)

