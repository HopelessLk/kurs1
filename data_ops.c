/* data_ops.c - Реализация операций с данными: детали, браки, учет */

#include <stdio.h>   /* Для printf, scanf */
#include <string.h>  /* Для strcmp, strcpy, strstr */
#include <stdlib.h>  /* Для общих функций */
#include "data_ops.h"    /* Подключаем заголовочный файл */
#include "validation.h"  /* Подключаем функции валидации */
#include "file_ops.h"    /* Подключаем файловые операции */
#include "vector_ops.h"  /* Подключаем операции с векторами */

/* ============================================================ */
/* Вспомогательные функции                                      */
/* ============================================================ */

/* Проверка существования кода детали */
int isDetailCodeExists(DetailVector *details, int code)
{
    int i; /* Переменная цикла */
    for (i = 0; i < details->size; i++) /* Перебираем все детали */
    {
        if (details->data[i].code == code) /* Если код совпадает */
        {
            return 1; /* Код существует */
        }
    }
    return 0; /* Код не найден */
}

/* Проверка существования кода брака */
int isDefectCodeExists(DefectVector *defects, int code)
{
    int i; /* Переменная цикла */
    for (i = 0; i < defects->size; i++) /* Перебираем все браки */
    {
        if (defects->data[i].code == code) /* Если код совпадает */
        {
            return 1; /* Код существует */
        }
    }
    return 0; /* Код не найден */
}

/* Получение названия детали по коду */
const char* getDetailNameByCode(DetailVector *details, int code)
{
    int i; /* Переменная цикла */
    for (i = 0; i < details->size; i++) /* Перебираем все детали */
    {
        if (details->data[i].code == code) /* Если код совпадает */
        {
            return details->data[i].name; /* Возвращаем название */
        }
    }
    return "Неизвестно"; /* Деталь не найдена */
}

/* Получение вида брака по коду */
const char* getDefectTypeByCode(DefectVector *defects, int code)
{
    int i; /* Переменная цикла */
    for (i = 0; i < defects->size; i++) /* Перебираем все браки */
    {
        if (defects->data[i].code == code) /* Если код совпадает */
        {
            return defects->data[i].type; /* Возвращаем вид брака */
        }
    }
    return "Неизвестно"; /* Брак не найден */
}

/* Сравнение двух дат в формате ДД.ММ.ГГГГ; возвращает <0, 0, >0 */
static int compareDates(const char *d1, const char *d2)
{
    int day1, mon1, year1; /* Компоненты первой даты */
    int day2, mon2, year2; /* Компоненты второй даты */

    /* Разбираем первую дату */
    day1 = (d1[0] - '0') * 10 + (d1[1] - '0');   /* День */
    mon1 = (d1[3] - '0') * 10 + (d1[4] - '0');   /* Месяц */
    year1 = (d1[6] - '0') * 1000 + (d1[7] - '0') * 100 +
            (d1[8] - '0') * 10 + (d1[9] - '0');  /* Год */

    /* Разбираем вторую дату */
    day2 = (d2[0] - '0') * 10 + (d2[1] - '0');   /* День */
    mon2 = (d2[3] - '0') * 10 + (d2[4] - '0');   /* Месяц */
    year2 = (d2[6] - '0') * 1000 + (d2[7] - '0') * 100 +
            (d2[8] - '0') * 10 + (d2[9] - '0');  /* Год */

    if (year1 != year2) return year1 - year2;     /* Сравниваем по году */
    if (mon1 != mon2) return mon1 - mon2;         /* Сравниваем по месяцу */
    return day1 - day2;                           /* Сравниваем по дню */
}

/* ============================================================ */
/* Работа с деталями                                            */
/* ============================================================ */

