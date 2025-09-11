/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:37:11 by mailinci          #+#    #+#             */
/*   Updated: 2025/09/05 20:36:14 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_simulation *simulation,
					pthread_mutex_t *forks, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_nbr)
	{
		philos[i].id = i + 1;
		philos[i].is_eating = false;
		philos[i].meals_eaten = 0;
		philos[i].args = args;
		philos[i].start_time = get_current_time();
		philos[i].last_meal_time = get_current_time();
		philos[i].write_lock = &simulation->write_lock;
		philos[i].dead_lock = &simulation->dead_lock;
		philos[i].meal_lock = &simulation->meal_lock;
		philos[i].dead = (bool *)&simulation->is_dead;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[args->philo_nbr - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_simulation(t_simulation *simulation, t_philo *philos)
{
	simulation->is_dead = false;
	simulation->philos = philos;
	pthread_mutex_init(&simulation->write_lock, NULL);
	pthread_mutex_init(&simulation->dead_lock, NULL);
	pthread_mutex_init(&simulation->meal_lock, NULL);
}
