/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greater.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:11 by mlegendr          #+#    #+#             */
/*   Updated: 2014/12/08 16:59:52 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

t_inter		greater(double angle, t_player player, t_map_info info)
{
	t_inter	hor;
	t_inter	ver;

	hor = check_horizontal(angle, player, info);
	ver = check_vertical(angle, player, info);
	if (ver.dist == -1 || (ver.dist >= hor.dist && hor.dist != -1))
	{
		hor.dist *= cos(fabs(player.angle - angle));
		return (hor);
	}
	ver.dist *= cos(fabs(player.angle - angle));
	return (ver);
}
