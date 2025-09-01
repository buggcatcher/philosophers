#include "philo.h"

static bool	philosopher_is_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal_time >= time_to_die
		&& philo->is_eating == false)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

static int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].args->philo_nbr)
	{
		if (philosopher_is_dead(&philos[i], philos[i].args->time_to_die))
		{
			print_message("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = true;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_if_full(t_philo *philos)
{
	int	i;
	bool	full;

	i = 0;
	full = false;
	if (philos[0].args->times_must_eat == -1)
		return (0);
	while (++i < philos[0].args->philo_nbr)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].args->times_must_eat)
			full = true;
		pthread_mutex_unlock(philos[i].meal_lock);
	}
	if (full == true)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = true;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitoring(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philos) == 1 || check_if_full(philos) == 1)
			break ;
	return (pointer);
}

