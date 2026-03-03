*This project has been created as part of the 42 curriculum by musajid.*

## Description
Philosophers is a classic computer science concurrency problem. The goal is to simulate philosophers sitting around a table, eating, thinking, and sleeping, without starving. This project explores threading, mutexes, and avoiding data races.

## Instructions
1. Run `make` to compile the `philo` executable.
2. Execute the program: `./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
   - Example: `./philo 5 800 200 200`

## Resources
- Operating Systems: Three Easy Pieces (Concurrency)
- POSIX Threads Programming
- AI was utilized as a peer-programming tool to optimize context switching delays (yielding), refine mutex locking order to prevent data races, and format code to adhere strictly to the 42 Norminette limits.