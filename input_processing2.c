/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:01:14 by pgober            #+#    #+#             */
/*   Updated: 2023/12/13 19:09:45 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	close_window(t_mlx_data *mlxdata)
{
	return (finish(*mlxdata, 0, 0), 0);
}

static int	check_cond1(t_mlx_data *mlxdata, int *wall, int w, int cond)
{
	if (cond == 1 && \
		abs(wall[w + 1] + mlxdata->pdata.hight - mlxdata->pdata.loc_y) <= \
		mlxdata->pdata.stepsz / 2)
		return (1);
	if (cond == 2 && \
		abs(mlxdata->pdata.loc_y + mlxdata->pdata.hight - wall[w + 1]) <= \
		mlxdata->pdata.stepsz / 2)
		return (1);
	if (cond == 3 && \
		abs(wall[w] + mlxdata->pdata.width - 1 - mlxdata->pdata.loc_x) <= \
		mlxdata->pdata.stepsz / 2)
		return (1);
	if (cond == 4 && \
		abs(mlxdata->pdata.loc_x + mlxdata->pdata.width - 1 - wall[w]) <= \
		mlxdata->pdata.stepsz / 2)
		return (1);
	return (0);
}

static int	check_cond2(t_mlx_data *mlxdata, int *wall, int w, int cond)
{
	if (cond == 1 && \
		((wall[w] <= mlxdata->pdata.loc_x && mlxdata->pdata.loc_x < \
		wall[w] + mlxdata->pdata.width - 1) || \
		(wall[w] < mlxdata->pdata.loc_x + mlxdata->pdata.width - 1 && \
		mlxdata->pdata.loc_x + mlxdata->pdata.width - 1 <= \
		wall[w] + mlxdata->pdata.width - 1)))
		return (1);
	if (cond == 2 && \
		((wall[w + 1] <= mlxdata->pdata.loc_y && mlxdata->pdata.loc_y < \
		wall[w + 1] + mlxdata->pdata.hight) || \
		(wall[w + 1] < mlxdata->pdata.loc_y + mlxdata->pdata.hight && \
		mlxdata->pdata.loc_y + mlxdata->pdata.hight <= \
		wall[w + 1] + mlxdata->pdata.hight)))
		return (1);
	return (0);
}

char	*check_iswall(t_mlx_data *mlxdt, int *wall, int wallnum)
{
	int		w;
	char	*instr;
	int		i;

	w = 0;
	i = 0;
	instr = (char *)malloc(16 * sizeof(char));
	if (!instr)
		return (finish(*mlxdt, 1, 0), NULL);
	while (w + 2 <= 2 * wallnum)
	{
		if (check_cond1(mlxdt, wall, w, 1) && check_cond2(mlxdt, wall, w, 1))
			instr[i++] = 'w';
		if (check_cond1(mlxdt, wall, w, 2) && check_cond2(mlxdt, wall, w, 1))
			instr[i++] = 's';
		if (check_cond1(mlxdt, wall, w, 3) && check_cond2(mlxdt, wall, w, 2))
			instr[i++] = 'a';
		if (check_cond1(mlxdt, wall, w, 4) && check_cond2(mlxdt, wall, w, 2))
			instr[i++] = 'd';
		w += 2;
	}
	instr[i] = 'x';
	return (instr);
}
