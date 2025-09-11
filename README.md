# The Dining Philosophers Problem

## About
This project is an implementation of the **Dining Philosophers problem**, a classic exercise in computer science and operating systems.  
The problem describes a group of philosophers sitting around a table with a fork between each of them. Each philosopher alternates between **eating**, **sleeping** and **thinking**, but in order to eat they need to pick up both forks beside them.  
This scenario demonstrates the challenges of **synchronization, concurrency, and deadlock avoidance** in shared-resource systems.

## Implementation
- Written in **C**.  
- Tested with **Helgrind** (a Valgrind tool) to ensure correctness in multithreading and avoid race conditions.  
- Designed to efficiently prevent **deadlocks** and resource starvation.  

## What I Learned
By working on this project, I deepened my understanding of key concepts such as:
- Processes and threads  
- Synchronization (mutexes, semaphores)  
- Concurrency and parallelism  
- Deadlocks and starvation  
- Race conditions  
- Critical sections  
- Inter-process communication (IPC)  
- Context switching  
- Scheduling strategies  
- Thread safety  
- Resource sharing and management  

## Tests
```
./philo/philo 6 200 100 100 6 | ./visualizer/philogramm 20 -f -n
```
![6_200_100_100_6](https://raw.githubusercontent.com/buggcatcher/public/main/6_200_100_100_6.png)  

```
./philo/philo 7 400 100 100 5 | ./visualizer/philogramm 20 -f -n
```
![7_400_100_100_5](https://raw.githubusercontent.com/buggcatcher/public/main/7_400_100_100_5.png)


