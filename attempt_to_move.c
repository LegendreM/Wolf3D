/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attempt_to_move.c.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:11 by mlegendr          #+#    #+#             */
/*   Updated: 2014/12/08 16:59:52 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

int	attempt_to_move(double x, double y, t_map_info info, t_player player)
{
	if (info.map[(int)floor(y)][(int)floor(x)].wall_type != 0)
		return (0);
	if (floor(x) != floor(player.x) && floor(y) != floor(player.y))
		return (0);
	return (1);
}
