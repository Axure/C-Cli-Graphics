//
// Created by 郑虎 on 15 年 August. 2..
//

#ifndef C_CLI_GRAPHICS_LINKED_LIST_C_H
#define C_CLI_GRAPHICS_LINKED_LIST_C_H


// TODO: you should focus on one style and write on. Make more improvements in the future. Do not expect a perfect start.
#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <sys/_types/_sigaltstack.h>

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 1
#endif

#define debug_print(fmt, ...) \
            do { if (DEBUG_TEST) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

#define container_of(ptr, type, member) ({ \
    const typeof( ((type *)0)->member ) \
    *__mptr = (ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})

#define struct_entry(ptr, type, member) \
	container_of(ptr, type, member)

void prefetch(const void *x);

/*!
 * The mysterious list end and starting point that can be directly traced in the memory.
 */
#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)

/*!
 * \struct The (singly) linked list node
 */
struct linked_list_node {
    struct linked_list_node *next; ///!< The next node in the list.
};

#define LINKED_LIST_HEAD_INIT(name) { &(name) }
#define LINKED_LIST_HEAD(name) \
	struct linked_list_node name = LIST_HEAD_INIT(name)

void INIT_LINKED_LIST_HEAD(struct linked_list_node *list);
/*!
 * The internal function that adds an element to the list
 * \param prev The pointer to the previous position.
 * \param new The pointer to the new position.
 * \param next The pointer to the next position.
 */
void __linked_list_add(struct linked_list_node *prev, struct linked_list_node *new, struct linked_list_node *next);
void linked_list_add_tail (struct linked_list_node *prev, struct linked_list_node *new);

void __linked_list_del(struct linked_list_node *prev, struct linked_list_node *next);
void __linked_list_del_entry_after(struct linked_list_node *entry);
void linked_list_del_after(struct linked_list_node *entry);
void linked_list_del_init_after(struct linked_list_node *entry);
// void __linked_list_del_entry(struct linked_list_node *entry);
// void linked_list_del(struct linked_list_node *entry);
// void linked_list_del_init(struct linked_list_node *entry);

#define linked_list_for_each(pos, head) \
for (pos = (head)->next; prefetch(pos->next), pos != (head); \
		pos = pos->next)

#define __linked_list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define linked_list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

// Imitate the Linux kernel that works. Do not try to go too far away in the beginning.
struct double_end_linked_list_node {
    struct linked_list_node linked_list_node;
    struct double_end_linked_list_node *prev;
};

#define DOUBLE_END_LINKED_LIST_HEAD_INIT(name) { &(name), &(name) }
#define DOUBLE_END_LINKED_LIST_HEAD(name) \
	struct double_end_linked_list_node name = LIST_HEAD_INIT(name)

void DOUBLE_END_INIT_LINKED_LIST_HEAD(struct double_end_linked_list_node *list);

void __double_end_linked_list_add(struct double_end_linked_list_node *prev, struct double_end_linked_list_node *new, struct double_end_linked_list_node *next);
void double_end_linked_list_add_head(struct double_end_linked_list_node *new, struct double_end_linked_list_node *next);
void double_end_linked_list_add_tail(struct double_end_linked_list_node *prev, struct double_end_linked_list_node *new);

void __double_end_linked_list_del(struct double_end_linked_list_node *prev, struct double_end_linked_list_node *next);
void __double_end_linked_list_del_entry(struct double_end_linked_list_node *entry);
void double_end_linked_list_del(struct double_end_linked_list_node *entry);
void double_end_linked_list_del_init(struct double_end_linked_list_node *entry);

#define double_end_linked_list_for_each(pos, head) \
for (pos = ((linked_list_node*)head)->next; prefetch(((linked_list_node*)pos)->next), pos != (head); \
		pos = ((linked_list_node*)pos)->next)

#define __double_end_linked_list_for_each(pos, head) \
	for (pos = ((linked_list_node*)head)->next; pos != (head); pos = ((linked_list_node*)pos)->next)

#define double_end_linked_list_for_each_safe(pos, n, head) \
	for (pos = ((linked_list_node*)head)->next, n = ((linked_list_node*)pos)->next; pos != (head); \
		pos = n, n = ((linked_list_node*)pos)->next)

struct linked_list {
    // Question: How to wrap the size into a method, instead of a variable, and remain a safe update?
    struct linked_list_node *linked_list_head;
    void (*init) (void);
};

struct double_end_linked_list {
    struct double_end_linked_list_node *double_end_linked_list_head;
    void (*init) (void);
};

void linked_list_init(struct linked_list* linked_list);
void double_end_linked_list_init(struct double_end_linked_list_node* double_end_linked_list);

struct parallel_linkded_list {

};

#endif //C_CLI_GRAPHICS_LINKED_LIST_C_H
