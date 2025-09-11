/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:38:19 by mailinci          #+#    #+#             */
/*   Updated: 2025/09/06 15:45:08 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

static void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while (!dead_loop(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (pointer);
}

int	create_threads(t_simulation *simulation, pthread_mutex_t *forks)
{
	pthread_t	monitor;
	int			i;

	if (pthread_create(&monitor, NULL, &monitoring, simulation->philos) != 0)
		destroy_all("error: pthread_create\n", simulation, forks);
	i = 0;
	while (i < simulation->philos[0].args->philo_nbr)
	{
		if (pthread_create(&simulation->philos[i].thread, NULL, &philo_routine,
				&simulation->philos[i]) != 0)
			destroy_all("error: pthread_create\n", simulation, forks);
		i++;
	}
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		destroy_all("error: pthread_join\n", simulation, forks);
	while (i < simulation->philos[0].args->philo_nbr)
	{
		if (pthread_join(simulation->philos[i].thread, NULL) != 0)
			destroy_all("error: pthread_join\n", simulation, forks);
		i++;
	}
	return (0);
}

void	destroy_all(char *str, t_simulation *simulation, pthread_mutex_t *forks)
{
	int	i;

	if (str)
		write(2, str, ft_strlen(str));
	pthread_mutex_destroy(&simulation->write_lock);
	pthread_mutex_destroy(&simulation->meal_lock);
	pthread_mutex_destroy(&simulation->dead_lock);
	i = 0;
	while (i < simulation->philos[0].args->philo_nbr)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
