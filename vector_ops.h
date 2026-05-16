/* vector_ops.h - Операции с динамическими массивами (векторами) */
#pragma once /* Защита от повторного включения */

#ifndef VECTOR_OPS_H /* Защита от повторного включения */
#define VECTOR_OPS_H /* Определяем макрос */

#include "structures.h" /* Подключаем определения структур */

/* === Функции для вектора учетных записей === */
void initAccountVector(AccountVector *vec);          /* Инициализация вектора учетных записей */
void pushAccount(AccountVector *vec, Account item);  /* Добавление учетной записи в вектор */
void removeAccount(AccountVector *vec, int index);   /* Удаление учетной записи по индексу */
void freeAccountVector(AccountVector *vec);           /* Освобождение памяти вектора учетных записей */

/* === Функции для вектора деталей === */
void initDetailVector(DetailVector *vec);             /* Инициализация вектора деталей */
void pushDetail(DetailVector *vec, Detail item);      /* Добавление детали в вектор */
void removeDetail(DetailVector *vec, int index);      /* Удаление детали по индексу */
void freeDetailVector(DetailVector *vec);              /* Освобождение памяти вектора деталей */

/* === Функции для вектора браков === */
void initDefectVector(DefectVector *vec);             /* Инициализация вектора браков */
void pushDefect(DefectVector *vec, Defect item);      /* Добавление брака в вектор */
void removeDefect(DefectVector *vec, int index);      /* Удаление брака по индексу */
void freeDefectVector(DefectVector *vec);              /* Освобождение памяти вектора браков */

/* === Функции для вектора учета === */
void initRecordVector(RecordVector *vec);             /* Инициализация вектора учета */
void pushRecord(RecordVector *vec, Record item);      /* Добавление записи учета в вектор */
void removeRecord(RecordVector *vec, int index);      /* Удаление записи учета по индексу */
void freeRecordVector(RecordVector *vec);              /* Освобождение памяти вектора учета */

#endif /* VECTOR_OPS_H */
