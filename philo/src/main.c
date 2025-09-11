/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:37:30 by mailinci          #+#    #+#             */
/*   Updated: 2025/09/06 17:28:28 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args			args;
	t_simulation	simulation;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (parse_args(argc, argv, &args))
		return (1);
	if (args.philo_nbr == 1)
		one_philo(args);
	else
	{
		init_simulation(&simulation, philos);
		init_forks(forks, args.philo_nbr);
		init_philos(philos, &simulation, forks, &args);
		create_threads(&simulation, forks);
		destroy_all(NULL, &simulation, forks);
	}
	return (0);
}
