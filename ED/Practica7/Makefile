HEADERS = avl.h avl.hxx bintree.h bintree.hxx
FLAGS = -std=c++0x -Wall
CC = g++

MAIN = principal.cpp
MAIN_TEST = prueba.cpp

BIN_DIR = ./bin
BIN_NAME = ed_avl
BIN_TEST = test

USE = "Compilar y ejecutar: \n\tmake all && ./bin/ed_avl"
USE_TEST = "Compilar y ejecutar un archivo main de prueba ( prueba.cpp ): \n\tmake test && ./bin/test"
USE_CLEAN = "Limpiar los archivos: \n\tmake clean"

usage:
	@echo
	@echo $(USE_TEST)
	@echo $(USE_CLEAN)


test: $(BIN_DIR)/test

$(BIN_DIR)/ed_avl: $(MAIN) $(HEADERS)
	@if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR);	fi
	$(CC) -o $(BIN_DIR)/$(BIN_NAME) $< $(FLAGS)

$(BIN_DIR)/test: $(MAIN_TEST) $(HEADERS)
	@if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR);	fi
	$(CC) -o $(BIN_DIR)/$(BIN_TEST) $< $(FLAGS)

clean:
	rm $(BIN_DIR)/*
	rmdir $(BIN_DIR)
