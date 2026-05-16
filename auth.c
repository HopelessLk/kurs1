/* auth.c - Реализация модуля авторизации и управления учетными записями */

#include <stdio.h>   /* Для printf, scanf */
#include <string.h>  /* Для strcmp, strcpy */
#include <stdlib.h>  /* Для общих функций */
#include "auth.h"        /* Подключаем заголовочный файл */
#include "vector_ops.h"  /* Подключаем операции с векторами */
#include "validation.h"  /* Подключаем функции валидации */
#include "file_ops.h"    /* Подключаем файловые операции */
#include "constants.h"   /* Подключаем константы */

/* Авторизация пользователя */
int authorize(AccountVector *accounts)
{
    char login[MAX_STR_LEN];    /* Введенный логин */
    char password[MAX_STR_LEN]; /* Введенный пароль */
    int i;                      /* Переменная цикла */
    int attempts = 3;           /* Количество попыток */

    printf("\n=== АВТОРИЗАЦИЯ ===\n"); /* Заголовок */

    while (attempts > 0) /* Пока есть попытки */
    {
        inputString("Логин: ", login, MAX_STR_LEN);       /* Вводим логин */
        inputString("Пароль: ", password, MAX_STR_LEN);   /* Вводим пароль */

        for (i = 0; i < accounts->size; i++) /* Перебираем все учетные записи */
        {
            /* Сравниваем логин и пароль */
            if (strcmp(accounts->data[i].login, login) == 0 &&
                strcmp(accounts->data[i].password, password) == 0)
            {
                printf("Авторизация успешна!\n"); /* Сообщение об успехе */
                if (accounts->data[i].role == ROLE_ADMIN) /* Проверяем роль */
                {
                    printf("Вы вошли как администратор.\n"); /* Информируем о роли */
                }
                else /* Если пользователь */
                {
                    printf("Вы вошли как пользователь.\n"); /* Информируем о роли */
                }
                return i; /* Возвращаем индекс пользователя */
            }
        }

        attempts--; /* Уменьшаем количество попыток */
        printf("Неверный логин или пароль! Осталось попыток: %d\n", attempts); /* Ошибка */
    }

    printf("Все попытки исчерпаны!\n"); /* Сообщение об исчерпании попыток */
    return -1; /* Возвращаем -1 при неудаче */
}

/* Проверка уникальности логина */
int isLoginUnique(AccountVector *accounts, const char *login)
{
    int i; /* Переменная цикла */

    for (i = 0; i < accounts->size; i++) /* Перебираем все учетные записи */
    {
        if (strcmp(accounts->data[i].login, login) == 0) /* Сравниваем логины */
        {
            return 0; /* Логин не уникален */
        }
    }
    return 1; /* Логин уникален */
}

/* Просмотр всех учетных записей */
void showAllAccounts(AccountVector *accounts)
{
    int i; /* Переменная цикла */

    if (accounts->size == 0) /* Проверяем наличие записей */
    {
        printf("Список учетных записей пуст.\n"); /* Сообщение */
        return; /* Выходим */
    }

    printf("\n%-5s %-20s %-20s %-15s\n", "№", "Логин", "Пароль", "Роль"); /* Заголовок таблицы */
    printf("-------------------------------------------------------------\n"); /* Разделитель */

    for (i = 0; i < accounts->size; i++) /* Перебираем все записи */
    {
        printf("%-5d %-20s %-20s %-15s\n",
               i + 1,                                                     /* Номер записи */
               accounts->data[i].login,                                   /* Логин */
               accounts->data[i].password,                                /* Пароль */
               accounts->data[i].role == ROLE_ADMIN ? "Администратор" : "Пользователь"); /* Роль */
    }
    printf("\n"); /* Пустая строка */
}

/* Добавление новой учетной записи */
void addAccount(AccountVector *accounts)
{
    Account new_account; /* Новая учетная запись */

    printf("\n=== ДОБАВЛЕНИЕ УЧЕТНОЙ ЗАПИСИ ===\n"); /* Заголовок */

    inputString("Введите логин: ", new_account.login, MAX_STR_LEN); /* Вводим логин */

    if (!isLoginUnique(accounts, new_account.login)) /* Проверяем уникальность */
    {
        printf("Учетная запись с таким логином уже существует!\n"); /* Сообщение об ошибке */
        return; /* Выходим */
    }

    inputString("Введите пароль: ", new_account.password, MAX_STR_LEN); /* Вводим пароль */

    printf("Выберите роль (0 - пользователь, 1 - администратор): "); /* Подсказка */
    new_account.role = inputMenuChoice(0, 1); /* Вводим роль */

    pushAccount(accounts, new_account); /* Добавляем в вектор */
    saveAccounts(accounts);             /* Сохраняем в файл */
    printf("Учетная запись успешно добавлена!\n"); /* Подтверждение */
}

