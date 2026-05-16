/* structures.h - Определение структур данных для учета бракованных деталей */
#pragma once /* Защита от повторного включения */

#ifndef STRUCTURES_H /* Защита от повторного включения (альтернативный способ) */
#define STRUCTURES_H /* Определяем макрос */

/* Максимальная длина строковых полей */
#define MAX_STR_LEN 100
/* Максимальная длина даты */
#define MAX_DATE_LEN 11

/* Структура "Деталь" - хранит информацию о детали */
typedef struct {
    int code;                       /* Код детали (уникальный идентификатор) */
    char name[MAX_STR_LEN];         /* Название детали */
    char material[MAX_STR_LEN];     /* Материал детали */
    double weight;                  /* Вес детали (кг) */
    double price;                   /* Цена детали (руб.) */
    char release_date[MAX_DATE_LEN];/* Дата выпуска (ДД.ММ.ГГГГ) */
} Detail;

/* Структура "Брак" - хранит информацию о виде брака */
typedef struct {
    int code;                       /* Код брака (уникальный идентификатор) */
    char property[MAX_STR_LEN];     /* Свойство брака */
    char type[MAX_STR_LEN];         /* Вид брака */
    double correction_price;        /* Цена корректировки (руб.) */
} Defect;

/* Структура "Учет" - связывает деталь и брак */
typedef struct {
    int detail_code;                /* Код детали (ссылка на деталь) */
    int defect_code;                /* Код брака (ссылка на брак) */
    char defect_date[MAX_DATE_LEN]; /* Дата образования брака (ДД.ММ.ГГГГ) */
    int quantity;                   /* Количество бракованных деталей */
} Record;

/* Структура "Учетная запись" - хранит данные пользователя системы */
typedef struct {
    char login[MAX_STR_LEN];        /* Логин пользователя */
    char password[MAX_STR_LEN];     /* Пароль пользователя */
    int role;                       /* Роль: 1 - администратор, 0 - пользователь */
} Account;

/* ============================================================ */
/* Динамические массивы (векторы) в стиле C                     */
/* ============================================================ */

/* Вектор деталей */
typedef struct {
    Detail *data;   /* Указатель на массив деталей */
    int size;       /* Текущее количество элементов */
    int capacity;   /* Выделенная емкость */
} DetailVector;

/* Вектор браков */
typedef struct {
    Defect *data;   /* Указатель на массив браков */
    int size;       /* Текущее количество элементов */
    int capacity;   /* Выделенная емкость */
} DefectVector;

/* Вектор записей учета */
typedef struct {
    Record *data;   /* Указатель на массив записей учета */
    int size;       /* Текущее количество элементов */
    int capacity;   /* Выделенная емкость */
} RecordVector;

/* Вектор учетных записей */
typedef struct {
    Account *data;  /* Указатель на массив учетных записей */
    int size;       /* Текущее количество элементов */
    int capacity;   /* Выделенная емкость */
} AccountVector;

#endif /* STRUCTURES_H */
