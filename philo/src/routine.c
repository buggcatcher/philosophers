#include "philo.h"

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
	pthread_mutex_lock(philo->right_fork);
	print_message("has taken right fork", philo, philo->id);
	if (philo->args->philo_nbr == 1)
	{
		ft_usleep(philo->args->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken left fork", philo, philo->id);
	philo->is_eating = true;
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_message("is eating", philo, philo->id);
	ft_usleep(philo->args->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->is_eating = false;
}
