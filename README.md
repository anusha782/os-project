# OS Project: Multi-Container Runtime with Kernel Monitoring

## 📌 Overview
This project implements a simplified container runtime in user space along with a kernel module for resource monitoring. It demonstrates concepts such as namespaces, process isolation, inter-process communication (IPC), and kernel-level memory monitoring.

---

## ⚙️ Features

### 🟢 Task 1: Multi-Container Runtime
- Supports launching multiple containers
- Uses Linux namespaces (PID, UTS, Mount)
- Root filesystem isolation using provided rootfs
- Basic supervisor functionality

---

### 🟢 Task 2: CLI + IPC
- `start` command to launch containers
- `ps` command to list running containers
- `stop` command to terminate containers
- Basic IPC simulation between supervisor and container

---

### 🟢 Task 3: Logging System
- Container output redirected to `container.log`
- Logs include command execution output
- Persistent logging for debugging

---

### 🟢 Task 4: Kernel Memory Monitor
- Kernel module tracks process memory usage (RSS)
- Soft limit warning when memory exceeds threshold
- Hard limit enforcement by killing process
- Logs available via `dmesg`

---

### 🟢 Task 5: Scheduling Experiments
- CPU-intensive workloads (`yes` command)
- Observed scheduling behavior using `top`
- Compared processes with different priorities (`nice`)

---

### 🟢 Task 6: Cleanup
- Proper unloading of kernel module
- No leftover processes after execution
- Verified using `ps` and `lsmod`

---

## 🛠️ Build Instructions

### Compile user-space program
```bash
gcc engine.c -o engine
