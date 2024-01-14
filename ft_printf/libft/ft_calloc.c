/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:46:22 by pgober            #+#    #+#             */
/*   Updated: 2023/12/13 11:29:43 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	str = (char *)malloc(nmemb * size);
	if (!str)
		return (NULL);
	if (((long int)size * nmemb) > 2147483647)
		return (free(str), NULL);
	ft_bzero(str, size * nmemb);
	return (str);
}

/*int main(void)
{
	char str[] = "Hello";
	char *astr;
	char *astr2;

	astr = ft_calloc(ft_strlen(str), 0); // sizeof(char));
	astr2 = calloc(ft_strlen(str), 0); //sizeof(char));
	free(astr);
	free(astr2);
}*/