/* Просмотр всех деталей */
void showAllDetails(DetailVector *details)
{
    int i; /* Переменная цикла */

    if (details->size == 0) /* Проверяем наличие данных */
    {
        printf("Список деталей пуст.\n"); /* Сообщение */
        return; /* Выходим */
    }

    printf("\n%-5s %-6s %-20s %-15s %-10s %-10s %-12s\n",
           "№", "Код", "Название", "Материал", "Вес", "Цена", "ДатаВыпуска"); /* Заголовок */
    printf("--------------------------------------------------------------------------------\n"); /* Разделитель */

    for (i = 0; i < details->size; i++) /* Перебираем все детали */
    {
        printf("%-5d %-6d %-20s %-15s %-10.2f %-10.2f %-12s\n",
               i + 1,                            /* Номер */
               details->data[i].code,             /* Код */
               details->data[i].name,             /* Название */
               details->data[i].material,         /* Материал */
               details->data[i].weight,           /* Вес */
               details->data[i].price,            /* Цена */
               details->data[i].release_date);    /* Дата выпуска */
    }
    printf("\n"); /* Пустая строка */
}

/* Добавление новой детали */
void addDetail(DetailVector *details)
{
    Detail new_detail; /* Новая деталь */

    printf("\n=== ДОБАВЛЕНИЕ ДЕТАЛИ ===\n"); /* Заголовок */

    new_detail.code = inputPositiveInt("Введите код детали: "); /* Вводим код */

    /* Проверяем уникальность кода */
    if (isDetailCodeExists(details, new_detail.code)) /* Если код уже есть */
    {
        printf("Деталь с таким кодом уже существует!\n"); /* Сообщение об ошибке */
        return; /* Выходим */
    }

    inputString("Введите название: ", new_detail.name, MAX_STR_LEN);           /* Название */
    inputString("Введите материал: ", new_detail.material, MAX_STR_LEN);       /* Материал */
    new_detail.weight = inputPositiveDouble("Введите вес (кг): ");             /* Вес */
    new_detail.price = inputPositiveDouble("Введите цену (руб.): ");           /* Цена */
    inputDate("Введите дату выпуска (ДД.ММ.ГГГГ): ", new_detail.release_date);/* Дата */

    pushDetail(details, new_detail); /* Добавляем в вектор */
    saveDetails(details);            /* Сохраняем в файл */
    printf("Деталь успешно добавлена!\n"); /* Подтверждение */
}

/* Редактирование детали */
void editDetail(DetailVector *details)
{
    int num;   /* Номер записи */
    int index; /* Индекс */

    printf("\n=== РЕДАКТИРОВАНИЕ ДЕТАЛИ ===\n"); /* Заголовок */
    showAllDetails(details); /* Показываем все детали */

    if (details->size == 0) return; /* Если нет данных, выходим */

    num = inputInt("Введите номер записи для редактирования: "); /* Вводим номер */
    index = num - 1; /* Преобразуем в индекс */

    if (index < 0 || index >= details->size) /* Проверяем диапазон */
    {
        printf("Некорректный номер записи!\n"); /* Ошибка */
        return; /* Выходим */
    }

    printf("Текущее название: %s\n", details->data[index].name); /* Показываем текущее */
    inputString("Введите новое название: ", details->data[index].name, MAX_STR_LEN); /* Новое */

    printf("Текущий материал: %s\n", details->data[index].material); /* Показываем */
    inputString("Введите новый материал: ", details->data[index].material, MAX_STR_LEN); /* Новый */

    printf("Текущий вес: %.2f\n", details->data[index].weight); /* Показываем */
    details->data[index].weight = inputPositiveDouble("Введите новый вес (кг): "); /* Новый */

    printf("Текущая цена: %.2f\n", details->data[index].price); /* Показываем */
    details->data[index].price = inputPositiveDouble("Введите новую цену (руб.): "); /* Новая */

    printf("Текущая дата выпуска: %s\n", details->data[index].release_date); /* Показываем */
    inputDate("Введите новую дату выпуска (ДД.ММ.ГГГГ): ", details->data[index].release_date); /* Новая */

    saveDetails(details); /* Сохраняем в файл */
    printf("Деталь успешно отредактирована!\n"); /* Подтверждение */
}

