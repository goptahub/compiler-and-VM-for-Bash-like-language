#ifndef LIST_H
#define LIST_H

#include <stddef.h>   /* для offsetof */

/**
 * Базовый узел списка.
 * Все пользовательские структуры должны начинаться с поля этого типа.
 */
struct list_node {
    struct list_node *next;
};

/**
 * Получить указатель на содержащую структуру по указателю на поле list_node.
 * Параметры:
 *   ptr  – указатель на поле list_node внутри структуры
 *   type – тип содержащей структуры
 *   member – имя поля типа list_node внутри структуры
 */
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

#ifdef __cplusplus
extern "C" {
#endif

/* ---------- Инициализация ---------- */
void list_init(struct list_node **head);

/* ---------- Вставка отдельных узлов ---------- */
void list_insert_head(struct list_node **head, struct list_node *node);
void list_insert_after(struct list_node *prev, struct list_node *node);
void list_insert_tail(struct list_node **head, struct list_node *node);
#define _list_insert_tail(head, node) list_insert_tail((struct list_node **) head, (struct list_node *)node)
/* ---------- Удаление отдельных узлов ---------- */
struct list_node* list_remove_head(struct list_node **head);
struct list_node* list_remove_after(struct list_node *prev);

/* ---------- Поиск и обход ---------- */
struct list_node* list_find(struct list_node *head,
                            int (*cmp)(const struct list_node *node, const void *key),
                            const void *key);

void list_foreach(struct list_node *head,
                  void (*func)(struct list_node *node, void *arg),
                  void *arg);

/* ---------- Освобождение памяти ---------- */
void list_free_all(struct list_node **head);

/* ---------- Вставка целого списка в другой ---------- */
void list_splice_head(struct list_node **dst_head, struct list_node **src_head);
void list_splice_tail(struct list_node **dst_head, struct list_node **src_head);
void list_splice_after(struct list_node *prev,
                       struct list_node **dst_head,
                       struct list_node **src_head);

/* ---------- Вырезание подсписка ---------- */
struct list_node* list_cut(struct list_node **head,
                           struct list_node *start,
                           struct list_node *end);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */