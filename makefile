TARGET = app
LIB_NAME = share_BBB

CC = gcc
CROSS_TOOLCHAIN =

VPATH = cat touch rm
INCLUDE = -I cat -I touch -I rm
CFLAGS = -g3 -c -O0 -Wall $(INCLUDE)

DEP_LIB_SH = cat.c touch.c rm.c argument_processing.c
OBJ = main.o 
MK_DIR = build

all:$(MK_DIR) $(TARGET)

$(TARGET): $(LIB_NAME) $(OBJ)
	$(CROSS_TOOLCHAIN)$(CC) $(OBJ) lib$(LIB_NAME).so -o $@
	@mv *.so *.o $(TARGET) $(MK_DIR)/

%.o : %.c
	$(CROSS_TOOLCHAIN)$(CC) $(CFLAGS) -o $@ $<

$(LIB_NAME):$(DEP_LIB_SH)
	$(CROSS_TOOLCHAIN)$(CC) -shared -fPIC -o lib$(LIB_NAME).so $^

$(MK_DIR):
	@mkdir -p $(MK_DIR)

.PHONY: all clean install 

install:
ifneq (,$(wildcard $(MK_DIR)/$(TARGET)))
	@echo "Target exist"
	@read -p "IP address and place: " address; \
	scp $(MK_DIR)/$(TARGET) $(MK_DIR)/lib$(LIB_NAME).so debian@$$address
else
	@echo "You must to generate the binary before"
endif

clean:
	@rm -rf $(MK_DIR)

