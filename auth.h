/* auth.h - Модуль авторизации и управления учетными записями */
#pragma once /* Защита от повторного включения */

#ifndef AUTH_H /* Защита от повторного включения */
#define AUTH_H /* Определяем макрос */

#include "structures.h" /* Подключаем определения структур */

/* Авторизация пользователя; возвращает индекс в векторе или -1 при неудаче */
int authorize(AccountVector *accounts);

/* Проверка уникальности логина; возвращает 1, если логин уникален */
int isLoginUnique(AccountVector *accounts, const char *login);

/* Меню управления учетными записями (для администратора) */
void menuManageAccounts(AccountVector *accounts, int current_user_index);

/* Просмотр всех учетных записей */
void showAllAccounts(AccountVector *accounts);

/* Добавление новой учетной записи */
void addAccount(AccountVector *accounts);

/* Редактирование учетной записи */
void editAccount(AccountVector *accounts, int current_user_index);

/* Удаление учетной записи */
void deleteAccount(AccountVector *accounts, int current_user_index);

#endif /* AUTH_H */
