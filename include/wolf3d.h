/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:11 by mlegendr          #+#    #+#             */
/*   Updated: 2014/12/08 16:59:52 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "mlxlibft.h"
# include <time.h>
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASEMASK (1L<<1)
# define KEYPRESS 2
# define KEYRELEASE 3
# define DIST_MAX_TAG 2.0f
# define SPEED_RUN 2.0f
# define SPEED_WALK 1.00f
# define ROT_SPEED_RUN 1.5f
# define ROT_SPEED_WALK 0.75f

enum				e_inter_from
{
	kTop,
	kBot,
	kRight,
	kLeft
};

typedef struct			s_textures
{
	t_mlx_image_8u		*bot;
	t_mlx_image_8u		*top;
	t_mlx_image_8u		*left;
	t_mlx_image_8u		*right;
}						t_textures;

typedef struct			s_map
{
	int					wall_type;
	t_textures			textures;
}						t_map;

typedef struct			s_inter
{
	t_map				wall;
	double				dist;
	float				x;
	float				y;
	enum e_inter_from	from;
}						t_inter;

typedef struct			s_draw_col_struct
{
	double				half;
	double				start;
	double				end;
	double				jump;
	double				aa;
	double				dist;
	double				angle;
	int					j;
	int					text_x;
	int					text_y;
	t_mlx_image_8u		*image;
}						t_draw_col_struct;

typedef struct			s_map_info
{
	int					width;
	int					height;
	t_map				**map;
}						t_map_info;

typedef struct			s_move
{
	int					forward;
	int					backward;
	int					right;
	int					left;
	int					walk;
	int					jump;
}						t_move;

typedef struct			s_player
{
	double				x;
	double				y;
	double				angle;
	double				fov;
	t_move				move;
	double				jump_speed;
	double				jump_alt;
}						t_player;

typedef struct			s_env
{
	t_map_info			info;
	t_player			player;
	clock_t				prev_time;
	int					win_width;
	int					win_height;
	void				*mlx_ptr;
	void				*win;
	t_mlx_image_8u		*img;
	t_mlx_image_8u		*aliased_img;
	t_mlx_image_8u		*minimap;
	t_mlx_image_8u		*texture;
	t_mlx_image_8u		*skybox;
	t_mlx_image_8u		*tag;
	t_pixel_8u			tag_color;
	time_t				clock;
	double				p_x;
	double				p_y;
	int					aa;
}						t_env;

t_map_info				parse(char *file, void *mlx_ptr);
void					ret_error(char *str);
void					raycast(t_env env);
void					aa_corection(t_mlx_image_8u *img1,
									t_mlx_image_8u *img2);
void					minimap(t_env env);
int						attempt_to_move(double x, double y,
							t_map_info info, t_player player);
int						loop_hook(t_env *env);
int						red_cross(int r);
int						expose(t_env *env);
t_inter					check_horizontal(double angle, t_player player,
										t_map_info info);
t_inter					check_vertical(double angle, t_player player,
									t_map_info info);
t_inter					greater(double angle, t_player player, t_map_info info);
void					tag(t_env *env);
void					put_tag(t_mlx_image_8u *input, t_mlx_image_8u *output,
								t_roi roi, t_pixel_8u color);

#endif
