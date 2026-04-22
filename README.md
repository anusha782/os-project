# OS Jackfruit – Lightweight Container Engine with Kernel Monitoring

## 📌 Overview

This project implements a **lightweight container engine** along with a **Linux kernel module** for process monitoring and resource control.

The system demonstrates core Operating System concepts including:

* Process creation and isolation
* Filesystem-based containerization
* Kernel-level monitoring
* CPU and memory resource management

---

## 🧠 Key Concepts

### 🔹 Containerization

Containers are implemented as **isolated processes** using separate filesystem roots (`rootfs`). Each container runs independently while sharing the host kernel.

### 🔹 Filesystem Isolation

A minimal Linux filesystem (Alpine rootfs) is used to create isolated environments for each container.

### 🔹 Kernel Module Monitoring

A custom kernel module (`monitor.ko`) tracks running processes and enforces resource limits.

### 🔹 Resource Control

Processes exceeding CPU or memory limits are automatically terminated.

---

## ⚙️ Project Structure

```
boilerplate/
 ├── engine.c        # Container engine implementation
 ├── monitor.c       # Kernel module for monitoring
 ├── memory_hog.c    # Memory stress test program
 ├── Makefile
run_all.sh           # Script to run full workflow
test.sh              # Testing script
README.md
```

---

## 🚀 How It Works

### 1. Setup Filesystem (Container Base)

```bash
tar -xzf alpine-minirootfs.tar.gz -C rootfs-base
cp -a rootfs-base rootfs-alpha
cp -a rootfs-base rootfs-beta
```

👉 Creates isolated filesystem environments for containers.

---

### 2. Compile Container Engine

```bash
gcc engine.c -o engine
```

👉 Builds the container runtime.

---

### 3. Run a Container

```bash
sudo ./engine start alpha ./rootfs-alpha /bin/bash
```

👉 Starts a container named `alpha` with its own filesystem.

---

### 4. Run Multiple Containers

```bash
sudo ./engine start c1 ./rootfs-alpha /bin/bash
sudo ./engine start c2 ./rootfs-alpha /bin/bash
```

👉 Each container runs as a separate process.

---

### 5. Verify Processes

```bash
ps aux | grep bash
```

👉 Shows multiple bash processes (one per container).

---

### 6. Run Commands Inside Container

```bash
sudo ./engine start logtest ./rootfs-alpha /bin/ls
cat container.log
```

👉 Executes a command inside container and logs output.

---

## 🔍 Process Monitoring

### Create CPU Load

```bash
yes > /dev/null &
```

👉 Creates a CPU-intensive process.

---

### Check CPU Usage

```bash
ps aux | grep yes
```

👉 Shows high CPU usage (~100%).

---

## 🧩 Kernel Module

### Load Module

```bash
sudo insmod monitor.ko
```

### Remove Module

```bash
sudo rmmod monitor
```

### View Logs

```bash
dmesg | tail
```

---

## ⚠️ Resource Control

### Memory Stress Test

```bash
./memory_hog
```

👉 Continuously allocates memory.

---

### Kernel Behavior

* **Soft Limit Exceeded**

  * Warning generated
* **Hard Limit Exceeded**

  * Process is terminated

Example:

```
Soft limit exceeded for PID: XXXX
Hard limit exceeded! Killing PID: XXXX
```

---

## 🧹 Cleanup

```bash
killall yes
killall memory_hog
sudo rmmod monitor
ps aux | grep yes
lsmod | grep monitor
```

👉 Ensures no processes or modules remain.

---

## 🎯 Key Features

* Lightweight container engine in C
* Filesystem-based isolation
* Kernel-level process monitoring
* Automatic CPU and memory control
* Logging and verification using system tools

---

## 📊 Concepts Demonstrated

* Process Management
* Resource Management
* Kernel Modules
* Filesystem Isolation
* Basic Containerization

---


---

## 🎤 Conclusion

This project demonstrates how containers can be implemented as isolated processes and how the Linux kernel can be extended to monitor and control system resources effectively.

---
