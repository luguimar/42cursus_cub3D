/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:42:47 by jduraes-          #+#    #+#             */
/*   Updated: 2023/11/09 18:45:23 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int		i;
	long	nr;
	long	sign;

	i = 0;
	nr = 0;
	sign = 1;
	while (str[i] && str[i] == 32)
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		nr = nr * 10 + str[i] - '0';
		i++;
	}
	return (nr * sign);
}
