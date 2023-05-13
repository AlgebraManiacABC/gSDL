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

ifeq ($(OS),Windows_NT)
	I_SDL=C:/SDL2_all/include/
	L_SDL=C:/SDL2_all/lib/
	CFLAGS:=-I$(I_SDL) -L$(L_SDL) -lgSDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
	RM=del /f /q /a
	EXT=exe
else
	CFLAGS:=-lgSDL $(shell sdl2-config --cflags --libs) -lSDL_image -lSDL2_ttf
	RM=rm -rf
	EXT=out
endif

all: $(LIB)

$(LIB): $(OBJS) | $(LIB_DIR)
	ar rcs $(LIB) $(OBJS)

$(LIB_DIR):
	mkdir $(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	gcc -c -o $@ $< -I"$(INC_DIR)" $(CFLAGS)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

.PHONY: install clean test run

install: $(INCS) $(LIB)
ifeq ($(OS),Windows_NT)
	$(foreach file, $(subst /,\,$(wildcard $(INC_DIR)/*)), copy $(file) C:\SDL2_all\include\$(notdir $(file)))
	copy $(subst /,\,$(LIB)) C:\SDL2_all\lib\lib$(NAME).a
else
	sudo cp $(INC_DIR)/* /usr/local/include/ 
	sudo cp $(LIB) /usr/local/lib/lib$(NAME).a
endif

test: $(TEST_DIR)/init.c install
	gcc -o $(TEST_DIR)/$@.$(EXT) $< -Wall -Werror -I"$(INC_DIR)" $(CFLAGS)

run: test
	./$(TEST_DIR)/$^.$(EXT)

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(LIB_DIR)