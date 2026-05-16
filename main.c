/* main.c - Главный файл программы учета бракованных деталей */

#include <stdio.h>    /* Для printf */
#include <stdlib.h>   /* Для system, exit */
#include <locale.h>   /* Для setlocale */
#include "structures.h"  /* Подключаем определения структур */
#include "constants.h"   /* Подключаем константы */
#include "vector_ops.h"  /* Подключаем операции с векторами */
#include "file_ops.h"    /* Подключаем файловые операции */
#include "auth.h"        /* Подключаем модуль авторизации */
#include "menu.h"        /* Подключаем модуль меню */

/* Главная функция программы */

system("chcp 65001");
int main(void)
{
    AccountVector accounts; /* Вектор учетных записей */
    DetailVector details;   /* Вектор деталей */
    DefectVector defects;   /* Вектор браков */
    RecordVector records;   /* Вектор учета */
    int user_index;         /* Индекс авторизованного пользователя */

    setlocale(LC_ALL, "ru_RU.UTF-8"); /* Устанавливаем русскую локаль */

    printf("============================================\n");           /* Разделитель */
    printf("  ПРОГРАММА УЧЕТА БРАКОВАННЫХ ДЕТАЛЕЙ\n");                 /* Название */
    printf("  произведенных в цеху\n");                                /* Подзаголовок */
    printf("============================================\n\n");         /* Разделитель */

    /* Инициализируем все векторы */
    initAccountVector(&accounts); /* Инициализация вектора учетных записей */
    initDetailVector(&details);   /* Инициализация вектора деталей */
    initDefectVector(&defects);   /* Инициализация вектора браков */
    initRecordVector(&records);   /* Инициализация вектора учета */

    /* Загружаем данные из файлов */
    loadAccounts(&accounts); /* Загружаем учетные записи */
    loadDetails(&details);   /* Загружаем детали */
    loadDefects(&defects);   /* Загружаем браки */
    loadRecords(&records);   /* Загружаем записи учета */

    /* Авторизация пользователя */
    user_index = authorize(&accounts); /* Выполняем авторизацию */

    if (user_index == -1) /* Если авторизация не пройдена */
    {
        printf("Доступ запрещен. Программа завершена.\n"); /* Сообщение */
        /* Освобождаем память перед выходом */
        freeAccountVector(&accounts); /* Освобождаем память учетных записей */
        freeDetailVector(&details);   /* Освобождаем память деталей */
        freeDefectVector(&defects);   /* Освобождаем память браков */
        freeRecordVector(&records);   /* Освобождаем память учета */
        return 1; /* Завершаем программу с кодом ошибки */
    }

    /* Определяем роль пользователя и показываем соответствующее меню */
    if (accounts.data[user_index].role == ROLE_ADMIN) /* Если администратор */
    {
        menuAdmin(&accounts, &details, &defects, &records, user_index); /* Меню администратора */
    }
    else /* Если пользователь */
    {
        menuUser(&details, &defects, &records); /* Меню пользователя */
    }

    /* Освобождаем выделенную память */
    freeAccountVector(&accounts); /* Освобождаем память учетных записей */
    freeDetailVector(&details);   /* Освобождаем память деталей */
    freeDefectVector(&defects);   /* Освобождаем память браков */
    freeRecordVector(&records);   /* Освобождаем память учета */

    printf("\nПрограмма завершена. До свидания!\n"); /* Прощальное сообщение */
    return 0; /* Успешное завершение программы */
}
