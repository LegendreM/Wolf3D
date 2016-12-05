/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 15:41:22 by mlegendr          #+#    #+#             */
/*   Updated: 2016/06/02 15:41:24 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "wolf3d.h"
#include <string.h>

static int	key_press(int keycode, t_env *env)
{
	if (keycode == 27)
		tag(env);
	if (keycode == 257)
		env->player.move.walk = 1;
	if (keycode == 28 && env->aa)
		env->aa = 0;
	else if (keycode == 28)
		env->aa = 1;
	if (keycode == 123 || keycode == 0)
		env->player.move.left = 1;
	if (keycode == 124 || keycode == 2)
		env->player.move.right = 1;
	if (keycode == 126 || keycode == 13)
		env->player.move.forward = 1;
	if (keycode == 125 || keycode == 1)
		env->player.move.backward = 1;
	if (keycode == 49)
		env->player.move.jump = 1;
	if (keycode == 53)
		exit(0);
	return (0);
}

static int	key_release(int keycode, t_env *env)
{
	if (keycode == 49)
		env->player.move.jump = 0;
	if (keycode == 257)
		env->player.move.walk = 0;
	if (keycode == 123 || keycode == 0)
		env->player.move.left = 0;
	if (keycode == 124 || keycode == 2)
		env->player.move.right = 0;
	if (keycode == 126 || keycode == 13)
		env->player.move.forward = 0;
	if (keycode == 125 || keycode == 1)
		env->player.move.backward = 0;
	return (0);
}

static void	init(t_env *env)
{
	env->tag_color = new_pixel_8u(230, 30, 80, 0);
	env->prev_time = clock();
	env->player.move.backward = 0;
	env->player.move.forward = 0;
	env->player.move.left = 0;
	env->player.move.right = 0;
	env->player.move.jump = 0;
	env->win_width = 1024;
	env->win_height = 1024;
	env->player.angle = M_PI;
	env->player.x = 6.5;
	env->player.y = 6.5;
	env->player.jump_speed = 0;
	env->player.jump_alt = 0;
	env->player.fov = M_PI / 4;
	env->aa = 1;
}

static void	init2(t_env *env)
{
	if (!(env->img = new_mlx_image_8u(env->mlx_ptr,
		env->win_width, env->win_height)))
		return ;
	if (!(env->aliased_img = new_mlx_image_8u(env->mlx_ptr,
		env->win_width, env->win_height)))
		return ;
	if (!(env->minimap = new_mlx_image_8u(env->mlx_ptr,
		200, 200)))
		return ;
	if (!(env->texture = new_mlx_xpm_image_8u(env->mlx_ptr,
		"texture/bot.xpm")))
		return ;
	if (!(env->skybox = new_mlx_xpm_image_8u(env->mlx_ptr,
		"texture/skybox.xpm")))
		return ;
	if (!(env->tag = new_mlx_xpm_image_8u(env->mlx_ptr,
		"texture/tag.xpm")))
		return ;
}

int			main(void)
{
	t_env			env;

	init(&env);
	if (!(env.mlx_ptr = mlx_init()))
		return (1);
	env.info = parse("first_map_wolf3d", env.mlx_ptr);
	if (!(env.win = mlx_new_window(env.mlx_ptr, env.win_width,
		env.win_height, "Wolf3d")))
	{
		return (1);
	}
	init2(&env);
	raycast(env);
	mlx_expose_hook(env.win, expose, &env);
	mlx_hook(env.win, KEYPRESS, KEYPRESSMASK, key_press, &env);
	mlx_hook(env.win, KEYRELEASE, KEYRELEASEMASK, key_release, &env);
	mlx_hook(env.win, 17, (1L << 17), red_cross, 0);
	mlx_loop_hook(env.mlx_ptr, loop_hook, &env);
	mlx_loop(env.mlx_ptr);
	return (0);
}
