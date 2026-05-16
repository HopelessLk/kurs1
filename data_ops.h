/* data_ops.h - Операции с данными: детали, браки, учет */
#pragma once /* Защита от повторного включения */

#ifndef DATA_OPS_H /* Защита от повторного включения */
#define DATA_OPS_H /* Определяем макрос */

#include "structures.h" /* Подключаем определения структур */

/* === Работа с деталями === */
void showAllDetails(DetailVector *details);                           /* Просмотр всех деталей */
void addDetail(DetailVector *details);                                /* Добавление детали */
void editDetail(DetailVector *details);                               /* Редактирование детали */
void deleteDetail(DetailVector *details, RecordVector *records);      /* Удаление детали */

/* === Работа с браками === */
void showAllDefects(DefectVector *defects);                           /* Просмотр всех браков */
void addDefect(DefectVector *defects);                                /* Добавление брака */
void editDefect(DefectVector *defects);                               /* Редактирование брака */
void deleteDefect(DefectVector *defects, RecordVector *records);      /* Удаление брака */

/* === Работа с учетом === */
void showAllRecords(RecordVector *records, DetailVector *details, DefectVector *defects); /* Просмотр учета */
void addRecord(RecordVector *records, DetailVector *details, DefectVector *defects);      /* Добавление записи */
void editRecord(RecordVector *records, DetailVector *details, DefectVector *defects);     /* Редактирование */
void deleteRecord(RecordVector *records);                              /* Удаление записи учета */

/* === Поиск === */
void searchDetailsByName(DetailVector *details);                      /* Поиск деталей по названию */
void searchDetailsByMaterial(DetailVector *details);                  /* Поиск деталей по материалу */
void searchRecordsByDate(RecordVector *records, DetailVector *details, DefectVector *defects); /* По дате */

/* === Сортировка === */
void sortDetailsByName(DetailVector *details);                        /* Сортировка деталей по названию */
void sortDetailsByPrice(DetailVector *details);                       /* Сортировка деталей по цене */
void sortDetailsByWeight(DetailVector *details);                      /* Сортировка деталей по весу */
void sortRecordsByDate(RecordVector *records);                        /* Сортировка учета по дате */
void sortRecordsByQuantity(RecordVector *records);                    /* Сортировка учета по количеству */

/* === Индивидуальное задание === */
/* Вывести количество бракованных деталей за определенный период */
void countDefectsByPeriod(RecordVector *records, DetailVector *details, DefectVector *defects);

/* Проверка существования кода детали */
int isDetailCodeExists(DetailVector *details, int code);

/* Проверка существования кода брака */
int isDefectCodeExists(DefectVector *defects, int code);

/* Получение названия детали по коду */
const char* getDetailNameByCode(DetailVector *details, int code);

/* Получение вида брака по коду */
const char* getDefectTypeByCode(DefectVector *defects, int code);

#endif /* DATA_OPS_H */
