/* validation.h - Функции проверки корректности вводимых данных */
#pragma once /* Защита от повторного включения */

#ifndef VALIDATION_H /* Защита от повторного включения */
#define VALIDATION_H /* Определяем макрос */

/* Проверка, является ли строка целым числом */
int isInteger(const char *str);

/* Проверка, является ли строка вещественным числом */
int isDouble(const char *str);

/* Проверка корректности формата даты (ДД.ММ.ГГГГ) */
int isDateValid(const char *date_str);

/* Ввод целого числа с проверкой */
int inputInt(const char *prompt);

/* Ввод вещественного числа с проверкой */
double inputDouble(const char *prompt);

/* Ввод положительного целого числа с проверкой */
int inputPositiveInt(const char *prompt);

/* Ввод положительного вещественного числа с проверкой */
double inputPositiveDouble(const char *prompt);

/* Ввод строки (без пробелов в начале/конце) */
void inputString(const char *prompt, char *buffer, int max_len);

/* Ввод даты с проверкой формата */
void inputDate(const char *prompt, char *buffer);

/* Ввод пункта меню с проверкой диапазона */
int inputMenuChoice(int min_val, int max_val);

#endif /* VALIDATION_H */
