//
// Created by 郑虎 on 15 年 August. 2..
//
/*!
 * We only need to wrap the double linked list defined in linked_list.h
 */
#ifndef C_CLI_GRAPHICS_QUEUE_H
#define C_CLI_GRAPHICS_QUEUE_H

#include "linked_list.h"

struct ccg_queue_node
{
    struct double_end_linked_list_node self;
};

#endif //C_CLI_GRAPHICS_QUEUE_H
