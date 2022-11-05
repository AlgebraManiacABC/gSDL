NAME=gSDL

LIB_DIR=lib
INC_DIR=include
SRC_DIR=src
OBJ_DIR=build
TEST_DIR=tests

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

.PHONY: install clean test

install: $(INCS) $(LIB)
	sudo cp $(INC_DIR)/* /usr/local/include/ 
	sudo cp $(LIB) /usr/local/lib/lib$(NAME).a

test: $(TEST_DIR)/init.c
	gcc -o $(TEST_DIR)/$@ $^ -Wall -Werror -I$(INC_DIR) -lSDL2main -lSDL2 -lgSDL -lSDL2_image -lSDL2_ttf

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(LIB_DIR)