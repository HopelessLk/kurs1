/* menu.c - Реализация модуля меню программы */

#include <stdio.h>   /* Для printf */
#include "menu.h"        /* Подключаем заголовочный файл */
#include "auth.h"        /* Подключаем модуль авторизации */
#include "data_ops.h"    /* Подключаем операции с данными */
#include "validation.h"  /* Подключаем функции валидации */
#include "constants.h"   /* Подключаем константы */

/* ============================================================ */
/* Подменю поиска                                               */
/* ============================================================ */

/* Подменю поиска */
void menuSearch(DetailVector *details, DefectVector *defects, RecordVector *records)
{
    int choice; /* Выбранный пункт */

    while (1) /* Бесконечный цикл меню */
    {
        printf("\n=== ПОИСК ===\n");                          /* Заголовок */
        printf("1. Поиск деталей по названию\n");             /* Пункт 1 */
        printf("2. Поиск деталей по материалу\n");            /* Пункт 2 */
        printf("3. Поиск записей учета по дате\n");           /* Пункт 3 */
        printf("0. Назад\n");                                 /* Пункт выхода */

        choice = inputMenuChoice(0, 3); /* Вводим выбор */

        switch (choice) /* Обрабатываем выбор */
        {
            case 1: /* Поиск по названию */
                searchDetailsByName(details);
                break;
            case 2: /* Поиск по материалу */
                searchDetailsByMaterial(details);
                break;
            case 3: /* Поиск по дате */
                searchRecordsByDate(records, details, defects);
                break;
            case 0: /* Выход */
                return; /* Возвращаемся */
            default: /* На всякий случай */
                break;
        }
    }
}

/* ============================================================ */
/* Подменю сортировки                                           */
/* ============================================================ */

/* Подменю сортировки */
void menuSort(DetailVector *details, DefectVector *defects, RecordVector *records)
{
    int choice; /* Выбранный пункт */

    while (1) /* Бесконечный цикл меню */
    {
        printf("\n=== СОРТИРОВКА ===\n");                      /* Заголовок */
        printf("1. Сортировка деталей по названию\n");         /* Пункт 1 */
        printf("2. Сортировка деталей по цене\n");             /* Пункт 2 */
        printf("3. Сортировка деталей по весу\n");             /* Пункт 3 */
        printf("4. Сортировка учета по дате\n");               /* Пункт 4 */
        printf("5. Сортировка учета по количеству\n");         /* Пункт 5 */
        printf("0. Назад\n");                                  /* Пункт выхода */

        choice = inputMenuChoice(0, 5); /* Вводим выбор */

        switch (choice) /* Обрабатываем выбор */
        {
            case 1: /* По названию */
                sortDetailsByName(details);
                break;
            case 2: /* По цене */
                sortDetailsByPrice(details);
                break;
            case 3: /* По весу */
                sortDetailsByWeight(details);
                break;
            case 4: /* По дате */
                sortRecordsByDate(records);
                showAllRecords(records, details, defects); /* Показываем результат */
                break;
            case 5: /* По количеству */
                sortRecordsByQuantity(records);
                showAllRecords(records, details, defects); /* Показываем результат */
                break;
            case 0: /* Выход */
                return; /* Возвращаемся */
            default: /* На всякий случай */
                break;
        }
    }
}

/* ============================================================ */
/* Подменю редактирования данных (администратор)                */
/* ============================================================ */

/* Подменю редактирования данных */
void menuEditData(DetailVector *details, DefectVector *defects, RecordVector *records)
{
    int choice; /* Выбранный пункт */

    while (1) /* Бесконечный цикл меню */
    {
        printf("\n=== РЕДАКТИРОВАНИЕ ДАННЫХ ===\n");           /* Заголовок */
        printf("--- Детали ---\n");                            /* Подзаголовок */
        printf("1. Просмотр всех деталей\n");                  /* Пункт 1 */
        printf("2. Добавление детали\n");                      /* Пункт 2 */
        printf("3. Редактирование детали\n");                  /* Пункт 3 */
        printf("4. Удаление детали\n");                        /* Пункт 4 */
        printf("--- Виды брака ---\n");                        /* Подзаголовок */
        printf("5. Просмотр всех видов брака\n");              /* Пункт 5 */
        printf("6. Добавление вида брака\n");                  /* Пункт 6 */
        printf("7. Редактирование вида брака\n");              /* Пункт 7 */
        printf("8. Удаление вида брака\n");                    /* Пункт 8 */
        printf("--- Учет брака ---\n");                        /* Подзаголовок */
        printf("9. Просмотр всех записей учета\n");            /* Пункт 9 */
        printf("10. Добавление записи учета\n");               /* Пункт 10 */
        printf("11. Редактирование записи учета\n");           /* Пункт 11 */
        printf("12. Удаление записи учета\n");                 /* Пункт 12 */
        printf("0. Назад\n");                                  /* Пункт выхода */

        choice = inputMenuChoice(0, 12); /* Вводим выбор */

        switch (choice) /* Обрабатываем выбор */
        {
            case 1:  showAllDetails(details); break;                    /* Просмотр деталей */
            case 2:  addDetail(details); break;                         /* Добавление детали */
            case 3:  editDetail(details); break;                        /* Редактирование детали */
            case 4:  deleteDetail(details, records); break;             /* Удаление детали */
            case 5:  showAllDefects(defects); break;                    /* Просмотр браков */
            case 6:  addDefect(defects); break;                         /* Добавление брака */
            case 7:  editDefect(defects); break;                        /* Редактирование брака */
            case 8:  deleteDefect(defects, records); break;             /* Удаление брака */
            case 9:  showAllRecords(records, details, defects); break;  /* Просмотр учета */
            case 10: addRecord(records, details, defects); break;       /* Добавление учета */
            case 11: editRecord(records, details, defects); break;      /* Редактирование учета */
            case 12: deleteRecord(records); break;                      /* Удаление учета */
            case 0:  return;                                            /* Выход */
            default: break;                                             /* На всякий случай */
        }
    }
}

