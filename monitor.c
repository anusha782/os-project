#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/signal.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("You");
MODULE_DESCRIPTION("Safe CPU Monitor Module");

static struct task_struct *monitor_thread;

// Thread function
static int monitor_fn(void *data)
{
    struct task_struct *task;

    printk(KERN_INFO "Monitor thread started\n");

    while (!kthread_should_stop()) {

        for_each_process(task) {

            // ONLY target "yes" process
            if (strcmp(task->comm, "yes") == 0) {

                printk(KERN_INFO "Found yes process PID: %d\n", task->pid);

                // if it used enough CPU time
                if (task->se.sum_exec_runtime > 500000000ULL) {
                    printk(KERN_ALERT "Killing YES process PID: %d\n", task->pid);
                    send_sig(SIGKILL, task, 0);
                }
            }
        }

        ssleep(2);  // wait before next scan
    }

    printk(KERN_INFO "Monitor thread stopping\n");
    return 0;
}

// Module init
static int __init monitor_init(void)
{
    printk(KERN_INFO "Monitor module loaded\n");

    monitor_thread = kthread_run(monitor_fn, NULL, "monitor_thread");

    if (IS_ERR(monitor_thread)) {
        printk(KERN_ERR "Failed to create monitor thread\n");
        return PTR_ERR(monitor_thread);
    }

    return 0;
}

// Module exit
static void __exit monitor_exit(void)
{
    if (monitor_thread) {
        kthread_stop(monitor_thread);
    }

    printk(KERN_INFO "Monitor module unloaded\n");
}

module_init(monitor_init);
module_exit(monitor_exit);
