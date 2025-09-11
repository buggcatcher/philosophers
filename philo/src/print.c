/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:37:50 by mailinci          #+#    #+#             */
/*   Updated: 2025/09/06 17:28:50 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_args args)
{
	printf("%d 1 has taken a fork\n", 0);
	ft_usleep(args.time_to_die);
	printf("%d 1 died\n", args.time_to_die);
	return ;
}

// static void	ft_vcheck(const char v, va_list ptr, int *c)
// {
// 	if (v == 'd')
// 		ft_putnbr(va_arg(ptr, long), c);
// 	else if (v == 's')
// 		ft_putstr(va_arg(ptr, char *), c);
// }

// int	print_state(const char *str, ...)
// {
// 	va_list	ptr;
// 	int		i;
// 	int		c;

// 	i = 0;
// 	c = 0;
// 	va_start(ptr, str);
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '%')
// 		{
// 			ft_vcheck(str[i + 1], ptr, &c);
// 			i++;
// 		}
// 		else
// 			ft_putchar(str[i], &c);
// 		i++;
// 	}
// 	va_end(ptr);
// 	return (c);
// }

void	print_message(char *state, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->dead_lock);
	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!(*philo->dead))
		printf("%zu %d %s\n", time, id, state);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_unlock(philo->dead_lock);
}