/* ============================================================ */
/* Подменю обработки данных                                     */
/* ============================================================ */

/* Подменю обработки данных */
void menuProcessData(DetailVector *details, DefectVector *defects, RecordVector *records)
{
    int choice; /* Выбранный пункт */

    while (1) /* Бесконечный цикл меню */
    {
        printf("\n=== ОБРАБОТКА ДАННЫХ ===\n");                /* Заголовок */
        printf("1. Индивидуальное задание (бракованные детали за период)\n"); /* Пункт 1 */
        printf("2. Поиск\n");                                  /* Пункт 2 */
        printf("3. Сортировка\n");                             /* Пункт 3 */
        printf("0. Назад\n");                                  /* Пункт выхода */

        choice = inputMenuChoice(0, 3); /* Вводим выбор */

        switch (choice) /* Обрабатываем выбор */
        {
            case 1: /* Индивидуальное задание */
                countDefectsByPeriod(records, details, defects);
                break;
            case 2: /* Поиск */
                menuSearch(details, defects, records);
                break;
            case 3: /* Сортировка */
                menuSort(details, defects, records);
                break;
            case 0: /* Выход */
                return; /* Возвращаемся */
            default: /* На всякий случай */
                break;
        }
    }
}

/* ============================================================ */
/* Главное меню администратора                                  */
/* ============================================================ */

/* Главное меню администратора */
void menuAdmin(AccountVector *accounts, DetailVector *details,
               DefectVector *defects, RecordVector *records, int user_index)
{
    int choice; /* Выбранный пункт */

    while (1) /* Бесконечный цикл меню */
    {
        printf("\n========================================\n");    /* Разделитель */
        printf("=== МЕНЮ АДМИНИСТРАТОРА ===\n");                  /* Заголовок */
        printf("========================================\n");      /* Разделитель */
        printf("1. Управление учетными записями\n");               /* Пункт 1 */
        printf("2. Работа с данными (редактирование)\n");          /* Пункт 2 */
        printf("3. Работа с данными (обработка)\n");               /* Пункт 3 */
        printf("0. Выход из системы\n");                           /* Пункт выхода */

        choice = inputMenuChoice(0, 3); /* Вводим выбор */

        switch (choice) /* Обрабатываем выбор */
        {
            case 1: /* Управление учетными записями */
                menuManageAccounts(accounts, user_index);
                break;
            case 2: /* Редактирование данных */
                menuEditData(details, defects, records);
                break;
            case 3: /* Обработка данных */
                menuProcessData(details, defects, records);
                break;
            case 0: /* Выход */
                printf("Выход из системы.\n"); /* Сообщение */
                return; /* Возвращаемся */
            default: /* На всякий случай */
                break;
        }
    }
}

/* ============================================================ */
/* Главное меню пользователя                                    */
/* ============================================================ */

/* Главное меню пользователя */
void menuUser(DetailVector *details, DefectVector *defects, RecordVector *records)
{
    int choice; /* Выбранный пункт */

    while (1) /* Бесконечный цикл меню */
    {
        printf("\n========================================\n");    /* Разделитель */
        printf("=== МЕНЮ ПОЛЬЗОВАТЕЛЯ ===\n");                    /* Заголовок */
        printf("========================================\n");      /* Разделитель */
        printf("1. Просмотр всех деталей\n");                      /* Пункт 1 */
        printf("2. Просмотр всех видов брака\n");                  /* Пункт 2 */
        printf("3. Просмотр записей учета\n");                     /* Пункт 3 */
        printf("4. Индивидуальное задание (бракованные детали за период)\n"); /* Пункт 4 */
        printf("5. Поиск\n");                                      /* Пункт 5 */
        printf("6. Сортировка\n");                                 /* Пункт 6 */
        printf("0. Выход из системы\n");                           /* Пункт выхода */

        choice = inputMenuChoice(0, 6); /* Вводим выбор */

        switch (choice) /* Обрабатываем выбор */
        {
            case 1: /* Просмотр деталей */
                showAllDetails(details);
                break;
            case 2: /* Просмотр браков */
                showAllDefects(defects);
                break;
            case 3: /* Просмотр учета */
                showAllRecords(records, details, defects);
                break;
            case 4: /* Индивидуальное задание */
                countDefectsByPeriod(records, details, defects);
                break;
            case 5: /* Поиск */
                menuSearch(details, defects, records);
                break;
            case 6: /* Сортировка */
                menuSort(details, defects, records);
                break;
            case 0: /* Выход */
                printf("Выход из системы.\n"); /* Сообщение */
                return; /* Возвращаемся */
            default: /* На всякий случай */
                break;
        }
    }
}
