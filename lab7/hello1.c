/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <hello1.h>

MODULE_AUTHOR("Kanyuka Mykyta IO-81");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static struct lab6_list_head *head;
static uint ct;

int hello_print(uint counter)
{
	uint i = 0;
	//temporary pointer
	struct lab6_list_head *temp;
	
	BUG_ON(counter > 10);

	if (counter <= 0) {
		pr_warn("Parameter = %d", counter);
		return -EINVAL;
	} else if (counter >= 5 && counter <= 10) {
		pr_warn("Parameter %d. In range [5;10]", counter);
	}

	ct = counter;

	//memory for first node
	head = kmalloc(sizeof(struct lab6_list_head), GFP_KERNEL);
	temp = head;

	for (i = 0; i < counter; i++) {
		if (i == 8) {
			temp = NULL;
		}
		temp->t_before_print = ktime_get();
		pr_info("Hello World!");
		temp->t_after_print = ktime_get();
		//memory for next node
		temp->next = kmalloc(sizeof(struct lab6_list_head), GFP_KERNEL);
		
		//intialize structure (memory clear)
		temp = temp->next;
		temp->t_before_print = 0;
		temp->t_after_print = 0;
		temp->next = NULL;
	}

	pr_info("");
	return 0;
}
EXPORT_SYMBOL(hello_print);

static int __init hello_init(void)
{
	return 0;
}

static void __exit hello_exit(void)
{
	struct lab6_list_head *temp;

	while (ct != 0) {
		temp = head;
		pr_info("Print time: %lld", temp->t_after_print - temp->t_before_print);
		head = temp->next;
		kfree(temp);
		ct--;
		if (ct == 0) {
			temp = head;
			head = temp->next;
			kfree(temp);
		}
	}
	pr_info("");
}


module_init(hello_init);
module_exit(hello_exit);
