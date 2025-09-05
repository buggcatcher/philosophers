#include "philo.h"

static void	take_forks(t_philo *philo, pthread_mutex_t **first, pthread_mutex_t **second)
{
	if (philo->id % 2 == 1)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	else
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
}

static void	eating_status(t_philo *philo, bool status)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->is_eating = status;
	if (status)
	{
		philo->last_meal_time = get_current_time();
		philo->meals_eaten++;
	}
	pthread_mutex_unlock(philo->meal_lock);
}

void	philo_think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	philo_sleep(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->args->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;

	take_forks(philo, &first, &second);
	pthread_mutex_lock(first);
	print_message("has taken a fork", philo, philo->id);
	if (philo->args->philo_nbr == 1)
	{
		ft_usleep(philo->args->time_to_die);
		pthread_mutex_unlock(first);
		return ;
	}
	pthread_mutex_lock(second);
	print_message("has taken a fork", philo, philo->id);
	eating_status(philo, true);
	print_message("is eating", philo, philo->id);
	ft_usleep(philo->args->time_to_eat);
	eating_status(philo, false);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}
 