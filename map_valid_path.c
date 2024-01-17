/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:00:30 by pgober            #+#    #+#             */
/*   Updated: 2023/12/13 18:14:05 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	search_path_rec(char **berlines, t_mlx_data mlxdata, int px, int py)
{
	char	curr;

	if (berlines == NULL || berlines[0] == NULL)
		return (finish(mlxdata, 1, 0));
	curr = berlines[py][px];
	if (curr == 'P' || curr == '0') //put '1' for 'already visited'
		berlines[py][px] = '1';
	else if (curr == 'C')
	{
		mlxdata.map.chcoll += 1; // add i to the number of collected collectibles
		berlines[py][px] = '1'; // put '1' for 'already visited'
	}
	else if (curr == 'E')
	{
		mlxdata.map.chex += 1;
		berlines[py][px] = '1';
	}
	else
		return ;
	search_path_rec(berlines, mlxdata, px + 1, py); // search in all directions
	search_path_rec(berlines, mlxdata, px - 1, py);
	search_path_rec(berlines, mlxdata, px, py + 1);
	search_path_rec(berlines, mlxdata, px, py - 1);
}

static char	**berlines_dup(t_mlx_data mlxdata) // duplicate lines of .ber file to not overwrite the original during path search
{
	char	**berl_dup;
	int		i;

	i = 0;
	while (mlxdata.map.berlines[i] != NULL)
		i++;
	if (i == 0)
		return (NULL);
	berl_dup = (char **)malloc((i + 1) * sizeof(char *));
	if (!berl_dup)
		return (finish(mlxdata, 1, 0), NULL);
	berl_dup[i] = NULL;
	i = 0;
	while (mlxdata.map.berlines[i] != NULL)
	{
		berl_dup[i] = ft_strdup(mlxdata.map.berlines[i]);
		if (!berl_dup[i])
		{
			return (free(berl_dup), finish(mlxdata, 1, 0), NULL);
		}
		i++;
	}
	return (berl_dup);
}

static void	free_berl_dup(char **berl)
{
	int	i;

	i = 0;
	while (berl[i] != NULL)
	{
		free(berl[i]);
		i++;
	}
	free(berl);
}

int	valid_path(t_mlx_data mlxdata)
{
	int		px;
	int		py;
	char	**berlines;

	berlines = berlines_dup(mlxdata);
	if (berlines == NULL || berlines[0] == NULL)
		return (finish(mlxdata, 1, 0), -1);
	px = mlxdata.pdata.loc_x / mlxdata.wscale;
	py = mlxdata.pdata.loc_y / mlxdata.wscale;
	search_path_rec(berlines, mlxdata, px, py);
	py = 0;
	while (berlines[py] != NULL)
	{
		px = 0;
		while (berlines[py][px] != '\n' && berlines[py][px] != '\0')
		{
			if (berlines[py][px] != '1' && berlines[py][px] != '0')
				return (free_berl_dup(berlines), -1);
			px++;
		}
		py++;
	}
	return (free_berl_dup(berlines), 1);
}
