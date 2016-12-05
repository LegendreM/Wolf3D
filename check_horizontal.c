/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_horizontal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:11 by mlegendr          #+#    #+#             */
/*   Updated: 2014/12/08 16:59:52 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

static double	get_dist(double angle, t_player player, int wall_y)
{
	double	dist;

	if (angle < M_PI / 2.0f)
		dist = fabs(wall_y - player.y) * tan(M_PI / 2.0f - angle);
	else if (angle < M_PI)
		dist = fabs(wall_y - player.y) * tan(angle - M_PI / 2.0f);
	else if (angle < M_PI * 1.5f)
		dist = fabs(wall_y - player.y) * tan(M_PI * 1.5f - angle);
	else
		dist = fabs(wall_y - player.y) * tan(angle - M_PI * 1.5f);
	if (angle > M_PI / 2.0f && angle < M_PI * 1.5f)
		dist *= -1;
	return (dist);
}

static int		wall_bot(t_map wall, t_inter *inter, int *wall_y,
							t_map_info info)
{
	inter->from = kBot;
	if (*wall_y < info.height && wall.wall_type != 0)
	{
		inter->wall = wall;
		return (1);
	}
	++(*wall_y);
	return (0);
}

static int		wall_top(t_map wall, t_inter *inter, int *wall_y)
{
	inter->from = kTop;
	if (*wall_y > 0 && wall.wall_type != 0)
	{
		inter->wall = wall;
		return (1);
	}
	--(*wall_y);
	return (0);
}

static t_inter	check_each_line(double angle, t_player player, t_map_info info,
	int *wall_y)
{
	double	dist;
	t_inter	inter;
	int		wall_x;

	inter.dist = -1;
	while (1)
	{
		dist = get_dist(angle, player, *wall_y);
		wall_x = floor(player.x + dist);
		if (wall_x < 0 || wall_x > info.width + 1)
			return (inter);
		if (angle > M_PI)
		{
			if (wall_bot(info.map[*wall_y][wall_x], &inter, wall_y, info))
				break ;
		}
		else if (wall_top(info.map[*wall_y - 1][wall_x], &inter, wall_y))
		{
			break ;
		}
	}
	inter.dist = dist;
	return (inter);
}

t_inter			check_horizontal(double angle, t_player player, t_map_info info)
{
	int		wall_y;
	t_inter inter;

	inter.dist = -1;
	if (angle < M_PI)
		wall_y = floor(player.y);
	else
		wall_y = ceil(player.y);
	inter = check_each_line(angle, player, info, &wall_y);
	if (inter.dist == -1)
		return (inter);
	inter.x = player.x + inter.dist;
	inter.y = wall_y;
	inter.dist = sqrt((inter.dist * inter.dist) + (wall_y - player.y)
		* (wall_y - player.y));
	return (inter);
}
