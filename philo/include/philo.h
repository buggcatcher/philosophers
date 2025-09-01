#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>

# define PHILO_MAX 200

typedef struct s_args {
	int philo_nbr;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int times_must_eat;
} t_args;

typedef struct s_philo {
	pthread_t thread;
	int id;
	bool is_eating;
	int meals_eaten;
	size_t last_meal_time;
	size_t start_time;
	bool *dead;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *write_lock;
	pthread_mutex_t *dead_lock;
	pthread_mutex_t *meal_lock;
	t_args *args;
} t_philo;

typedef struct		s_simulation
{
	bool			is_dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
} t_simulation;


// routine
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);

// init
void 	init_args(t_args *args, char **argv);
void 	init_philos(t_philo *philos, t_simulation *simulation, pthread_mutex_t *forks, t_args *args);
void 	init_simulation(t_simulation *simulation, t_philo *philos);
void 	init_forks(pthread_mutex_t *forks, int philo_num);

// threads
int		thread_create(t_simulation *simulation, pthread_mutex_t *forks);
void	*monitoring(void *pointer);
int		parse_args(int argc, char **argv, t_args *args);
void	destroy_all(char *str, t_simulation *simulation, pthread_mutex_t *forks);

// libft & utils
int		ft_usleep(size_t microseconds);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
int		ft_isdigit(int c);
void	ft_putnbr(long n, int *count);
void	ft_putstr(char *str, int *count);
void	ft_putchar(char c, int *count);
void	print_message(char *state, t_philo *philo, int id);
size_t	get_current_time(void);

#endif
