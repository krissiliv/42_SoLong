/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_getdim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:01:25 by pgober            #+#    #+#             */
/*   Updated: 2023/12/13 18:24:12 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	check_len(t_mlx_data *mlxdata, int len, int berpath)
{
	if (len <= 0)
	{
		close(berpath);
		return (finish(*mlxdata, 1, 1));
	}
}

void	map_getdim(t_mlx_data *mlxdata)
{
	int		berpath;
	int		len;
	int		helper;
	char	berchar[1];

	berpath = open(mlxdata->map.path, O_RDONLY);
	if (berpath == -1)
		return (finish(*mlxdata, 1, 1));
	helper = 0;
	len = read(berpath, berchar, 1);
	check_len(mlxdata, len, berpath);
	while (len != 0)
	{
		helper++;
		if (berchar[0] == '\n')
		{
			mlxdata->win_dim[0] = (helper - 1);
			helper = 0;
			mlxdata->win_dim[1]++;
		}
		len = read(berpath, berchar, 1);
	}
	mlxdata->win_dim[1]++;
	close(berpath);
}
