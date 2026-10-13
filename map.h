// Map.h
#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include <stdbool.h>

typedef long long MAP_VALUE_T;

typedef enum {
    JUST_ADD,
    SUBSTITUTE_ADD,
    NOT_EXIST_ADD
} AddType;

// Элемент: пара (строка, число)
typedef struct {
    char *key;      // указатель на строку (владеет памятью)
    MAP_VALUE_T value;
} KeyValuePair;

// Структура динамического массива элементов
typedef struct {
    KeyValuePair *items;   // указатель на массив пар
    size_t capacity;       // текущая ёмкость массива
    size_t size;           // количество заполненных элементов
    AddType addType;
} Map;

// Инициализация пустой структуры
void map_init(Map *map, AddType which_add);

// Добавить или обновить элемент по строке
void _map_add(Map *map, const char *key, MAP_VALUE_T value);
#define map_add(map, key, value) _map_add(map, key, (MAP_VALUE_T)value)

// Получить число по строке.
// Возвращает true, если ключ найден, и записывает значение в *out.
// Иначе возвращает false.
bool _map_get(const Map *map, const char *key, MAP_VALUE_T *out);
#define map_get(map, key, value) _map_get(map, key, (MAP_VALUE_T*)value)

// Освободить всю память, занимаемую структурой
void map_free(Map *map, bool free_values);

#endif // MAP_H