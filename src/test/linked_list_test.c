#include "../lib/linked_list.h"
#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct linked_list_node list;
    int num;
};

int main(int argc, char const *argv[])
{
    int i;
    struct node *tem;
    struct linked_list_node *pos, *n;

    struct node mylist;
    INIT_LINKED_LIST_HEAD(&mylist.list);

    for (i = 0; i < 10; ++i)
    {
        tem = (struct node*)malloc(sizeof(struct node));
        tem->num = i;
        linked_list_add_tail(&(mylist.list), &(tem->list));
    }

    linked_list_for_each(pos, &mylist.list)
    {
        tem = struct_entry(pos, struct node, list);
        printf("%d", tem->num);
    }

    printf("\n");

    typedef int BOOL;
#define TRUE 1
#define FALSE 0
    BOOL delete_after;
    delete_after = FALSE;

    struct linked_list_node * prev = NULL;
    linked_list_for_each_safe(pos, n, &mylist.list)
    {
        tem = struct_entry(pos, struct node, list);
        printf("%d\n", tem->num);
//		if (tem->num == 5)
//		{
//			//
//			delete_after = TRUE;
//		}
//		if (delete_after == TRUE) {
//			printf("Fucked!");
//			linked_list_del_after(pos);
//			delete_after = FALSE;
//		}

        if (tem->num == 5)
        {
            free(prev->next);
            linked_list_del_after(prev);
            printf("Fucked!");
//			debug_print("Fcuked%d", 1);
        }

        prev = pos;
    }

    linked_list_for_each(pos, &mylist.list)
    {
        tem = struct_entry(pos, struct node, list);
        printf("%d", tem->num);
    }

    linked_list_for_each_safe(pos, n, &mylist.list)
    {
        tem = struct_entry(pos, struct node, list);

    }

    return 0;
}