/* Удаление детали */
void deleteDetail(DetailVector *details, RecordVector *records)
{
    int num;   /* Номер записи */
    int index; /* Индекс */
    int i;     /* Переменная цикла */
    char confirm[MAX_STR_LEN]; /* Подтверждение */

    printf("\n=== УДАЛЕНИЕ ДЕТАЛИ ===\n"); /* Заголовок */
    showAllDetails(details); /* Показываем все детали */

    if (details->size == 0) return; /* Если нет данных, выходим */

    num = inputInt("Введите номер записи для удаления: "); /* Вводим номер */
    index = num - 1; /* Преобразуем в индекс */

    if (index < 0 || index >= details->size) /* Проверяем диапазон */
    {
        printf("Некорректный номер записи!\n"); /* Ошибка */
        return; /* Выходим */
    }

    /* Проверяем, используется ли деталь в записях учета */
    for (i = 0; i < records->size; i++) /* Перебираем записи учета */
    {
        if (records->data[i].detail_code == details->data[index].code) /* Если связана */
        {
            printf("Нельзя удалить деталь, которая используется в записях учета!\n"); /* Ошибка */
            return; /* Выходим */
        }
    }

    inputString("Вы действительно хотите удалить запись? (да/нет): ", confirm, MAX_STR_LEN);
    if (strcmp(confirm, "да") != 0 && strcmp(confirm, "Да") != 0 &&
        strcmp(confirm, "ДА") != 0) /* Проверяем подтверждение */
    {
        printf("Удаление отменено.\n"); /* Отмена */
        return; /* Выходим */
    }

    removeDetail(details, index); /* Удаляем из вектора */
    saveDetails(details);         /* Сохраняем в файл */
    printf("Деталь успешно удалена!\n"); /* Подтверждение */
}

/* ============================================================ */
/* Работа с браками                                             */
/* ============================================================ */

/* Просмотр всех браков */
void showAllDefects(DefectVector *defects)
{
    int i; /* Переменная цикла */

    if (defects->size == 0) /* Проверяем наличие данных */
    {
        printf("Список браков пуст.\n"); /* Сообщение */
        return; /* Выходим */
    }

    printf("\n%-5s %-6s %-20s %-20s %-15s\n",
           "№", "Код", "Свойство", "Вид", "Цена корр."); /* Заголовок */
    printf("----------------------------------------------------------------------\n"); /* Разделитель */

    for (i = 0; i < defects->size; i++) /* Перебираем все браки */
    {
        printf("%-5d %-6d %-20s %-20s %-15.2f\n",
               i + 1,                               /* Номер */
               defects->data[i].code,                /* Код */
               defects->data[i].property,            /* Свойство */
               defects->data[i].type,                /* Вид */
               defects->data[i].correction_price);   /* Цена корректировки */
    }
    printf("\n"); /* Пустая строка */
}

/* Добавление нового брака */
void addDefect(DefectVector *defects)
{
    Defect new_defect; /* Новый брак */

    printf("\n=== ДОБАВЛЕНИЕ ВИДА БРАКА ===\n"); /* Заголовок */

    new_defect.code = inputPositiveInt("Введите код брака: "); /* Вводим код */

    if (isDefectCodeExists(defects, new_defect.code)) /* Проверяем уникальность */
    {
        printf("Брак с таким кодом уже существует!\n"); /* Ошибка */
        return; /* Выходим */
    }

    inputString("Введите свойство: ", new_defect.property, MAX_STR_LEN);     /* Свойство */
    inputString("Введите вид брака: ", new_defect.type, MAX_STR_LEN);        /* Вид */
    new_defect.correction_price = inputPositiveDouble("Введите цену корректировки (руб.): "); /* Цена */

    pushDefect(defects, new_defect); /* Добавляем в вектор */
    saveDefects(defects);            /* Сохраняем в файл */
    printf("Вид брака успешно добавлен!\n"); /* Подтверждение */
}

/* Редактирование брака */
void editDefect(DefectVector *defects)
{
    int num;   /* Номер записи */
    int index; /* Индекс */

    printf("\n=== РЕДАКТИРОВАНИЕ ВИДА БРАКА ===\n"); /* Заголовок */
    showAllDefects(defects); /* Показываем все браки */

    if (defects->size == 0) return; /* Если нет данных, выходим */

    num = inputInt("Введите номер записи для редактирования: "); /* Вводим номер */
    index = num - 1; /* Преобразуем в индекс */

    if (index < 0 || index >= defects->size) /* Проверяем диапазон */
    {
        printf("Некорректный номер записи!\n"); /* Ошибка */
        return; /* Выходим */
    }

    printf("Текущее свойство: %s\n", defects->data[index].property); /* Показываем */
    inputString("Введите новое свойство: ", defects->data[index].property, MAX_STR_LEN); /* Новое */

    printf("Текущий вид: %s\n", defects->data[index].type); /* Показываем */
    inputString("Введите новый вид: ", defects->data[index].type, MAX_STR_LEN); /* Новый */

    printf("Текущая цена корректировки: %.2f\n", defects->data[index].correction_price); /* Показываем */
    defects->data[index].correction_price = inputPositiveDouble("Введите новую цену корректировки (руб.): ");

    saveDefects(defects); /* Сохраняем в файл */
    printf("Вид брака успешно отредактирован!\n"); /* Подтверждение */
}

