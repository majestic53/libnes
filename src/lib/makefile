# libnes
# Copyright (C) 2015 David Jolly
# ----------------------
#
# libnes is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libnes is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC=clang++
CC_FLAGS=-march=native -pthread -std=gnu++11 -O3 -Wall -Werror
DIR_BIN=./../../bin/
DIR_BUILD=./../../build/
DIR_INC=./include/
DIR_SRC=./src/
LIB=libnes.a

all: build archive

archive:
	@echo ''
	@echo '--- BUILDING LIBRARY -----------------------'
	ar rcs $(DIR_BUILD)$(LIB) $(DIR_BUILD)nes.o $(DIR_BUILD)nes_exception.o $(DIR_BUILD)nes_memory.o
	@echo '--- DONE -----------------------------------'
	@echo ''

build: nes.o nes_exception.o nes_memory.o

nes.o: $(DIR_SRC)nes.cpp $(DIR_INC)nes.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes.cpp -o $(DIR_BUILD)nes.o

nes_exception.o: $(DIR_SRC)nes_exception.cpp $(DIR_INC)nes_exception.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes_exception.cpp -o $(DIR_BUILD)nes_exception.o

# COMPONENTS

nes_memory.o: $(DIR_SRC)nes_memory.cpp $(DIR_INC)nes_memory.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes_memory.cpp -o $(DIR_BUILD)nes_memory.o
