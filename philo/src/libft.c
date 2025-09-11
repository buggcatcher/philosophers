/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:37:18 by mailinci          #+#    #+#             */
/*   Updated: 2025/09/01 17:50:11 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_putchar(char ch, int *c)
{
	write(1, &ch, 1);
	(*c)++;
}

void	ft_putstr(char *str, int *c)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		*c += 6;
		return ;
	}
	while (str[i] != '\0')
	{
		ft_putchar(str[i], c);
		i++;
	}
}

void	ft_putnbr(long n, int *c)
{
	if (n < 0)
	{
		ft_putchar('-', c);
		n = -n;
	}
	if (n < 10)
		ft_putchar((char)(n + '0'), c);
	else
	{
		ft_putnbr(n / 10, c);
		ft_putnbr(n % 10, c);
	}
}

int	ft_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 43)
		i++;
	else if (str[i] == 45)
	{
		sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result *= sign);
}
