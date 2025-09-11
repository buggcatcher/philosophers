/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:37:37 by mailinci          #+#    #+#             */
/*   Updated: 2025/09/06 16:28:55 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philosopher_is_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal_time > time_to_die
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
	int		i;

	i = 0;
	if (philos[0].args->times_must_eat == -1)
		return (0);
	while (i < philos[0].args->philo_nbr)
	{
		pthread_mutex_lock(philos[0].meal_lock);
		if (philos[i].meals_eaten < philos[0].args->times_must_eat)
		{
			pthread_mutex_unlock(philos[0].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(philos[0].meal_lock);
		i++;
	}
	pthread_mutex_lock(philos[0].dead_lock);
	*philos->dead = true;
	pthread_mutex_unlock(philos[0].dead_lock);
	return (1);
}

void	*monitoring(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (check_if_dead(philos) == 1 || check_if_full(philos) == 1)
			break ;
		if (VALGRIND)
			usleep(100);
	}
	return (pointer);
}