/* Редактирование учетной записи */
void editAccount(AccountVector *accounts, int current_user_index)
{
    int num;             /* Номер записи для редактирования */
    int index;           /* Индекс в массиве */
    char new_login[MAX_STR_LEN]; /* Новый логин */

    printf("\n=== РЕДАКТИРОВАНИЕ УЧЕТНОЙ ЗАПИСИ ===\n"); /* Заголовок */
    showAllAccounts(accounts); /* Показываем все записи */

    if (accounts->size == 0) return; /* Если нет записей, выходим */

    num = inputInt("Введите номер записи для редактирования: "); /* Вводим номер */
    index = num - 1; /* Преобразуем в индекс */

    if (index < 0 || index >= accounts->size) /* Проверяем диапазон */
    {
        printf("Некорректный номер записи!\n"); /* Сообщение об ошибке */
        return; /* Выходим */
    }

    printf("Текущий логин: %s\n", accounts->data[index].login); /* Показываем текущий логин */
    inputString("Введите новый логин (или тот же): ", new_login, MAX_STR_LEN); /* Вводим новый */

    /* Проверяем уникальность только если логин изменился */
    if (strcmp(new_login, accounts->data[index].login) != 0) /* Если логин изменился */
    {
        if (!isLoginUnique(accounts, new_login)) /* Проверяем уникальность */
        {
            printf("Учетная запись с таким логином уже существует!\n"); /* Ошибка */
            return; /* Выходим */
        }
    }
    strcpy(accounts->data[index].login, new_login); /* Устанавливаем новый логин */

    printf("Текущий пароль: %s\n", accounts->data[index].password); /* Показываем пароль */
    inputString("Введите новый пароль: ", accounts->data[index].password, MAX_STR_LEN); /* Новый пароль */

    /* Не даем менять роль самому себе */
    if (index != current_user_index) /* Если редактируем не себя */
    {
        printf("Текущая роль: %s\n",
               accounts->data[index].role == ROLE_ADMIN ? "Администратор" : "Пользователь"); /* Роль */
        printf("Выберите новую роль (0 - пользователь, 1 - администратор): "); /* Подсказка */
        accounts->data[index].role = inputMenuChoice(0, 1); /* Вводим роль */
    }

    saveAccounts(accounts); /* Сохраняем в файл */
    printf("Учетная запись успешно отредактирована!\n"); /* Подтверждение */
}

/* Удаление учетной записи */
void deleteAccount(AccountVector *accounts, int current_user_index)
{
    int num;     /* Номер записи для удаления */
    int index;   /* Индекс в массиве */
    char confirm[MAX_STR_LEN]; /* Подтверждение удаления */

    printf("\n=== УДАЛЕНИЕ УЧЕТНОЙ ЗАПИСИ ===\n"); /* Заголовок */
    showAllAccounts(accounts); /* Показываем все записи */

    if (accounts->size == 0) return; /* Если нет записей, выходим */

    num = inputInt("Введите номер записи для удаления: "); /* Вводим номер */
    index = num - 1; /* Преобразуем в индекс */

    if (index < 0 || index >= accounts->size) /* Проверяем диапазон */
    {
        printf("Некорректный номер записи!\n"); /* Сообщение об ошибке */
        return; /* Выходим */
    }

    if (index == current_user_index) /* Проверяем, не удаляет ли себя */
    {
        printf("Нельзя удалить собственную учетную запись!\n"); /* Запрет */
        return; /* Выходим */
    }

    /* Запрашиваем подтверждение */
    inputString("Вы действительно хотите удалить запись? (да/нет): ", confirm, MAX_STR_LEN);
    if (strcmp(confirm, "да") != 0 && strcmp(confirm, "Да") != 0 &&
        strcmp(confirm, "ДА") != 0) /* Проверяем подтверждение */
    {
        printf("Удаление отменено.\n"); /* Сообщение об отмене */
        return; /* Выходим */
    }

    removeAccount(accounts, index); /* Удаляем из вектора */
    saveAccounts(accounts);         /* Сохраняем в файл */
    printf("Учетная запись успешно удалена!\n"); /* Подтверждение */
}

/* Меню управления учетными записями */
void menuManageAccounts(AccountVector *accounts, int current_user_index)
{
    int choice; /* Выбранный пункт меню */

    while (1) /* Бесконечный цикл меню */
    {
        printf("\n=== УПРАВЛЕНИЕ УЧЕТНЫМИ ЗАПИСЯМИ ===\n"); /* Заголовок меню */
        printf("1. Просмотр всех учетных записей\n");       /* Пункт 1 */
        printf("2. Добавление новой учетной записи\n");     /* Пункт 2 */
        printf("3. Редактирование учетной записи\n");       /* Пункт 3 */
        printf("4. Удаление учетной записи\n");             /* Пункт 4 */
        printf("0. Назад\n");                               /* Пункт выхода */

        choice = inputMenuChoice(0, 4); /* Вводим выбор */

        switch (choice) /* Обрабатываем выбор */
        {
            case 1: /* Просмотр */
                showAllAccounts(accounts);
                break;
            case 2: /* Добавление */
                addAccount(accounts);
                break;
            case 3: /* Редактирование */
                editAccount(accounts, current_user_index);
                break;
            case 4: /* Удаление */
                deleteAccount(accounts, current_user_index);
                break;
            case 0: /* Выход */
                return; /* Возвращаемся в предыдущее меню */
            default: /* На всякий случай */
                break;
        }
    }
}
