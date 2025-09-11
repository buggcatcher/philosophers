/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:37:02 by mailinci          #+#    #+#             */
/*   Updated: 2025/09/05 18:08:31 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg_limits(int argc, t_args *args)
{
	if (args->philo_nbr <= 0 || args->philo_nbr > PHILO_MAX)
		return (printf("Invalid philosophers number\n"), 1);
	if (args->time_to_die < 60 || args->time_to_die > INT_MAX)
		return (printf("Invalid time to die\n"), 1);
	if (args->time_to_eat < 60 || args->time_to_eat > INT_MAX)
		return (printf("Invalid time to eat\n"), 1);
	if (args->time_to_sleep < 60 || args->time_to_sleep > INT_MAX)
		return (printf("Invalid time to sleep\n"), 1);
	if (argc == 6 && (args->times_must_eat < 0
			|| args->times_must_eat > INT_MAX))
		return (printf
			("Invalid number of times each philosopher must eat\n"), 1);
	return (0);
}

static int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	if (!arg || arg[0] == '\0')
		return (1);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	validate_arguments(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philosophers <number_of_philosophers> <time_to_die>\
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		exit(1);
	}
	i = 1;
	while (i < argc)
	{
		if (check_arg_content(argv[i]))
		{
			printf("Error: Argument %d should be a number\n", i);
			exit(1);
		}
		i++;
	}
}

int	parse_args(int argc, char **argv, t_args *args)
{
	validate_arguments(argc, argv);
	args->philo_nbr = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->times_must_eat = ft_atoi(argv[5]);
	else
		args->times_must_eat = -1;
	return (check_arg_limits(argc, args));
}
