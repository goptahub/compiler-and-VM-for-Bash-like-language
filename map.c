#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Инициализация пустой структуры
void map_init(Map *map, AddType which_add) {
    map->items = NULL;
    map->capacity = 0;
    map->size = 0;
    map->addType = which_add;
}

// Внутренняя функция: увеличение ёмкости при необходимости
static void map_reserve(Map *map, size_t additional) {
    if (map->size + additional > map->capacity) {
        size_t new_capacity = map->capacity == 0 ? 4 : map->capacity * 2;
        while (new_capacity < map->size + additional) {
            new_capacity *= 2;
        }
        KeyValuePair *new_items = realloc(map->items, new_capacity * sizeof(KeyValuePair));
        if (!new_items) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            exit(EXIT_FAILURE);
        }
        map->items = new_items;
        map->capacity = new_capacity;
    }
}

// Добавить или обновить элемент по ключу
void _map_add(Map *map, const char *key, MAP_VALUE_T value) {
    // Сначала проверим, существует ли уже такой ключ
    if (map->addType == SUBSTITUTE_ADD)
    {
        for (size_t i = 0; i < map->size; ++i) {
            if (strcmp(map->items[i].key, key) == 0) {
                // Обновляем значение существующего элемента
                map->items[i].value = value;
                return;
            }
        }
    }
    else if (map->addType == NOT_EXIST_ADD)
    {
        for (size_t i = 0; i < map->size; ++i) {
            if (strcmp(map->items[i].key, key) == 0) {
                // НЕ Обновляем значение существующего элемента
                return;
            }
        }
    }

    // Ключа нет — добавляем новый элемент
    map_reserve(map, 1);

    // Копируем строку
    char *key_copy = malloc(strlen(key) + 1);
    if (!key_copy) {
        fprintf(stderr, "Ошибка выделения памяти для строки\n");
        exit(EXIT_FAILURE);
    }
    strcpy(key_copy, key);

    map->items[map->size].key = key_copy;
    map->items[map->size].value = value;
    map->size++;
}

// Получить значение по строке. Возвращает true, если ключ найден,
// и записывает значение в *out. Иначе возвращает false.
bool _map_get(const Map *map, const char *key, MAP_VALUE_T *out) {
    for (size_t i = 0; i < map->size; ++i) {
        if (strcmp(map->items[i].key, key) == 0) {
            *out = map->items[i].value;
            return true;
        }
    }
    return false;
}

// Освободить всю память, занимаемую структурой
void map_free(Map *map, bool free_values) {
    if (free_values) {
        for (size_t i = 0; i < map->size; ++i) {
            free(map->items[i].key);
            free((void*)map->items[i].value);
        }
    }
    else {
        for (size_t i = 0; i < map->size; ++i) {
            free(map->items[i].key);
        }
    }
    free(map->items);
    map->items = NULL;
    map->capacity = 0;
    map->size = 0;
}


// ------------------------ Пример использования ------------------------
// int main(void) {
//     Map map;
//     map_init(&map);

//     map_add(&map, "apple", 10);
//     map_add(&map, "banana", 20);
//     map_add(&map, "cherry", 30);
//     map_add(&map, "apple", 99);  // обновляет значение для "apple"

//     int value;
//     if (map_get(&map, "apple", &value)) {
//         printf("apple -> %d\n", value);   // 99
//     } else {
//         printf("apple not found\n");
//     }

//     if (map_get(&map, "banana", &value)) {
//         printf("banana -> %d\n", value);  // 20
//     }

//     if (map_get(&map, "date", &value)) {
//         printf("date -> %d\n", value);
//     } else {
//         printf("date not found\n");
//     }

//     map_free(&map);
//     return 0;
// }