/* Удаление брака */
void deleteDefect(DefectVector *defects, RecordVector *records)
{
    int num;   /* Номер записи */
    int index; /* Индекс */
    int i;     /* Переменная цикла */
    char confirm[MAX_STR_LEN]; /* Подтверждение */

    printf("\n=== УДАЛЕНИЕ ВИДА БРАКА ===\n"); /* Заголовок */
    showAllDefects(defects); /* Показываем все браки */

    if (defects->size == 0) return; /* Если нет данных, выходим */

    num = inputInt("Введите номер записи для удаления: "); /* Вводим номер */
    index = num - 1; /* Преобразуем в индекс */

    if (index < 0 || index >= defects->size) /* Проверяем диапазон */
    {
        printf("Некорректный номер записи!\n"); /* Ошибка */
        return; /* Выходим */
    }

    /* Проверяем, используется ли брак в записях учета */
    for (i = 0; i < records->size; i++) /* Перебираем записи учета */
    {
        if (records->data[i].defect_code == defects->data[index].code) /* Если связан */
        {
            printf("Нельзя удалить вид брака, который используется в записях учета!\n"); /* Ошибка */
            return; /* Выходим */
        }
    }

    inputString("Вы действительно хотите удалить запись? (да/нет): ", confirm, MAX_STR_LEN);
    if (strcmp(confirm, "да") != 0 && strcmp(confirm, "Да") != 0 &&
        strcmp(confirm, "ДА") != 0) /* Проверяем подтверждение */
    {
        printf("Удаление отменено.\n"); /* Отмена */
        return; /* Выходим */
    }

    removeDefect(defects, index); /* Удаляем из вектора */
    saveDefects(defects);         /* Сохраняем в файл */
    printf("Вид брака успешно удален!\n"); /* Подтверждение */
}

/* ============================================================ */
/* Работа с учетом                                              */
/* ============================================================ */

/* Просмотр всех записей учета */
void showAllRecords(RecordVector *records, DetailVector *details, DefectVector *defects)
{
    int i; /* Переменная цикла */

    if (records->size == 0) /* Проверяем наличие данных */
    {
        printf("Список записей учета пуст.\n"); /* Сообщение */
        return; /* Выходим */
    }

    printf("\n%-5s %-8s %-20s %-8s %-20s %-12s %-10s\n",
           "№", "КодДет", "Деталь", "КодБр", "Вид брака", "Дата", "Кол-во"); /* Заголовок */
    printf("------------------------------------------------------------------------------------\n"); /* Разделитель */

    for (i = 0; i < records->size; i++) /* Перебираем все записи */
    {
        printf("%-5d %-8d %-20s %-8d %-20s %-12s %-10d\n",
               i + 1,                                                     /* Номер */
               records->data[i].detail_code,                              /* Код детали */
               getDetailNameByCode(details, records->data[i].detail_code), /* Название детали */
               records->data[i].defect_code,                              /* Код брака */
               getDefectTypeByCode(defects, records->data[i].defect_code), /* Вид брака */
               records->data[i].defect_date,                              /* Дата */
               records->data[i].quantity);                                 /* Количество */
    }
    printf("\n"); /* Пустая строка */
}

