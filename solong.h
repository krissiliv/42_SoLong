/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:25:57 by pgober            #+#    #+#             */
/*   Updated: 2023/12/13 19:20:02 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include <complex.h>
# include <fcntl.h>
# include <unistd.h>
# include "ft_printf/ft_printf.h"
# include "getnextline/get_next_line.h"
# include <stdbool.h>
# include <mlx.h>

typedef struct s_person
{
	void	*img_pers;
	int		stepsz;
	int		width;
	int		hight;
	int		loc_x;
	int		loc_y;
}	t_person;

typedef struct s_map
{
	char	*path;
	char	**berlines;
	int		chcoll;
	int		chex; // check exitnum (should be 1)
	int		exit;
	int		start_pos;
	int		*collloc; // collectibles location
	int		collnum;
	int		*wallwloc; // walls within (inside walls) location
	int		wallnum; // within walls number
	int		*wallsloc; // surrounding walls location
	int		wallsnum; // surrounding walls number
	int		exloc[2]; // exit location
}	t_map;

typedef struct s_mlx_data
{
	void		*connection;
	void		*window;
	int			win_dim[2]; // set in map_getdim
	int			wscale;
	t_map		map;
	t_person	pdata;
	void		*transp_img;
	void		*wallimg;
	void		*collimg;
	void		*exitimg;
	int			movenum; // number of movements of player (displayed in terminal)
}	t_mlx_data;

typedef unsigned char	t_byte;

// input processing
int		input_processing(int keycode, t_mlx_data *mlxdata);

// input processing 2
int		close_window(t_mlx_data *mlxdata);
char	*check_iswall(t_mlx_data *mlxdt, int *wall, int wallnum);

// map
int		parse_map(t_mlx_data *mlxdata);
void	put_map(t_mlx_data *mlxdata, bool pers);

// map_check
int		map_check(t_mlx_data *mlxdata);

//valid path
int		*set_coll_check(t_mlx_data mlxdata, int px, int py, int *chcoll);
int		valid_path(t_mlx_data mlxdata);

// map get dim
void	map_getdim(t_mlx_data *mlxdata);

//finish
void	finish(t_mlx_data mlxdata, int excode, int errcode);

// math
int		abs(int i);

#endif
