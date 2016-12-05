/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:11 by mlegendr          #+#    #+#             */
/*   Updated: 2014/12/08 16:59:52 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

static void	lanorme(t_env env, int i, int j)
{
	double p_x;
	double p_y;

	p_x = env.p_x;
	p_y = env.p_y;
	if (p_x < 0 || p_x >= env.info.width || p_y < 0 || p_y >= env.info.height)
		pixel_8u(env.minimap, i, j, new_pixel_8u(0, 0, 0, 80));
	else if (env.minimap->width / 2 - 2 < i && env.minimap->height / 2 - 2 < j
		&& env.minimap->width / 2 + 2 > i && env.minimap->height / 2 + 2 > j)
	{
		pixel_8u(env.minimap, i, j, new_pixel_8u(0, 255, 60, 0));
	}
	else if (env.info.map[(int)floor(p_y)][(int)floor(p_x)].wall_type != 0)
		pixel_8u(env.minimap, i, j, new_pixel_8u(255, 88, 03, 40));
	else
		pixel_8u(env.minimap, i, j, new_pixel_8u(139, 136, 120, 80));
}

void		minimap(t_env env)
{
	int		i;
	int		j;
	double	p_x;
	double	p_y;

	j = 0;
	while (j < env.minimap->height)
	{
		i = 0;
		p_y = env.player.y + (j - env.minimap->height / 2) / 20.0f;
		while (i < env.minimap->width)
		{
			p_x = env.player.x + (i - env.minimap->width / 2) / 20.0f;
			env.p_x = p_x;
			env.p_y = p_y;
			lanorme(env, i, j);
			i++;
		}
		j++;
	}
}
