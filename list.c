#include "list.h"
#include <stdlib.h>

/* ---------- Инициализация ---------- */
void list_init(struct list_node **head) {
    if (head) *head = NULL;
}

/* ---------- Вставка отдельных узлов ---------- */
void list_insert_head(struct list_node **head, struct list_node *node) {
    if (!head || !node) return;
    node->next = *head;
    *head = node;
}

void list_insert_after(struct list_node *prev, struct list_node *node) {
    if (!prev || !node) return;
    node->next = prev->next;
    prev->next = node;
}

void list_insert_tail(struct list_node **head, struct list_node *node) {
    if (!head || !node) return;
    node->next = NULL;
    if (*head == NULL) {
        *head = node;
        return;
    }
    struct list_node *curr = *head;
    while (curr->next)
        curr = curr->next;
    curr->next = node;
}

/* ---------- Удаление отдельных узлов ---------- */
struct list_node* list_remove_head(struct list_node **head) {
    if (!head || !*head) return NULL;
    struct list_node *removed = *head;
    *head = removed->next;
    removed->next = NULL;
    return removed;
}

struct list_node* list_remove_after(struct list_node *prev) {
    if (!prev || !prev->next) return NULL;
    struct list_node *removed = prev->next;
    prev->next = removed->next;
    removed->next = NULL;
    return removed;
}

/* ---------- Поиск и обход ---------- */
struct list_node* list_find(struct list_node *head,
                            int (*cmp)(const struct list_node *node, const void *key),
                            const void *key) {
    if (!cmp) return NULL;
    struct list_node *curr = head;
    while (curr) {
        if (cmp(curr, key) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

void list_foreach(struct list_node *head,
                  void (*func)(struct list_node *node, void *arg),
                  void *arg) {
    if (!func) return;
    struct list_node *curr = head;
    while (curr) {
        func(curr, arg);
        curr = curr->next;
    }
}

/* ---------- Освобождение памяти ---------- */
void list_free_all(struct list_node **head) {
    if (!head) return;
    struct list_node *curr = *head;
    while (curr) {
        struct list_node *next = curr->next;
        free(curr);
        curr = next;
    }
    *head = NULL;
}

/* ---------- Вставка целого списка ---------- */
void list_splice_head(struct list_node **dst_head, struct list_node **src_head) {
    if (!dst_head || !src_head || !*src_head) return;
    struct list_node *src = *src_head;
    struct list_node *last = src;
    while (last->next)
        last = last->next;
    last->next = *dst_head;
    *dst_head = src;
    *src_head = NULL;
}

void list_splice_tail(struct list_node **dst_head, struct list_node **src_head) {
    if (!dst_head || !src_head || !*src_head) return;
    if (*dst_head == NULL) {
        *dst_head = *src_head;
    } else {
        struct list_node *tail = *dst_head;
        while (tail->next)
            tail = tail->next;
        tail->next = *src_head;
    }
    *src_head = NULL;
}

void list_splice_after(struct list_node *prev,
                       struct list_node **dst_head,
                       struct list_node **src_head) {
    if (!dst_head || !src_head || !*src_head) return;
    if (prev == NULL) {
        /* Если prev == NULL, вставляем в начало */
        list_splice_head(dst_head, src_head);
        return;
    }
    struct list_node *src = *src_head;
    struct list_node *last = src;
    while (last->next)
        last = last->next;
    last->next = prev->next;
    prev->next = src;
    *src_head = NULL;
}

/* ---------- Вырезание подсписка ---------- */
struct list_node* list_cut(struct list_node **head,
                           struct list_node *start,
                           struct list_node *end) {
    if (!head || !*head || !start || !end) return NULL;

    /* Если start — голова списка */
    if (start == *head) {
        *head = end->next;
        end->next = NULL;
        return start;
    }

    /* Ищем узел, предшествующий start */
    struct list_node *prev = *head;
    while (prev && prev->next != start)
        prev = prev->next;

    if (!prev)   /* start не найден в списке */
        return NULL;

    struct list_node *after_end = end->next;
    prev->next = after_end;
    end->next = NULL;
    return start;
}