/* Добавление записи учета */
void addRecord(RecordVector *records, DetailVector *details, DefectVector *defects)
{
    Record new_record; /* Новая запись */

    printf("\n=== ДОБАВЛЕНИЕ ЗАПИСИ УЧЕТА БРАКА ===\n"); /* Заголовок */

    /* Показываем доступные детали */
    showAllDetails(details); /* Отображаем список деталей */

    new_record.detail_code = inputPositiveInt("Введите код детали: "); /* Вводим код детали */
    if (!isDetailCodeExists(details, new_record.detail_code)) /* Проверяем существование */
    {
        printf("Деталь с таким кодом не найдена!\n"); /* Ошибка */
        return; /* Выходим */
    }

    /* Показываем доступные виды брака */
    showAllDefects(defects); /* Отображаем список браков */

    new_record.defect_code = inputPositiveInt("Введите код брака: "); /* Вводим код брака */
    if (!isDefectCodeExists(defects, new_record.defect_code)) /* Проверяем существование */
    {
        printf("Брак с таким кодом не найден!\n"); /* Ошибка */
        return; /* Выходим */
    }

    inputDate("Введите дату образования брака (ДД.ММ.ГГГГ): ", new_record.defect_date); /* Дата */
    new_record.quantity = inputPositiveInt("Введите количество: "); /* Количество */

    pushRecord(records, new_record); /* Добавляем в вектор */
    saveRecords(records);            /* Сохраняем в файл */
    printf("Запись учета успешно добавлена!\n"); /* Подтверждение */
}

/* Редактирование записи учета */
void editRecord(RecordVector *records, DetailVector *details, DefectVector *defects)
{
    int num;   /* Номер записи */
    int index; /* Индекс */
    int new_code; /* Новый код */

    printf("\n=== РЕДАКТИРОВАНИЕ ЗАПИСИ УЧЕТА ===\n"); /* Заголовок */
    showAllRecords(records, details, defects); /* Показываем все записи */

    if (records->size == 0) return; /* Если нет данных, выходим */

    num = inputInt("Введите номер записи для редактирования: "); /* Вводим номер */
    index = num - 1; /* Преобразуем в индекс */

    if (index < 0 || index >= records->size) /* Проверяем диапазон */
    {
        printf("Некорректный номер записи!\n"); /* Ошибка */
        return; /* Выходим */
    }

    /* Редактируем код детали */
    showAllDetails(details); /* Показываем детали */
    printf("Текущий код детали: %d\n", records->data[index].detail_code); /* Показываем */
    new_code = inputPositiveInt("Введите новый код детали: "); /* Вводим */
    if (!isDetailCodeExists(details, new_code)) /* Проверяем */
    {
        printf("Деталь с таким кодом не найдена!\n"); /* Ошибка */
        return; /* Выходим */
    }
    records->data[index].detail_code = new_code; /* Устанавливаем */

    /* Редактируем код брака */
    showAllDefects(defects); /* Показываем браки */
    printf("Текущий код брака: %d\n", records->data[index].defect_code); /* Показываем */
    new_code = inputPositiveInt("Введите новый код брака: "); /* Вводим */
    if (!isDefectCodeExists(defects, new_code)) /* Проверяем */
    {
        printf("Брак с таким кодом не найден!\n"); /* Ошибка */
        return; /* Выходим */
    }
    records->data[index].defect_code = new_code; /* Устанавливаем */

    printf("Текущая дата: %s\n", records->data[index].defect_date); /* Показываем */
    inputDate("Введите новую дату (ДД.ММ.ГГГГ): ", records->data[index].defect_date); /* Новая */

    printf("Текущее количество: %d\n", records->data[index].quantity); /* Показываем */
    records->data[index].quantity = inputPositiveInt("Введите новое количество: "); /* Новое */

    saveRecords(records); /* Сохраняем в файл */
    printf("Запись учета успешно отредактирована!\n"); /* Подтверждение */
}

/* Удаление записи учета */
void deleteRecord(RecordVector *records)
{
    int num;   /* Номер записи */
    int index; /* Индекс */
    char confirm[MAX_STR_LEN]; /* Подтверждение */

    printf("\n=== УДАЛЕНИЕ ЗАПИСИ УЧЕТА ===\n"); /* Заголовок */

    if (records->size == 0) /* Проверяем наличие данных */
    {
        printf("Список записей учета пуст.\n"); /* Сообщение */
        return; /* Выходим */
    }

    num = inputInt("Введите номер записи для удаления: "); /* Вводим номер */
    index = num - 1; /* Преобразуем в индекс */

    if (index < 0 || index >= records->size) /* Проверяем диапазон */
    {
        printf("Некорректный номер записи!\n"); /* Ошибка */
        return; /* Выходим */
    }

    inputString("Вы действительно хотите удалить запись? (да/нет): ", confirm, MAX_STR_LEN);
    if (strcmp(confirm, "да") != 0 && strcmp(confirm, "Да") != 0 &&
        strcmp(confirm, "ДА") != 0) /* Проверяем подтверждение */
    {
        printf("Удаление отменено.\n"); /* Отмена */
        return; /* Выходим */
    }

    removeRecord(records, index); /* Удаляем из вектора */
    saveRecords(records);         /* Сохраняем в файл */
    printf("Запись учета успешно удалена!\n"); /* Подтверждение */
}

