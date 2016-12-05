/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:11 by mlegendr          #+#    #+#             */
/*   Updated: 2014/12/08 16:59:52 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	expose(t_env *env)
{
	mlx_put_image_to_window(env->mlx_ptr, env->win,
		env->aliased_img->ptr, 0, 0);
	mlx_put_image_to_window(env->mlx_ptr, env->win, env->minimap->ptr, 804, 20);
	return (0);
}
