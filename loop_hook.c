/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:11 by mlegendr          #+#    #+#             */
/*   Updated: 2014/12/08 16:59:52 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>
#include <stdlib.h>

static void	forward(t_env *env, double speed, double diff_time)
{
	double	x;
	double	y;

	x = env->player.x + cos(env->player.angle) * speed *
		(double)diff_time / CLOCKS_PER_SEC;
	y = env->player.y - sin(env->player.angle) * speed *
		(double)diff_time / CLOCKS_PER_SEC;
	if (attempt_to_move(x, y, env->info, env->player))
	{
		env->player.x = x;
		env->player.y = y;
	}
	else if (attempt_to_move(x, env->player.y, env->info, env->player))
		env->player.x = x;
	else if (attempt_to_move(env->player.x, y, env->info, env->player))
		env->player.y = y;
}

static void	backward(t_env *env, double speed, double diff_time)
{
	double	x;
	double	y;

	x = env->player.x - cos(env->player.angle) * speed *
		(double)diff_time / CLOCKS_PER_SEC;
	y = env->player.y + sin(env->player.angle) * speed *
		(double)diff_time / CLOCKS_PER_SEC;
	if (attempt_to_move(x, y, env->info, env->player))
	{
		env->player.x = x;
		env->player.y = y;
	}
}

static void	jump(t_env *env, double diff_time)
{
	if (env->player.move.jump && env->player.jump_alt == 0)
		env->player.jump_speed = 4000.0f;
	if ((env->player.jump_alt > 0 || env->player.move.jump) &&
		env->player.jump_alt >= 0)
	{
		env->player.jump_alt += env->player.jump_speed *
		(double)diff_time / CLOCKS_PER_SEC;
		env->player.jump_speed -= 15000.0 * (double)diff_time / CLOCKS_PER_SEC;
	}
	else
	{
		env->player.jump_speed = 0.0f;
		env->player.jump_alt = 0.0f;
	}
}

static void	move(t_env *env, double speed, double rot_speed, double diff_time)
{
	if (env->player.move.left == 1)
	{
		env->player.angle = fmod(env->player.angle - rot_speed *
		(double)diff_time / CLOCKS_PER_SEC + 2 * M_PI, 2 * M_PI);
	}
	if (env->player.move.right == 1)
	{
		env->player.angle = fmod(env->player.angle + rot_speed *
		(double)diff_time / CLOCKS_PER_SEC, 2 * M_PI);
	}
	if (env->player.move.forward == 1)
		forward(env, speed, diff_time);
	if (env->player.move.backward == 1)
		backward(env, speed, diff_time);
}

int			loop_hook(t_env *env)
{
	double	speed;
	double	rot_speed;
	clock_t	diff_time;

	if (!env->mlx_ptr)
		exit(0);
	diff_time = clock() - env->prev_time;
	if (env->player.move.walk == 1)
	{
		speed = SPEED_WALK;
		rot_speed = ROT_SPEED_WALK;
	}
	else
	{
		speed = SPEED_RUN;
		rot_speed = ROT_SPEED_RUN;
	}
	move(env, speed, rot_speed, diff_time);
	jump(env, diff_time);
	env->prev_time = clock();
	raycast(*env);
	minimap(*env);
	expose(env);
	return (0);
}
