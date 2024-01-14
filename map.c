/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:26:21 by pgober            #+#    #+#             */
/*   Updated: 2023/12/13 19:33:47 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	parse_map(t_mlx_data *mlxdata)
{
	int	berpath;
	int	i;

	mlxdata->map.berlines = (char **)malloc((mlxdata->win_dim[1] + 1) * \
					sizeof(char *));
	if (!mlxdata->map.berlines)
	{
		return (finish(*mlxdata, 1, 0), -1);
	}
	i = 0;
	berpath = open(mlxdata->map.path, O_RDONLY);
	if (berpath == -1)
		return (finish(*mlxdata, 1, 1), -1);
	while (i < mlxdata->win_dim[1] / mlxdata->wscale)
	{
		mlxdata->map.berlines[i] = get_next_line(berpath);
		if (!mlxdata->map.berlines[i])
			return (finish(*mlxdata, 1, 2), -1);
		i++;
	}
	mlxdata->map.berlines[i] = NULL;
	close(berpath);
	if (map_check(mlxdata) < 0)
		return (-1);
	return (0);
}

static void	set_walloc(t_mlx_data *mlxdata, int i, size_t j)
{
	int	scl;

	scl = mlxdata->wscale;
	if (mlxdata->map.berlines[i + 1] && \
			mlxdata->map.berlines[i][j] == '1' && \
			j != 0 && j != ft_strlen(mlxdata->map.berlines[i]) - 2 && \
			i != 0 && i * mlxdata->wscale != \
			mlxdata->win_dim[1] - mlxdata->wscale)
	{
		mlxdata->map.wallwloc[mlxdata->map.wallnum++] = j * scl;
		mlxdata->map.wallwloc[mlxdata->map.wallnum++] = i * scl;
	}
	else if (mlxdata->map.berlines[i][j] == '1')
	{
		mlxdata->map.wallsloc[mlxdata->map.wallsnum++] = j * scl;
		mlxdata->map.wallsloc[mlxdata->map.wallsnum++] = i * scl;
	}
}

static void	find_walls_within(t_mlx_data *mlxdata)
{
	int		i;
	size_t	j;

	i = 0;
	while (mlxdata->map.berlines[i])
	{
		j = 0;
		while (mlxdata->map.berlines[i][j])
		{
			set_walloc(mlxdata, i, j);
			j++;
		}
		i++;
	}
	mlxdata->map.wallnum /= 2;
	mlxdata->map.wallsnum /= 2;
}

static void	put_imgs(t_mlx_data *m)
{
	int	w;

	w = 0;
	while (w < 2 * m->map.wallnum)
	{
		mlx_put_image_to_window(m->connection, m->window, m->wallimg, \
		m->map.wallwloc[w], m->map.wallwloc[w + 1]);
		w += 2;
	}
	w = 0;
	while (w < 2 * m->map.wallsnum)
	{
		mlx_put_image_to_window(m->connection, m->window, \
		m->wallimg, m->map.wallsloc[w], \
		m->map.wallsloc[w + 1]);
		w += 2;
	}
	w = 0;
	while (w < 2 * m->map.collnum)
	{
		mlx_put_image_to_window(m->connection, m->window,
			m->collimg, m->map.collloc[w], \
			m->map.collloc[w + 1]);
		w += 2;
	}
}

void	put_map(t_mlx_data *mlxdata, bool pers)
{
	find_walls_within(mlxdata);
	mlxdata->wallimg = mlx_xpm_file_to_image(mlxdata->connection, \
		"./textures/wall.xpm", &mlxdata->pdata.width, &mlxdata->pdata.hight);
	if (!mlxdata->wallimg)
		return (finish(*mlxdata, 1, 0));
	mlxdata->collimg = mlx_xpm_file_to_image(mlxdata->connection, \
		"./textures/collectable.xpm", &mlxdata->pdata.width, \
		&mlxdata->pdata.hight);
	if (!mlxdata->collimg)
		return (finish(*mlxdata, 1, 0));
	mlxdata->exitimg = mlx_xpm_file_to_image(mlxdata->connection, \
		"./textures/exit.xpm", &mlxdata->pdata.width, &mlxdata->pdata.hight);
	if (!mlxdata->exitimg)
		return (finish(*mlxdata, 1, 0));
	mlxdata->pdata.img_pers = mlx_xpm_file_to_image(mlxdata->connection, \
		"./textures/smallperson.xpm", &mlxdata->pdata.width, \
		&mlxdata->pdata.hight);
	if (!mlxdata->pdata.img_pers)
		return (finish(*mlxdata, 1, 0));
	put_imgs(mlxdata);
	mlx_put_image_to_window(mlxdata->connection, mlxdata->window, \
		mlxdata->exitimg, mlxdata->map.exloc[0], mlxdata->map.exloc[1]);
	if (pers == true)
		mlx_put_image_to_window(mlxdata->connection, mlxdata->window, \
		mlxdata->pdata.img_pers, mlxdata->pdata.loc_x, mlxdata->pdata.loc_y);
}
