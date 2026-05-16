/* constants.h - Глобальные константы программы */
#pragma once /* Защита от повторного включения */

#ifndef CONSTANTS_H /* Защита от повторного включения */
#define CONSTANTS_H /* Определяем макрос */

/* Имена файлов для хранения данных */
#define FILE_ACCOUNTS "accounts.txt"     /* Файл учетных записей */
#define FILE_DETAILS "details.txt"       /* Файл деталей */
#define FILE_DEFECTS "defects.txt"       /* Файл браков */
#define FILE_RECORDS "records.txt"       /* Файл учета */

/* Начальная емкость векторов */
#define INITIAL_CAPACITY 10              /* Начальный размер динамического массива */

/* Роли пользователей */
#define ROLE_USER 0                      /* Роль: пользователь */
#define ROLE_ADMIN 1                     /* Роль: администратор */

/* Логин и пароль администратора по умолчанию */
#define DEFAULT_ADMIN_LOGIN "admin"      /* Логин администратора по умолчанию */
#define DEFAULT_ADMIN_PASSWORD "admin"   /* Пароль администратора по умолчанию */

/* Коды возврата меню */
#define MENU_EXIT 0                      /* Выход из меню */

#endif /* CONSTANTS_H */
