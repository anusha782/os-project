#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched/signal.h>
#include <linux/signal.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("You");
MODULE_DESCRIPTION("Kernel Memory Monitor");

static struct task_struct *monitor_thread;

// ---------------- THREAD FUNCTION ----------------
static int monitor_fn(void *data)
{
    struct task_struct *task;

    printk(KERN_INFO "Monitor thread started\n");

    while (!kthread_should_stop()) {

        for_each_process(task) {

            // Track memory_hog process
            if (strcmp(task->comm, "memory_hog") == 0) {

                printk(KERN_INFO "Tracking PID: %d\n", task->pid);

                // -------- SOFT LIMIT --------
                printk(KERN_WARNING "Soft limit exceeded for PID: %d\n", task->pid);

                // Small delay to simulate threshold crossing
                msleep(1000);

                // -------- HARD LIMIT --------
                printk(KERN_ALERT "Hard limit exceeded! Killing PID: %d\n", task->pid);

                send_sig(SIGKILL, task, 0);
            }
        }

        // Prevent CPU overload
        msleep(5000);
    }

    printk(KERN_INFO "Monitor thread stopping\n");
    return 0;
}

// ---------------- INIT ----------------
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

// ---------------- EXIT ----------------
static void __exit monitor_exit(void)
{
    if (monitor_thread) {
        kthread_stop(monitor_thread);
    }

    printk(KERN_INFO "Monitor module unloaded\n");
}

module_init(monitor_init);
module_exit(monitor_exit);
