#include "string_module.h"
#include <stdlib.h>
#include <stdio.h>   // для snprintf
#include <string.h>

/* Внутреннее состояние модуля */
static char** strings = NULL;   // массив указателей на строки
static size_t capacity = 0;     // текущая ёмкость массива
static size_t count = 0;        // количество сохранённых строк

char* create_string(char* str, unsigned int num) {

    size_t str_sz = strlen(str)+11; // 10 - num, 1 - \0

    // Выделяем память под строку (достаточно для "_" + до 10 цифр + '\0')
    char* new_str = malloc(str_sz * sizeof(char));
    if (!new_str) {
        return NULL;
    }

    snprintf(new_str, str_sz, "%s%u", str, num);

    return new_str;
}

char* create_string_s(char* str, unsigned int num) {

    size_t str_sz = strlen(str)+11; // 10 - num, 1 - \0

    // Выделяем память под строку (достаточно для "_" + до 10 цифр + '\0')
    char* new_str = malloc(str_sz * sizeof(char));
    if (!new_str) {
        return NULL;
    }

    snprintf(new_str, str_sz, "%s%u", str, num);

    if (strings == NULL) {
        capacity = 32;
        strings = malloc(capacity * sizeof(char*));
        if (!strings) {
            free(new_str);
            return NULL;
        }
    }
    else if (count == capacity) {
        size_t new_capacity = capacity * 2;
        char** new_ptr = realloc(strings, new_capacity * sizeof(char*));
        if (!new_ptr) {
            free(new_str);
            return NULL;
        }
        strings = new_ptr;
        capacity = new_capacity;
    }

    // Сохраняем указатель и увеличиваем счётчик элементов
    strings[count++] = new_str;
    return new_str;
}


void free_all_strings(void) {
    if (strings != NULL) {
        // Освобождаем каждую строку
        for (size_t i = 0; i < count; ++i) {
            free(strings[i]);
        }
        // Освобождаем массив указателей
        free(strings);
        // Сбрасываем состояние
        strings = NULL;
        capacity = 0;
        count = 0;
        // Счётчик номеров НЕ сбрасывается, чтобы сохранить уникальность номеров
        // при возможных последующих вызовах create_string().
        // При желании можно раскомментировать строку ниже для сброса:
        // label_cnt = 0;
    }
}