/* ============================================================ */
/* Поиск                                                        */
/* ============================================================ */

/* Поиск деталей по названию */
void searchDetailsByName(DetailVector *details)
{
    char query[MAX_STR_LEN]; /* Строка поиска */
    int i;                   /* Переменная цикла */
    int found = 0;           /* Флаг: найдено ли что-то */

    inputString("Введите название для поиска: ", query, MAX_STR_LEN); /* Вводим запрос */

    printf("\nРезультаты поиска:\n"); /* Заголовок */
    printf("%-5s %-6s %-20s %-15s %-10s %-10s %-12s\n",
           "№", "Код", "Название", "Материал", "Вес", "Цена", "ДатаВыпуска"); /* Заголовок таблицы */
    printf("--------------------------------------------------------------------------------\n"); /* Разделитель */

    for (i = 0; i < details->size; i++) /* Перебираем все детали */
    {
        if (strstr(details->data[i].name, query) != NULL) /* Ищем вхождение подстроки */
        {
            printf("%-5d %-6d %-20s %-15s %-10.2f %-10.2f %-12s\n",
                   i + 1,                            /* Номер */
                   details->data[i].code,             /* Код */
                   details->data[i].name,             /* Название */
                   details->data[i].material,         /* Материал */
                   details->data[i].weight,           /* Вес */
                   details->data[i].price,            /* Цена */
                   details->data[i].release_date);    /* Дата */
            found = 1; /* Отмечаем, что нашли */
        }
    }

    if (!found) /* Если ничего не найдено */
    {
        printf("Ничего не найдено по запросу \"%s\".\n", query); /* Сообщение */
    }
}

/* Поиск деталей по материалу */
void searchDetailsByMaterial(DetailVector *details)
{
    char query[MAX_STR_LEN]; /* Строка поиска */
    int i;                   /* Переменная цикла */
    int found = 0;           /* Флаг */

    inputString("Введите материал для поиска: ", query, MAX_STR_LEN); /* Вводим запрос */

    printf("\nРезультаты поиска:\n"); /* Заголовок */
    printf("%-5s %-6s %-20s %-15s %-10s %-10s %-12s\n",
           "№", "Код", "Название", "Материал", "Вес", "Цена", "ДатаВыпуска"); /* Заголовок */
    printf("--------------------------------------------------------------------------------\n"); /* Разделитель */

    for (i = 0; i < details->size; i++) /* Перебираем все детали */
    {
        if (strstr(details->data[i].material, query) != NULL) /* Ищем подстроку */
        {
            printf("%-5d %-6d %-20s %-15s %-10.2f %-10.2f %-12s\n",
                   i + 1, details->data[i].code, details->data[i].name,
                   details->data[i].material, details->data[i].weight,
                   details->data[i].price, details->data[i].release_date);
            found = 1; /* Найдено */
        }
    }

    if (!found) printf("Ничего не найдено по запросу \"%s\".\n", query); /* Не найдено */
}

