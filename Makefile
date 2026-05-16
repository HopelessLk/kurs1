# Makefile - Файл сборки проекта учета бракованных деталей
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
TARGET = defect_tracker
SOURCES = main.c vector_ops.c file_ops.c validation.c auth.c data_ops.c menu.c
HEADERS = structures.h constants.h vector_ops.h file_ops.h validation.h auth.h data_ops.h menu.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) *.txt

.PHONY: all clean
