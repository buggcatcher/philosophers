/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:38:08 by mailinci          #+#    #+#             */
/*   Updated: 2025/09/06 15:42:08 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo, pthread_mutex_t **first, \
						pthread_mutex_t **second)
{
	if (philo->id != philo->args->philo_nbr - 1)
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
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->right_fork;
	second = philo->left_fork;
	if (philo->id == philo->args->philo_nbr - 1)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	pthread_mutex_lock(first);
	print_message("has taken a fork", philo, philo->id);
	pthread_mutex_lock(second);
	print_message("has taken a fork", philo, philo->id);
	eating_status(philo, true);
	print_message("is eating", philo, philo->id);
	ft_usleep(philo->args->time_to_eat);
	eating_status(philo, false);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}