/* Поиск записей учета по дате */
void searchRecordsByDate(RecordVector *records, DetailVector *details, DefectVector *defects)
{
    char query[MAX_DATE_LEN]; /* Дата для поиска */
    int i;                    /* Переменная цикла */
    int found = 0;            /* Флаг */

    inputDate("Введите дату для поиска (ДД.ММ.ГГГГ): ", query); /* Вводим дату */

    printf("\nРезультаты поиска:\n"); /* Заголовок */
    printf("%-5s %-8s %-20s %-8s %-20s %-12s %-10s\n",
           "№", "КодДет", "Деталь", "КодБр", "Вид брака", "Дата", "Кол-во"); /* Заголовок */
    printf("------------------------------------------------------------------------------------\n");

    for (i = 0; i < records->size; i++) /* Перебираем все записи */
    {
        if (strcmp(records->data[i].defect_date, query) == 0) /* Сравниваем даты */
        {
            printf("%-5d %-8d %-20s %-8d %-20s %-12s %-10d\n",
                   i + 1,
                   records->data[i].detail_code,
                   getDetailNameByCode(details, records->data[i].detail_code),
                   records->data[i].defect_code,
                   getDefectTypeByCode(defects, records->data[i].defect_code),
                   records->data[i].defect_date,
                   records->data[i].quantity);
            found = 1; /* Найдено */
        }
    }

    if (!found) printf("Записи с датой \"%s\" не найдены.\n", query); /* Не найдено */
}

/* ============================================================ */
/* Сортировка (пузырьковая)                                     */
/* ============================================================ */

/* Сортировка деталей по названию */
void sortDetailsByName(DetailVector *details)
{
    int i, j;       /* Переменные циклов */
    Detail temp;    /* Временная переменная для обмена */

    if (details->size < 2) /* Если менее 2 элементов */
    {
        printf("Недостаточно данных для сортировки.\n"); /* Сообщение */
        return; /* Выходим */
    }

    for (i = 0; i < details->size - 1; i++) /* Внешний цикл */
    {
        for (j = 0; j < details->size - i - 1; j++) /* Внутренний цикл */
        {
            if (strcmp(details->data[j].name, details->data[j + 1].name) > 0) /* Сравниваем */
            {
                temp = details->data[j];                /* Сохраняем */
                details->data[j] = details->data[j + 1]; /* Меняем */
                details->data[j + 1] = temp;            /* Завершаем обмен */
            }
        }
    }
    printf("Детали отсортированы по названию.\n"); /* Подтверждение */
    showAllDetails(details); /* Показываем результат */
}

/* Сортировка деталей по цене */
void sortDetailsByPrice(DetailVector *details)
{
    int i, j;       /* Переменные циклов */
    Detail temp;    /* Временная переменная */

    if (details->size < 2) /* Если менее 2 элементов */
    {
        printf("Недостаточно данных для сортировки.\n"); /* Сообщение */
        return; /* Выходим */
    }

    for (i = 0; i < details->size - 1; i++) /* Внешний цикл */
    {
        for (j = 0; j < details->size - i - 1; j++) /* Внутренний цикл */
        {
            if (details->data[j].price > details->data[j + 1].price) /* Сравниваем */
            {
                temp = details->data[j];                /* Сохраняем */
                details->data[j] = details->data[j + 1]; /* Меняем */
                details->data[j + 1] = temp;            /* Завершаем обмен */
            }
        }
    }
    printf("Детали отсортированы по цене (по возрастанию).\n"); /* Подтверждение */
    showAllDetails(details); /* Показываем результат */
}

/* Сортировка деталей по весу */
void sortDetailsByWeight(DetailVector *details)
{
    int i, j;       /* Переменные циклов */
    Detail temp;    /* Временная переменная */

    if (details->size < 2) /* Если менее 2 элементов */
    {
        printf("Недостаточно данных для сортировки.\n"); /* Сообщение */
        return; /* Выходим */
    }

    for (i = 0; i < details->size - 1; i++) /* Внешний цикл */
    {
        for (j = 0; j < details->size - i - 1; j++) /* Внутренний цикл */
        {
            if (details->data[j].weight > details->data[j + 1].weight) /* Сравниваем */
            {
                temp = details->data[j];                /* Сохраняем */
                details->data[j] = details->data[j + 1]; /* Меняем */
                details->data[j + 1] = temp;            /* Завершаем обмен */
            }
        }
    }
    printf("Детали отсортированы по весу (по возрастанию).\n"); /* Подтверждение */
    showAllDetails(details); /* Показываем результат */
}

