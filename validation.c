/* validation.c - Реализация функций проверки корректности вводимых данных */

#include <stdio.h>   /* Для printf, scanf, fgets */
#include <string.h>  /* Для strlen, strchr */
#include <stdlib.h>  /* Для atoi, atof */
#include <ctype.h>   /* Для isdigit, isspace */
#include "validation.h" /* Подключаем заголовочный файл */
#include "structures.h"  /* Подключаем определения структур (для MAX_STR_LEN, MAX_DATE_LEN) */

/* Проверка, является ли строка целым числом */
int isInteger(const char *str)
{
    int i = 0; /* Индекс символа */

    if (str == NULL || str[0] == '\0') /* Проверяем на пустоту */
    {
        return 0; /* Пустая строка - не число */
    }

    if (str[0] == '-' || str[0] == '+') /* Допускаем знак в начале */
    {
        i = 1; /* Начинаем проверку со второго символа */
    }

    if (str[i] == '\0') /* Если после знака ничего нет */
    {
        return 0; /* Не число */
    }

    for (; str[i] != '\0'; i++) /* Перебираем все символы */
    {
        if (!isdigit((unsigned char)str[i])) /* Если символ не цифра */
        {
            return 0; /* Не целое число */
        }
    }
    return 1; /* Строка является целым числом */
}

/* Проверка, является ли строка вещественным числом */
int isDouble(const char *str)
{
    int i = 0;          /* Индекс символа */
    int dot_count = 0;  /* Счетчик точек */

    if (str == NULL || str[0] == '\0') /* Проверяем на пустоту */
    {
        return 0; /* Пустая строка - не число */
    }

    if (str[0] == '-' || str[0] == '+') /* Допускаем знак в начале */
    {
        i = 1; /* Начинаем проверку со второго символа */
    }

    if (str[i] == '\0') /* Если после знака ничего нет */
    {
        return 0; /* Не число */
    }

    for (; str[i] != '\0'; i++) /* Перебираем все символы */
    {
        if (str[i] == '.') /* Если символ - точка */
        {
            dot_count++; /* Увеличиваем счетчик точек */
            if (dot_count > 1) /* Если больше одной точки */
            {
                return 0; /* Не число */
            }
        }
        else if (!isdigit((unsigned char)str[i])) /* Если символ не цифра и не точка */
        {
            return 0; /* Не вещественное число */
        }
    }
    return 1; /* Строка является вещественным числом */
}

/* Проверка корректности формата даты (ДД.ММ.ГГГГ) */
int isDateValid(const char *date_str)
{
    int day, month, year; /* День, месяц, год */

    if (date_str == NULL || strlen(date_str) != 10) /* Проверяем длину строки */
    {
        return 0; /* Неверный формат */
    }

    if (date_str[2] != '.' || date_str[5] != '.') /* Проверяем разделители */
    {
        return 0; /* Неверный формат */
    }

    /* Проверяем, что остальные символы - цифры */
    if (!isdigit((unsigned char)date_str[0]) || !isdigit((unsigned char)date_str[1]) ||
        !isdigit((unsigned char)date_str[3]) || !isdigit((unsigned char)date_str[4]) ||
        !isdigit((unsigned char)date_str[6]) || !isdigit((unsigned char)date_str[7]) ||
        !isdigit((unsigned char)date_str[8]) || !isdigit((unsigned char)date_str[9]))
    {
        return 0; /* Неверный формат */
    }

    /* Извлекаем день, месяц, год */
    day = (date_str[0] - '0') * 10 + (date_str[1] - '0');     /* Вычисляем день */
    month = (date_str[3] - '0') * 10 + (date_str[4] - '0');   /* Вычисляем месяц */
    year = (date_str[6] - '0') * 1000 + (date_str[7] - '0') * 100 +
           (date_str[8] - '0') * 10 + (date_str[9] - '0');    /* Вычисляем год */

    if (month < 1 || month > 12) /* Проверяем диапазон месяца */
    {
        return 0; /* Неверный месяц */
    }

    if (day < 1 || day > 31) /* Проверяем диапазон дня */
    {
        return 0; /* Неверный день */
    }

    if (year < 1900 || year > 2100) /* Проверяем диапазон года */
    {
        return 0; /* Неверный год */
    }

    return 1; /* Дата корректна */
}

/* Ввод целого числа с проверкой */
int inputInt(const char *prompt)
{
    char buffer[MAX_STR_LEN]; /* Буфер для ввода */
    int result;               /* Результат */

    while (1) /* Бесконечный цикл до корректного ввода */
    {
        printf("%s", prompt);          /* Выводим подсказку */
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) /* Читаем строку */
        {
            printf("Ошибка ввода!\n"); /* Сообщение об ошибке */
            continue;                  /* Повторяем ввод */
        }
        buffer[strcspn(buffer, "\n")] = '\0'; /* Удаляем символ новой строки */

        if (isInteger(buffer)) /* Проверяем, является ли ввод числом */
        {
            result = atoi(buffer); /* Преобразуем строку в число */
            return result;         /* Возвращаем результат */
        }
        printf("Некорректный ввод! Введите целое число.\n"); /* Сообщение об ошибке */
    }
}

