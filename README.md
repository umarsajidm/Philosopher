*This project has been created as part of the 42 curriculum by musajid.*

# Philosophers

## Description
Philosophers is a classic computer science concurrency problem based on the **Dining Philosophers problem**. The goal of the project is to simulate philosophers sitting around a table who alternate between thinking, eating, and sleeping.

Each philosopher needs two forks to eat, which are shared resources between neighboring philosophers. The challenge is to coordinate access to these forks using **threads and mutexes** while preventing:
- **Deadlocks**
- **Data races**
- **Starvation**

This project introduces practical concepts of **multithreading**, **synchronization**, and **concurrency control** using POSIX threads.

---

## Instructions

### Compilation
Run the following command to compile the project:

```bash
make
