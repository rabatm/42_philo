# 42_philo: Philosophers
!GitHub

42_philo is a project from École 42 that delves into multi-threading and multi-process programming. It simulates a twist on the famous Dining Philosophers problem, where philosophers sit around a circular table, either eating, thinking, or sleeping.

## Project Overview
### Objective: 
Simulate the behavior of philosophers sitting at a round table with a large bowl of spaghetti in the center.
### Rules:
Philosophers can perform three actions: eating, thinking, or sleeping. \
Each philosopher must eat with two forks (one for each hand). \
Philosophers must never be starving. \
The simulation stops when a philosopher dies. \
options: \
**number_of_philosophers**: The number of philosophers (also the number of forks). \
**time_to_die**: Time in milliseconds; if a philosopher doesn’t start eating within this time after their last meal or the beginning of the simulation, they die. \
**time_to_eat**: Time in milliseconds for a philosopher to eat (while holding both forks). \
**time_to_sleep**: Time in milliseconds for a philosopher to sleep. \

### Installation
Clone the repository:
```
git clone https://github.com/rabatm/42_philo.git
cd 42_philo
```

Compile :
```
make philo_one
```

## License
42_philo is licensed under MIT License. See LICENSE for full details.

## Authors
rabatm - https://github.com/rabatm

Please note that all functions are created in accordance with the Norm – a set of rules governing code formatting at École 42. \
Happy philosophizing! 🍝🔍