/* Сортировка записей учета по дате */
void sortRecordsByDate(RecordVector *records)
{
    int i, j;       /* Переменные циклов */
    Record temp;    /* Временная переменная */

    if (records->size < 2) /* Если менее 2 элементов */
    {
        printf("Недостаточно данных для сортировки.\n"); /* Сообщение */
        return; /* Выходим */
    }

    for (i = 0; i < records->size - 1; i++) /* Внешний цикл */
    {
        for (j = 0; j < records->size - i - 1; j++) /* Внутренний цикл */
        {
            if (compareDates(records->data[j].defect_date, records->data[j + 1].defect_date) > 0)
            {
                temp = records->data[j];                /* Сохраняем */
                records->data[j] = records->data[j + 1]; /* Меняем */
                records->data[j + 1] = temp;            /* Завершаем обмен */
            }
        }
    }
    printf("Записи учета отсортированы по дате.\n"); /* Подтверждение */
}

/* Сортировка записей учета по количеству */
void sortRecordsByQuantity(RecordVector *records)
{
    int i, j;       /* Переменные циклов */
    Record temp;    /* Временная переменная */

    if (records->size < 2) /* Если менее 2 элементов */
    {
        printf("Недостаточно данных для сортировки.\n"); /* Сообщение */
        return; /* Выходим */
    }

    for (i = 0; i < records->size - 1; i++) /* Внешний цикл */
    {
        for (j = 0; j < records->size - i - 1; j++) /* Внутренний цикл */
        {
            if (records->data[j].quantity > records->data[j + 1].quantity) /* Сравниваем */
            {
                temp = records->data[j];                /* Сохраняем */
                records->data[j] = records->data[j + 1]; /* Меняем */
                records->data[j + 1] = temp;            /* Завершаем обмен */
            }
        }
    }
    printf("Записи учета отсортированы по количеству (по возрастанию).\n"); /* Подтверждение */
}

/* ============================================================ */
/* Индивидуальное задание                                       */
/* ============================================================ */

/* Вывести количество бракованных деталей за определенный период */
void countDefectsByPeriod(RecordVector *records, DetailVector *details, DefectVector *defects)
{
    char date_from[MAX_DATE_LEN]; /* Начальная дата периода */
    char date_to[MAX_DATE_LEN];   /* Конечная дата периода */
    int total_count = 0;          /* Общее количество бракованных деталей */
    int i;                        /* Переменная цикла */
    int found = 0;                /* Флаг: найдены ли записи */

    printf("\n=== КОЛИЧЕСТВО БРАКОВАННЫХ ДЕТАЛЕЙ ЗА ПЕРИОД ===\n"); /* Заголовок */

    inputDate("Введите начальную дату периода (ДД.ММ.ГГГГ): ", date_from); /* Начало */
    inputDate("Введите конечную дату периода (ДД.ММ.ГГГГ): ", date_to);     /* Конец */

    /* Проверяем, что начальная дата не позже конечной */
    if (compareDates(date_from, date_to) > 0) /* Если начало позже конца */
    {
        printf("Начальная дата не может быть позже конечной!\n"); /* Ошибка */
        return; /* Выходим */
    }

    printf("\nЗаписи за период с %s по %s:\n", date_from, date_to); /* Информируем */
    printf("%-8s %-20s %-20s %-12s %-10s\n",
           "КодДет", "Деталь", "Вид брака", "Дата", "Кол-во"); /* Заголовок */
    printf("----------------------------------------------------------------------\n"); /* Разделитель */

    for (i = 0; i < records->size; i++) /* Перебираем все записи учета */
    {
        /* Проверяем, попадает ли дата в период */
        if (compareDates(records->data[i].defect_date, date_from) >= 0 &&
            compareDates(records->data[i].defect_date, date_to) <= 0)
        {
            printf("%-8d %-20s %-20s %-12s %-10d\n",
                   records->data[i].detail_code,                                /* Код детали */
                   getDetailNameByCode(details, records->data[i].detail_code),  /* Название */
                   getDefectTypeByCode(defects, records->data[i].defect_code),  /* Вид брака */
                   records->data[i].defect_date,                                /* Дата */
                   records->data[i].quantity);                                  /* Количество */
            total_count += records->data[i].quantity; /* Суммируем количество */
            found = 1; /* Отмечаем, что нашли */
        }
    }

    if (found) /* Если записи найдены */
    {
        printf("\nИтого бракованных деталей за период: %d\n", total_count); /* Итог */
    }
    else /* Если записи не найдены */
    {
        printf("За указанный период бракованных деталей не обнаружено.\n"); /* Сообщение */
    }
}
