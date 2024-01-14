/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:27:45 by pgober            #+#    #+#             */
/*   Updated: 2023/12/13 11:44:13 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == 0 && src == 0)
	{
		if (src)
			free((char *)src);
		if (dest)
			free((char *)dest);
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

/*int	main(void)
{
	char	src[] = "Hello world!!";
	char	dest[100];
	
	ft_memcpy(dest, src, 0);
	printf("src: %p\n", src);
	printf("dest: %p\n", dest);


	char    src2[] = "Hello world!!";
    char    dest2[100];

    memcpy(dest2, src2, 0);
    printf("src: %p\n", src2);
    printf("dest: %p\n", dest2);
}*/
