/* vector_ops.c - Реализация операций с динамическими массивами (векторами) */

#include <stdlib.h>  /* Для malloc, realloc, free */
#include <string.h>  /* Для memcpy */
#include <stdio.h>   /* Для printf */
#include "vector_ops.h"  /* Подключаем заголовочный файл */
#include "constants.h"   /* Подключаем константы */

/* ============================================================ */
/* Функции для вектора учетных записей                          */
/* ============================================================ */

/* Инициализация вектора учетных записей */
void initAccountVector(AccountVector *vec)
{
    vec->size = 0;                                            /* Начальный размер - 0 */
    vec->capacity = INITIAL_CAPACITY;                         /* Начальная емкость */
    vec->data = (Account *)malloc(sizeof(Account) * vec->capacity); /* Выделяем память */
    if (vec->data == NULL)                                    /* Проверяем успешность выделения */
    {
        printf("Ошибка выделения памяти!\n");                 /* Сообщение об ошибке */
        exit(1);                                              /* Завершаем программу с ошибкой */
    }
}

/* Добавление учетной записи в вектор */
void pushAccount(AccountVector *vec, Account item)
{
    if (vec->size >= vec->capacity)                           /* Если массив заполнен */
    {
        vec->capacity *= 2;                                   /* Удваиваем емкость */
        vec->data = (Account *)realloc(vec->data, sizeof(Account) * vec->capacity); /* Перевыделяем память */
        if (vec->data == NULL)                                /* Проверяем успешность */
        {
            printf("Ошибка перевыделения памяти!\n");         /* Сообщение об ошибке */
            exit(1);                                          /* Завершаем программу */
        }
    }
    vec->data[vec->size] = item;                              /* Записываем элемент */
    vec->size++;                                              /* Увеличиваем размер */
}

/* Удаление учетной записи по индексу */
void removeAccount(AccountVector *vec, int index)
{
    int i; /* Переменная цикла */
    if (index < 0 || index >= vec->size)                      /* Проверяем корректность индекса */
    {
        printf("Некорректный индекс для удаления!\n");        /* Сообщение об ошибке */
        return;                                               /* Выходим из функции */
    }
    for (i = index; i < vec->size - 1; i++)                   /* Сдвигаем элементы влево */
    {
        vec->data[i] = vec->data[i + 1];                      /* Копируем следующий элемент */
    }
    vec->size--;                                              /* Уменьшаем размер */
}

/* Освобождение памяти вектора учетных записей */
void freeAccountVector(AccountVector *vec)
{
    free(vec->data);                                          /* Освобождаем память */
    vec->data = NULL;                                         /* Обнуляем указатель */
    vec->size = 0;                                            /* Сбрасываем размер */
    vec->capacity = 0;                                        /* Сбрасываем емкость */
}

/* ============================================================ */
/* Функции для вектора деталей                                  */
/* ============================================================ */

/* Инициализация вектора деталей */
void initDetailVector(DetailVector *vec)
{
    vec->size = 0;                                            /* Начальный размер - 0 */
    vec->capacity = INITIAL_CAPACITY;                         /* Начальная емкость */
    vec->data = (Detail *)malloc(sizeof(Detail) * vec->capacity); /* Выделяем память */
    if (vec->data == NULL)                                    /* Проверяем успешность */
    {
        printf("Ошибка выделения памяти!\n");                 /* Сообщение об ошибке */
        exit(1);                                              /* Завершаем программу */
    }
}

/* Добавление детали в вектор */
void pushDetail(DetailVector *vec, Detail item)
{
    if (vec->size >= vec->capacity)                           /* Если массив заполнен */
    {
        vec->capacity *= 2;                                   /* Удваиваем емкость */
        vec->data = (Detail *)realloc(vec->data, sizeof(Detail) * vec->capacity); /* Перевыделяем */
        if (vec->data == NULL)                                /* Проверяем успешность */
        {
            printf("Ошибка перевыделения памяти!\n");         /* Сообщение об ошибке */
            exit(1);                                          /* Завершаем программу */
        }
    }
    vec->data[vec->size] = item;                              /* Записываем элемент */
    vec->size++;                                              /* Увеличиваем размер */
}

/* Удаление детали по индексу */
void removeDetail(DetailVector *vec, int index)
{
    int i; /* Переменная цикла */
    if (index < 0 || index >= vec->size)                      /* Проверяем корректность индекса */
    {
        printf("Некорректный индекс для удаления!\n");        /* Сообщение об ошибке */
        return;                                               /* Выходим из функции */
    }
    for (i = index; i < vec->size - 1; i++)                   /* Сдвигаем элементы влево */
    {
        vec->data[i] = vec->data[i + 1];                      /* Копируем следующий элемент */
    }
    vec->size--;                                              /* Уменьшаем размер */
}

