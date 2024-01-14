/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:57:46 by pgober            #+#    #+#             */
/*   Updated: 2023/09/08 12:26:32 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char str)
{
	if (str == 32 || (9 <= str && str <= 13))
		return (1);
	return (0);
}

static int	is_num(char str)
{
	if ('0' <= str && str <= '9')
		return (1);
	return (0);
}

static int	is_pm(char str)
{
	if (str == '+' || str == '-')
		return (1);
	return (0);
}

static int	is_valid(char str)
{
	if (is_space(str) == 1 || is_num(str) == 1 || is_pm(str) == 1)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;

	sign = 1;
	res = 0;
	while (*nptr != '\0' && is_valid(*nptr) == 1)
	{
		while (is_space(*nptr) == 1 && is_space(*(nptr + 1)) == 1)
			nptr++;
		if (is_pm(*nptr) == 1 && is_num(*(nptr + 1)) == 0)
			return (0);
		else if (*nptr == '-')
			sign = sign * (-1);
		while (is_num(*nptr) == 1)
		{
			res = res * 10 + *nptr - '0';
			if (is_num(*(nptr + 1)) == 0)
				return (sign * res);
			nptr++;
		}
		nptr++;
	}
	return (sign * res);
}

/*int	main(void)
{
	printf("%d", ft_atoi("\t\n\r\v\fd469 \n"));
	printf("\n%d", atoi("\t\n\r\v\fd469 \n"));
}*/