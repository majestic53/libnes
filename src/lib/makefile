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
	ar rcs $(DIR_BUILD)$(LIB) $(DIR_BUILD)libnes.o $(DIR_BUILD)nes.o $(DIR_BUILD)nes_cpu.o $(DIR_BUILD)nes_exception.o $(DIR_BUILD)nes_memory.o $(DIR_BUILD)nes_ppu.o $(DIR_BUILD)nes_rom.o $(DIR_BUILD)nes_test.o $(DIR_BUILD)nes_test_cpu.o $(DIR_BUILD)nes_test_memory.o $(DIR_BUILD)nes_test_ppu.o $(DIR_BUILD)nes_test_rom.o
	@echo '--- DONE -----------------------------------'
	@echo ''

build: libnes.o nes.o nes_cpu.o nes_exception.o nes_memory.o nes_ppu.o nes_rom.o nes_test.o nes_test_cpu.o nes_test_memory.o nes_test_ppu.o nes_test_rom.o

libnes.o: $(DIR_SRC)libnes.cpp $(DIR_INC)libnes.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)libnes.cpp -o $(DIR_BUILD)libnes.o

nes.o: $(DIR_SRC)nes.cpp $(DIR_INC)nes.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes.cpp -o $(DIR_BUILD)nes.o

nes_exception.o: $(DIR_SRC)nes_exception.cpp $(DIR_INC)nes_exception.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes_exception.cpp -o $(DIR_BUILD)nes_exception.o

# COMPONENTS

nes_cpu.o: $(DIR_SRC)nes_cpu.cpp $(DIR_INC)nes_cpu.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes_cpu.cpp -o $(DIR_BUILD)nes_cpu.o

nes_memory.o: $(DIR_SRC)nes_memory.cpp $(DIR_INC)nes_memory.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes_memory.cpp -o $(DIR_BUILD)nes_memory.o

nes_ppu.o: $(DIR_SRC)nes_ppu.cpp $(DIR_INC)nes_ppu.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes_ppu.cpp -o $(DIR_BUILD)nes_ppu.o

nes_rom.o: $(DIR_SRC)nes_rom.cpp $(DIR_INC)nes_rom.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes_rom.cpp -o $(DIR_BUILD)nes_rom.o

# TEST

nes_test.o: $(DIR_SRC)nes_test.cpp $(DIR_INC)nes_test.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes_test.cpp -o $(DIR_BUILD)nes_test.o

nes_test_cpu.o: $(DIR_SRC)nes_test_cpu.cpp $(DIR_INC)nes_test_cpu.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes_test_cpu.cpp -o $(DIR_BUILD)nes_test_cpu.o

nes_test_memory.o: $(DIR_SRC)nes_test_memory.cpp $(DIR_INC)nes_test_memory.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes_test_memory.cpp -o $(DIR_BUILD)nes_test_memory.o

nes_test_ppu.o: $(DIR_SRC)nes_test_ppu.cpp $(DIR_INC)nes_test_ppu.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes_test_ppu.cpp -o $(DIR_BUILD)nes_test_ppu.o

nes_test_rom.o: $(DIR_SRC)nes_test_rom.cpp $(DIR_INC)nes_test_rom.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)nes_test_rom.cpp -o $(DIR_BUILD)nes_test_rom.o
