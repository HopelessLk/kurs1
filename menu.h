/* menu.h - Модуль меню программы */
#pragma once /* Защита от повторного включения */

#ifndef MENU_H /* Защита от повторного включения */
#define MENU_H /* Определяем макрос */

#include "structures.h" /* Подключаем определения структур */

/* Главное меню администратора */
void menuAdmin(AccountVector *accounts, DetailVector *details,
               DefectVector *defects, RecordVector *records, int user_index);

/* Главное меню пользователя */
void menuUser(DetailVector *details, DefectVector *defects, RecordVector *records);

/* Подменю редактирования данных (для администратора) */
void menuEditData(DetailVector *details, DefectVector *defects, RecordVector *records);

/* Подменю обработки данных (для администратора и пользователя) */
void menuProcessData(DetailVector *details, DefectVector *defects, RecordVector *records);

/* Подменю поиска */
void menuSearch(DetailVector *details, DefectVector *defects, RecordVector *records);

/* Подменю сортировки */
void menuSort(DetailVector *details, DefectVector *defects, RecordVector *records);

#endif /* MENU_H */
