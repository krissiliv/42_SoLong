/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:26:35 by pgober            #+#    #+#             */
/*   Updated: 2023/12/13 18:38:08 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	char_check(t_mlx_data *mlxdata, int i, int *c) // locate the player, the exit and the collectibles
{
	int	j;

	j = 0;
	while (mlxdata->map.berlines[i][j] != '\0')
	{
		if (mlxdata->map.berlines[i][j] == 'E')
		{
			mlxdata->map.exit += 1;
			mlxdata->map.exloc[0] = j * mlxdata->wscale;
			mlxdata->map.exloc[1] = i * mlxdata->wscale;
		}
		if (mlxdata->map.berlines[i][j] == 'C')
		{
			mlxdata->map.collnum += 1;
			mlxdata->map.collloc[(*c)++] = j * mlxdata->wscale;
			mlxdata->map.collloc[(*c)++] = i * mlxdata->wscale;
		}
		if (mlxdata->map.berlines[i][j] == 'P')
		{
			mlxdata->map.start_pos += 1;
			mlxdata->pdata.loc_x = j * mlxdata->wscale;
			mlxdata->pdata.loc_y = i * mlxdata->wscale;
		}
		j++;
	}
}

static int	wall_surr_check(char *str, bool strt_end) // look for '1' at the beginning and the end of each line
{
	int	j;

	j = 0;
	if (str[0] != '1')
		return (-1);
	while (str[j])
		j++;
	if (str[j - 2] != '1')
		return (-1);
	j = 0;
	while (strt_end == true && str[j + 2])
	{
		if (str[j] != '1')
			return (-1);
		j++;
	}
	return (0);
}

static int	map_comp_check(t_mlx_data mlxdata) // check if the map is composed of only '0', '1', 'P', 'C', 'E' and '\n'
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (mlxdata.map.berlines[i])
	{
		j = 0;
		while (mlxdata.map.berlines[i][j])
		{
			c = mlxdata.map.berlines[i][j];
			if (c != '0' && c != '1' && c != 'P' && c != 'C' && \
				c != 'E' && c != '\n')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	map_check(t_mlx_data *mlxdata) // check if the map is valid
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	if (wall_surr_check(mlxdata->map.berlines[i], true) == -1 || \
		map_comp_check(*mlxdata) == -1)
		return (-1);
	while (mlxdata->map.berlines[i + 1])
	{
		if (ft_strlen(mlxdata->map.berlines[i]) != \
			ft_strlen(mlxdata->map.berlines[0]) || \
			wall_surr_check(mlxdata->map.berlines[i], false) == -1)
			return (-1);
		char_check(mlxdata, i, &c);
		i++;
	}
	if (ft_strlen(mlxdata->map.berlines[i]) + 1 != \
		ft_strlen(mlxdata->map.berlines[0]) || \
		mlxdata->map.start_pos != 1 || mlxdata->map.collnum == 0 || \
		mlxdata->map.exit != 1 || \
		wall_surr_check(mlxdata->map.berlines[i], true) == -1 || \
		valid_path(*mlxdata) == -1)
		return (-1); // all lines should have the same length
	return (0);
}
