/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:43:40 by pgober            #+#    #+#             */
/*   Updated: 2023/12/13 19:13:57 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	move_restr(t_mlx_data *mlxdt, char keycode)
{
	char	*instrw;
	char	*instrs;
	int		i;

	instrw = check_iswall(mlxdt, mlxdt->map.wallwloc, mlxdt->map.wallnum);
	if (!instrw)
		return (finish(*mlxdt, 1, 0), 1);
	i = 0;
	while (instrw[i] != 'x')
	{
		if (instrw[i++] == keycode)
			return (free(instrw), 1);
	}
	instrs = check_iswall(mlxdt, mlxdt->map.wallsloc, mlxdt->map.wallsnum);
	if (!instrs)
		return (free(instrw), finish(*mlxdt, 1, 0), 1);
	i = 0;
	while (instrs[i] != 'x')
	{
		if (instrs[i++] == keycode)
			return (free(instrw), free(instrs), 1);
	}
	return (free(instrw), free(instrs), 0);
}

static int	remove_collectable(t_mlx_data *mlxdata, int w)
{
	mlxdata->map.collnum -= 1;
	while (w < 2 * mlxdata->map.collnum)
	{
		mlxdata->map.collloc[w] = mlxdata->map.collloc[w + 2];
		mlxdata->map.collloc[w + 1] = mlxdata->map.collloc[w + 3];
		w += 2;
	}
	return (0);
}

static void	movement(t_mlx_data *mlxdata, char keycode)
{
	if (keycode == 'd')
		mlxdata->pdata.loc_x += mlxdata->pdata.stepsz;
	if (keycode == 'a')
		mlxdata->pdata.loc_x -= mlxdata->pdata.stepsz;
	if (keycode == 's')
		mlxdata->pdata.loc_y += mlxdata->pdata.stepsz;
	if (keycode == 'w')
		mlxdata->pdata.loc_y -= mlxdata->pdata.stepsz;
}

static int	move_person(t_mlx_data *mlxdata, char keycode)
{
	int	w;

	if (move_restr(mlxdata, keycode))
		return (0);
	w = 0;
	while (w + 2 <= 2 * mlxdata->map.collnum)
	{
		if ((mlxdata->pdata.loc_x == mlxdata->map.collloc[w] && \
			mlxdata->pdata.loc_y == mlxdata->map.collloc[w + 1]))
			remove_collectable(mlxdata, w);
		w += 2;
	}
	if (!(mlxdata->pdata.loc_x == mlxdata->map.exloc[0] && \
		mlxdata->pdata.loc_y == mlxdata->map.exloc[1]))
		mlx_put_image_to_window(mlxdata->connection, mlxdata->window, \
		mlxdata->transp_img, mlxdata->pdata.loc_x, mlxdata->pdata.loc_y);
	else
		mlx_put_image_to_window(mlxdata->connection, mlxdata->window, \
		mlxdata->exitimg, mlxdata->pdata.loc_x, mlxdata->pdata.loc_y);
	movement(mlxdata, keycode);
	mlx_put_image_to_window(mlxdata->connection, mlxdata->window, \
		mlxdata->pdata.img_pers, mlxdata->pdata.loc_x, mlxdata->pdata.loc_y);
	mlxdata->movenum++;
	ft_printf("\rMove #: %d", mlxdata->movenum);
	return (0);
}

int	input_processing(int keycode, t_mlx_data *mlxdata)
{
	if (keycode == 65307)
		return (finish(*mlxdata, 0, 0), 1);
	if (mlxdata->pdata.loc_x == mlxdata->map.exloc[0] && \
		mlxdata->pdata.loc_y == mlxdata->map.exloc[1] && \
		mlxdata->map.collnum == 0)
		return (finish(*mlxdata, 0, 0), 1);
	if (keycode == 100)
		return (move_person(mlxdata, 'd'));
	if (keycode == 97)
		return (move_person(mlxdata, 'a'));
	if (keycode == 119)
		return (move_person(mlxdata, 'w'));
	if (keycode == 115)
		return (move_person(mlxdata, 's'));
	return (0);
}
