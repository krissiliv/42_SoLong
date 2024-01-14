/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:01:00 by pgober            #+#    #+#             */
/*   Updated: 2023/12/13 19:19:03 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	destr_and_null(t_mlx_data mlxdata)
{
	if (mlxdata.wallimg)
	{
		mlx_destroy_image(mlxdata.connection, mlxdata.wallimg);
		mlxdata.wallimg = NULL;
	}
	if (mlxdata.pdata.img_pers)
	{
		mlx_destroy_image(mlxdata.connection, mlxdata.pdata.img_pers);
		mlxdata.pdata.img_pers = NULL;
	}
	if (mlxdata.transp_img)
	{
		mlx_destroy_image(mlxdata.connection, mlxdata.transp_img);
		mlxdata.transp_img = NULL;
	}
	if (mlxdata.collimg)
	{
		mlx_destroy_image(mlxdata.connection, mlxdata.collimg);
		mlxdata.collimg = NULL;
	}
	if (mlxdata.exitimg)
	{
		mlx_destroy_image(mlxdata.connection, mlxdata.exitimg);
		mlxdata.exitimg = NULL;
	}
}

static void	free_and_null(void *alloc)
{
	if (alloc)
	{
		free(alloc);
		alloc = NULL;
	}
}

static void	print_error_msg(int errcode)
{
	if (errcode == 0)
		return ;
	if (errcode == 1)
		perror("Error\nCan not open/read map.\n");
	if (errcode == 2)
		perror("Error\nMap allocation failed.\n");
	if (errcode == 3)
		perror("Error\nNew window creation failed.\n");
	if (errcode == 4)
		perror("Error\nInvalid map.\n");
	return ;
}

void	finish(t_mlx_data mlxdata, int excode, int errcode)
{
	int	i;

	print_error_msg(errcode);
	i = 0;
	if (mlxdata.map.berlines)
	{
		while (mlxdata.map.berlines[i])
			free_and_null(mlxdata.map.berlines[i++]);
		free_and_null(mlxdata.map.berlines);
	}
	destr_and_null(mlxdata);
	free_and_null(mlxdata.map.collloc);
	free_and_null(mlxdata.map.wallwloc);
	free_and_null(mlxdata.map.wallsloc);
	if (mlxdata.window)
		mlx_destroy_window(mlxdata.connection, mlxdata.window);
	if (mlxdata.connection)
	{
		mlx_destroy_display(mlxdata.connection);
		free(mlxdata.connection);
	}
	exit (excode);
}
