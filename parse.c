/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:11 by mlegendr          #+#    #+#             */
/*   Updated: 2014/12/08 16:59:52 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include <fcntl.h>
#include "wolf3d.h"

static int			how_much_col(char *str)
{
	int	i;
	int	cp;

	i = 0;
	cp = 1;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			++cp;
			while (str[i] == ' ')
				++i;
		}
		++i;
	}
	return (cp);
}

static t_map_info	init_tab(char *file)
{
	char		*line;
	t_map_info	info;
	int			i;
	int			fd;

	line = NULL;
	if ((fd = open(file, O_RDONLY)) < 1)
		ret_error("Open failed.");
	info.height = 1;
	get_next_line(fd, &line);
	info.width = how_much_col(line);
	while (get_next_line(fd, &line) > 0)
		++info.height;
	i = 0;
	if (!(info.map = (t_map **)malloc(sizeof(t_map *) * info.height)))
		ret_error("Malloc failed.");
	while (i < info.height)
	{
		if (!(info.map[i] = (t_map *)malloc(sizeof(t_map) * info.width)))
			ret_error("Malloc failed.");
		++i;
	}
	return (info);
}

static void			textures(t_map *map, void *mlx_ptr, int j)
{
	map[j].textures.bot = new_mlx_xpm_image_8u(mlx_ptr, "texture/bot.xpm");
	map[j].textures.top = new_mlx_xpm_image_8u(mlx_ptr, "texture/top.xpm");
	map[j].textures.left = new_mlx_xpm_image_8u(mlx_ptr, "texture/left.xpm");
	map[j].textures.right = new_mlx_xpm_image_8u(mlx_ptr, "texture/right.xpm");
}

static void			fill_line(char *line, t_map *map, void *mlx_ptr)
{
	int		i;
	int		j;

	j = -1;
	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			map[++j].wall_type = ft_atoi(&line[i]);
			if (map[j].wall_type != 0)
				textures(map, mlx_ptr, j);
		}
		while (line[i] >= '0' && line[i] <= '9')
			++i;
		while (line[i] == ' ')
			++i;
	}
}

t_map_info			parse(char *file, void *mlx_ptr)
{
	char		*line;
	int			fd;
	t_map_info	info;
	int			i;

	line = NULL;
	info = init_tab(file);
	if ((fd = open(file, O_RDONLY)) < 1)
		ret_error("Open failed.");
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		fill_line(line, info.map[i], mlx_ptr);
		++i;
	}
	if ((fd = close(fd)) < 0)
		ret_error("Close failed.");
	return (info);
}