/* Освобождение памяти вектора деталей */
void freeDetailVector(DetailVector *vec)
{
    free(vec->data);                                          /* Освобождаем память */
    vec->data = NULL;                                         /* Обнуляем указатель */
    vec->size = 0;                                            /* Сбрасываем размер */
    vec->capacity = 0;                                        /* Сбрасываем емкость */
}

/* ============================================================ */
/* Функции для вектора браков                                   */
/* ============================================================ */

/* Инициализация вектора браков */
void initDefectVector(DefectVector *vec)
{
    vec->size = 0;                                            /* Начальный размер - 0 */
    vec->capacity = INITIAL_CAPACITY;                         /* Начальная емкость */
    vec->data = (Defect *)malloc(sizeof(Defect) * vec->capacity); /* Выделяем память */
    if (vec->data == NULL)                                    /* Проверяем успешность */
    {
        printf("Ошибка выделения памяти!\n");                 /* Сообщение об ошибке */
        exit(1);                                              /* Завершаем программу */
    }
}

/* Добавление брака в вектор */
void pushDefect(DefectVector *vec, Defect item)
{
    if (vec->size >= vec->capacity)                           /* Если массив заполнен */
    {
        vec->capacity *= 2;                                   /* Удваиваем емкость */
        vec->data = (Defect *)realloc(vec->data, sizeof(Defect) * vec->capacity); /* Перевыделяем */
        if (vec->data == NULL)                                /* Проверяем успешность */
        {
            printf("Ошибка перевыделения памяти!\n");         /* Сообщение об ошибке */
            exit(1);                                          /* Завершаем программу */
        }
    }
    vec->data[vec->size] = item;                              /* Записываем элемент */
    vec->size++;                                              /* Увеличиваем размер */
}

/* Удаление брака по индексу */
void removeDefect(DefectVector *vec, int index)
{
    int i; /* Переменная цикла */
    if (index < 0 || index >= vec->size)                      /* Проверяем корректность индекса */
    {
        printf("Некорректный индекс для удаления!\n");        /* Сообщение об ошибке */
        return;                                               /* Выходим из функции */
    }
    for (i = index; i < vec->size - 1; i++)                   /* Сдвигаем элементы влево */
    {
        vec->data[i] = vec->data[i + 1];                      /* Копируем следующий элемент */
    }
    vec->size--;                                              /* Уменьшаем размер */
}

/* Освобождение памяти вектора браков */
void freeDefectVector(DefectVector *vec)
{
    free(vec->data);                                          /* Освобождаем память */
    vec->data = NULL;                                         /* Обнуляем указатель */
    vec->size = 0;                                            /* Сбрасываем размер */
    vec->capacity = 0;                                        /* Сбрасываем емкость */
}

/* ============================================================ */
/* Функции для вектора учета                                    */
/* ============================================================ */

/* Инициализация вектора учета */
void initRecordVector(RecordVector *vec)
{
    vec->size = 0;                                            /* Начальный размер - 0 */
    vec->capacity = INITIAL_CAPACITY;                         /* Начальная емкость */
    vec->data = (Record *)malloc(sizeof(Record) * vec->capacity); /* Выделяем память */
    if (vec->data == NULL)                                    /* Проверяем успешность */
    {
        printf("Ошибка выделения памяти!\n");                 /* Сообщение об ошибке */
        exit(1);                                              /* Завершаем программу */
    }
}

/* Добавление записи учета в вектор */
void pushRecord(RecordVector *vec, Record item)
{
    if (vec->size >= vec->capacity)                           /* Если массив заполнен */
    {
        vec->capacity *= 2;                                   /* Удваиваем емкость */
        vec->data = (Record *)realloc(vec->data, sizeof(Record) * vec->capacity); /* Перевыделяем */
        if (vec->data == NULL)                                /* Проверяем успешность */
        {
            printf("Ошибка перевыделения памяти!\n");         /* Сообщение об ошибке */
            exit(1);                                          /* Завершаем программу */
        }
    }
    vec->data[vec->size] = item;                              /* Записываем элемент */
    vec->size++;                                              /* Увеличиваем размер */
}

/* Удаление записи учета по индексу */
void removeRecord(RecordVector *vec, int index)
{
    int i; /* Переменная цикла */
    if (index < 0 || index >= vec->size)                      /* Проверяем корректность индекса */
    {
        printf("Некорректный индекс для удаления!\n");        /* Сообщение об ошибке */
        return;                                               /* Выходим из функции */
    }
    for (i = index; i < vec->size - 1; i++)                   /* Сдвигаем элементы влево */
    {
        vec->data[i] = vec->data[i + 1];                      /* Копируем следующий элемент */
    }
    vec->size--;                                              /* Уменьшаем размер */
}

/* Освобождение памяти вектора учета */
void freeRecordVector(RecordVector *vec)
{
    free(vec->data);                                          /* Освобождаем память */
    vec->data = NULL;                                         /* Обнуляем указатель */
    vec->size = 0;                                            /* Сбрасываем размер */
    vec->capacity = 0;                                        /* Сбрасываем емкость */
}
