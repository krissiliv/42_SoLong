/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:25:45 by pgober            #+#    #+#             */
/*   Updated: 2023/12/13 18:29:13 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	init_mlxdata(t_mlx_data *mlxdata)
{
	mlxdata->win_dim[0] = 0;
	mlxdata->win_dim[1] = 0;
	mlxdata->map.wallnum = 0;
	mlxdata->map.wallsnum = 0;
	mlxdata->map.collnum = 0;
	mlxdata->map.exit = 0;
	mlxdata->map.start_pos = 0;
	mlxdata->map.berlines = NULL;
	mlxdata->wallimg = NULL;
	mlxdata->pdata.img_pers = NULL;
	mlxdata->collimg = NULL;
	mlxdata->exitimg = NULL;
	mlxdata->map.collloc = NULL;
	mlxdata->map.wallwloc = NULL;
	mlxdata->map.wallsloc = NULL;
	mlxdata->window = NULL;
	mlxdata->wallimg = NULL;
	mlxdata->pdata.img_pers = NULL;
	mlxdata->collimg = NULL;
	mlxdata->exitimg = NULL;
	mlxdata->transp_img = mlx_xpm_file_to_image(mlxdata->connection,
			"./textures/transparent.xpm",
			&mlxdata->pdata.width, &mlxdata->pdata.hight);
	if (!mlxdata->transp_img)
		return (finish(*mlxdata, 1, 0));
}

static void	initialize(t_mlx_data *mlxdata)
{
	init_mlxdata(mlxdata);
	map_getdim(mlxdata);
	if (mlxdata->win_dim[0] == 0)
		return (finish(*mlxdata, 1, 1));
	mlxdata->wscale = mlxdata->pdata.width;
	mlxdata->map.collloc = (int *)malloc((mlxdata->win_dim[0] * \
			mlxdata->win_dim[1]) * 2 * sizeof(int));
	if (!mlxdata->map.collloc)
		return (finish(*mlxdata, 1, 2));
	mlxdata->map.wallwloc = (int *)malloc((mlxdata->win_dim[0] * \
			mlxdata->win_dim[1]) * 2 * sizeof(int));
	if (!mlxdata->map.wallwloc)
		return (finish(*mlxdata, 1, 2));
	mlxdata->map.wallsloc = (int *)malloc((mlxdata->win_dim[0] * \
			mlxdata->win_dim[1]) * 6 * sizeof(int));
	if (!mlxdata->map.wallsloc)
		return (finish(*mlxdata, 1, 2));
	mlxdata->win_dim[0] *= mlxdata->wscale;
	mlxdata->win_dim[1] *= mlxdata->wscale;
	mlxdata->pdata.stepsz = mlxdata->pdata.width;
}

int	main(int argc, char **argv)
{
	t_mlx_data	mlxdata;

	if (argc != 2 || \
	ft_strncmp(argv[argc - 1] + ft_strlen(argv[argc - 1]) - 4, ".ber", 4) != 0)
	{
		perror("Error\n(Only) .ber file needed as argument.\n");
		exit(1);
	}
	mlxdata.map.path = argv[argc - 1];
	mlxdata.connection = mlx_init();
	if (mlxdata.connection == NULL)
		return (1);
	mlxdata.movenum = 0;
	initialize(&mlxdata);
	if (parse_map(&mlxdata) < 0)
		return (finish(mlxdata, 1, 4), 1);
	mlxdata.window = mlx_new_window(mlxdata.connection,
			mlxdata.win_dim[0], mlxdata.win_dim[1], "Pia's Game");
	if (mlxdata.window == NULL)
		return (finish(mlxdata, 1, 3), 1);
	put_map(&mlxdata, true);
	mlx_key_hook(mlxdata.window, input_processing, &mlxdata);
	mlx_hook(mlxdata.window, 17, 0, close_window, &mlxdata);
	mlx_loop(mlxdata.connection);
	return (finish(mlxdata, 0, 0), 0);
}
