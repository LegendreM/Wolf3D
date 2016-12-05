/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vertical.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:11 by mlegendr          #+#    #+#             */
/*   Updated: 2014/12/08 16:59:52 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

static double	get_dist(double angle, t_player player, int wall_x)
{
	double dist;

	if (angle < M_PI / 2.0f)
		dist = fabs(wall_x - player.x) * tan(angle);
	else if (angle < M_PI)
		dist = fabs(wall_x - player.x) * tan(M_PI - angle);
	else if (angle < M_PI * 1.5f)
		dist = fabs(wall_x - player.x) * tan(angle - M_PI);
	else
		dist = fabs(wall_x - player.x) * tan(2.0f * M_PI - angle);
	if (angle < M_PI)
		dist *= -1;
	return (dist);
}

static int		wall_right(t_map wall, t_inter *inter, int *wall_x,
							t_map_info info)
{
	inter->from = kRight;
	if (*wall_x < info.width && wall.wall_type != 0)
	{
		inter->wall = wall;
		return (1);
	}
	++(*wall_x);
	return (0);
}

static int		wall_left(t_map wall, t_inter *inter, int *wall_x)
{
	inter->from = kLeft;
	if (*wall_x > 0 && wall.wall_type != 0)
	{
		inter->wall = wall;
		return (1);
	}
	--(*wall_x);
	return (0);
}

static t_inter	check_each_line(double angle, t_player player, t_map_info info,
								int *wall_x)
{
	double	dist;
	t_inter	inter;
	int		wall_y;

	inter.dist = -1;
	while (1)
	{
		dist = get_dist(angle, player, *wall_x);
		wall_y = floor(player.y + dist);
		if (wall_y < 0 || wall_y >= info.height)
			return (inter);
		if (angle < M_PI / 2.0f || angle > M_PI * 1.5f)
		{
			if (wall_right(info.map[wall_y][*wall_x], &inter, wall_x, info))
				break ;
		}
		else if (wall_left(info.map[wall_y][*wall_x - 1], &inter, wall_x))
			break ;
	}
	inter.dist = dist;
	return (inter);
}

t_inter			check_vertical(double angle, t_player player, t_map_info info)
{
	int		wall_x;
	t_inter	inter;

	if (angle < M_PI / 2.0f || angle > M_PI * 1.5f)
		wall_x = ceil(player.x);
	else
		wall_x = floor(player.x);
	inter = check_each_line(angle, player, info, &wall_x);
	if (inter.dist == -1)
		return (inter);
	inter.x = wall_x;
	inter.y = player.y + inter.dist;
	inter.dist = sqrt((inter.dist * inter.dist) + (wall_x - player.x) *
				(wall_x - player.x));
	return (inter);
}
