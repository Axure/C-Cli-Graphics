//
// Created by 郑虎 on 15 年 August. 2..
//

#include "linked_list.h"

void prefetch(const void *x) {;}

void INIT_LINKED_LIST_HEAD(struct linked_list_node *list)
{
    list->next = list;
}

void DOUBLE_END_INIT_LINKED_LIST_HEAD(struct double_end_linked_list_node *list)
{
    ((struct linked_list_node*)list)->next = (struct linked_list_node*)list;
    list->prev = list;
}

/*!
 * \fn __linked_list_add
 * \brief The internal function that adds elements inside two elements.
 *
 * Simply point the next of previous to the new, the point the next of the new to the next.
 */
void __linked_list_add(struct linked_list_node *prev, struct linked_list_node *new, struct linked_list_node *next)
{
    prev->next = new;
    new->next = next;
}

void linked_list_add_tail (struct linked_list_node *prev, struct linked_list_node *new)
{
    __linked_list_add(prev, new, prev->next);
}

void __double_end_linked_list_add(struct double_end_linked_list_node *prev, struct double_end_linked_list_node *new, struct double_end_linked_list_node *next)
{
    __linked_list_add((struct linked_list_node*)prev, (struct linked_list_node*)new, (struct linked_list_node*)next);
    new->prev = prev;
    next->prev = new;
}

void __linked_list_del(struct linked_list_node *prev, struct linked_list_node *next)
{
    prev->next = next;
}

void __linked_list_del_entry_after(struct linked_list_node *entry)
{
    __linked_list_del(entry, entry->next->next);
}

void linked_list_del_after(struct linked_list_node *entry)
{
    struct linked_list_node *next_entry = entry->next;
    __linked_list_del_entry_after(entry);
//    __linked_list_del(entry, entry->next->next);
    next_entry->next = LIST_POISON1; // Beware here, entry->next->next has changed.
}

/*
 *
 *
 */
void linked_list_del_init_after(struct linked_list_node *entry)
{
    struct linked_list_node *next_entry = entry->next;
    __linked_list_del_entry_after(entry);
    INIT_LINKED_LIST_HEAD(next_entry);
}

void __double_end_linked_list_del(struct double_end_linked_list_node *prev, struct double_end_linked_list_node *next)
{
    ((struct linked_list_node *)prev)->next = (struct linked_list_node *)next;
    next->prev = prev;
}

void __double_end_linked_list_del_entry(struct double_end_linked_list_node *entry)
{
    __double_end_linked_list_del(entry->prev, ((struct double_end_linked_list_node*) ((struct linked_list_node*) entry)->next));
}

void double_end_linked_list_del(struct double_end_linked_list_node *entry)
{
    __double_end_linked_list_del_entry(entry);
//	__double_end_linked_list_del(entry->prev, ((struct double_end_linked_list_node*) ((struct linked_list_node*) entry)->next));
    ( ( (struct linked_list_node*)entry )->next ) = LIST_POISON1;
    entry->prev = LIST_POISON2;
}

void double_end_linked_list_del_init(struct double_end_linked_list_node *entry)
{
    __double_end_linked_list_del_entry(entry);
    DOUBLE_END_INIT_LINKED_LIST_HEAD(entry);
}