/* Ввод вещественного числа с проверкой */
double inputDouble(const char *prompt)
{
    char buffer[MAX_STR_LEN]; /* Буфер для ввода */
    double result;            /* Результат */

    while (1) /* Бесконечный цикл до корректного ввода */
    {
        printf("%s", prompt);          /* Выводим подсказку */
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) /* Читаем строку */
        {
            printf("Ошибка ввода!\n"); /* Сообщение об ошибке */
            continue;                  /* Повторяем ввод */
        }
        buffer[strcspn(buffer, "\n")] = '\0'; /* Удаляем символ новой строки */

        if (isDouble(buffer)) /* Проверяем, является ли ввод числом */
        {
            result = atof(buffer); /* Преобразуем строку в число */
            return result;         /* Возвращаем результат */
        }
        printf("Некорректный ввод! Введите число.\n"); /* Сообщение об ошибке */
    }
}

/* Ввод положительного целого числа с проверкой */
int inputPositiveInt(const char *prompt)
{
    int result; /* Результат */

    while (1) /* Бесконечный цикл до корректного ввода */
    {
        result = inputInt(prompt); /* Вводим целое число */
        if (result > 0)            /* Проверяем положительность */
        {
            return result;         /* Возвращаем результат */
        }
        printf("Число должно быть положительным!\n"); /* Сообщение об ошибке */
    }
}

/* Ввод положительного вещественного числа с проверкой */
double inputPositiveDouble(const char *prompt)
{
    double result; /* Результат */

    while (1) /* Бесконечный цикл до корректного ввода */
    {
        result = inputDouble(prompt); /* Вводим вещественное число */
        if (result > 0.0)             /* Проверяем положительность */
        {
            return result;            /* Возвращаем результат */
        }
        printf("Число должно быть положительным!\n"); /* Сообщение об ошибке */
    }
}

/* Ввод строки */
void inputString(const char *prompt, char *buffer, int max_len)
{
    while (1) /* Бесконечный цикл до корректного ввода */
    {
        printf("%s", prompt);          /* Выводим подсказку */
        if (fgets(buffer, max_len, stdin) == NULL) /* Читаем строку */
        {
            printf("Ошибка ввода!\n"); /* Сообщение об ошибке */
            continue;                  /* Повторяем ввод */
        }
        buffer[strcspn(buffer, "\n")] = '\0'; /* Удаляем символ новой строки */

        if (strlen(buffer) > 0) /* Проверяем, что строка не пустая */
        {
            return; /* Выходим из функции */
        }
        printf("Строка не может быть пустой!\n"); /* Сообщение об ошибке */
    }
}

/* Ввод даты с проверкой формата */
void inputDate(const char *prompt, char *buffer)
{
    while (1) /* Бесконечный цикл до корректного ввода */
    {
        printf("%s", prompt);          /* Выводим подсказку */
        if (fgets(buffer, MAX_DATE_LEN + 1, stdin) == NULL) /* Читаем строку */
        {
            printf("Ошибка ввода!\n"); /* Сообщение об ошибке */
            /* Очищаем буфер ввода */
            while (getchar() != '\n'); /* Считываем до конца строки */
            continue;                  /* Повторяем ввод */
        }
        buffer[strcspn(buffer, "\n")] = '\0'; /* Удаляем символ новой строки */

        /* Если строка заняла весь буфер, очищаем остаток */
        if (strlen(buffer) >= (size_t)(MAX_DATE_LEN)) /* Проверяем переполнение */
        {
            int c; /* Символ для очистки буфера */
            while ((c = getchar()) != '\n' && c != EOF); /* Очищаем буфер */
        }

        if (isDateValid(buffer)) /* Проверяем корректность даты */
        {
            return; /* Выходим из функции */
        }
        printf("Некорректный формат даты! Используйте формат ДД.ММ.ГГГГ\n"); /* Сообщение об ошибке */
    }
}

/* Ввод пункта меню с проверкой диапазона */
int inputMenuChoice(int min_val, int max_val)
{
    int choice; /* Выбранный пункт */

    while (1) /* Бесконечный цикл до корректного ввода */
    {
        choice = inputInt("Ваш выбор: "); /* Вводим номер пункта */
        if (choice >= min_val && choice <= max_val) /* Проверяем диапазон */
        {
            return choice; /* Возвращаем выбор */
        }
        printf("Выберите пункт от %d до %d!\n", min_val, max_val); /* Сообщение об ошибке */
    }
}


