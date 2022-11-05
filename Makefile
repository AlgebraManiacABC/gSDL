NAME=gSDL

LIB_DIR=lib
INC_DIR=include
SRC_DIR=src
OBJ_DIR=build

INCS=$(wildcard $(INC_DIR)/*.h)
SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(notdir $(SRCS:.c=.o))
OBJS:=$(addprefix $(OBJ_DIR)/,$(OBJS))
LIB=$(LIB_DIR)/$(NAME).a


all: $(LIB)

$(LIB): $(OBJS) | $(LIB_DIR)
	ar rcs $(LIB) $(OBJS)

$(LIB_DIR):
	mkdir $(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	gcc -c -o $@ $< -I"$(INC_DIR)"

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

.PHONY: install clean

install: $(INCS) $(LIB)
	sudo cp $(INC_DIR)/* /usr/local/include/ 
	sudo cp $(LIB) /usr/local/lib/lib$(NAME).a

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(LIB_DIR)