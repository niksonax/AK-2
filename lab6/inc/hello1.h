#include <linux/ktime.h>
#pragma once

struct lab6_list_head {
    struct lab6_list_head *next;
    ktime_t t_before_print;
    ktime_t t_after_print;
};

int hello_print(uint counter);
