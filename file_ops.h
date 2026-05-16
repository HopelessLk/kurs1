/* file_ops.h - Операции чтения/записи данных в файлы */
#pragma once /* Защита от повторного включения */

#ifndef FILE_OPS_H /* Защита от повторного включения */
#define FILE_OPS_H /* Определяем макрос */

#include "structures.h" /* Подключаем определения структур */

/* === Функции для работы с файлом учетных записей === */
void loadAccounts(AccountVector *vec);                /* Чтение учетных записей из файла */
void saveAccounts(AccountVector *vec);                /* Запись учетных записей в файл */

/* === Функции для работы с файлом деталей === */
void loadDetails(DetailVector *vec);                  /* Чтение деталей из файла */
void saveDetails(DetailVector *vec);                  /* Запись деталей в файл */

/* === Функции для работы с файлом браков === */
void loadDefects(DefectVector *vec);                  /* Чтение браков из файла */
void saveDefects(DefectVector *vec);                  /* Запись браков в файл */

/* === Функции для работы с файлом учета === */
void loadRecords(RecordVector *vec);                  /* Чтение записей учета из файла */
void saveRecords(RecordVector *vec);                  /* Запись записей учета в файл */

#endif /* FILE_OPS_H */
