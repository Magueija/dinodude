/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinodude.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 18:41:40 by tosilva           #+#    #+#             */
/*   Updated: 2021/09/12 17:46:05 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinodude.h"

static void	parse_floor_and_wall_to_images(t_dinodude *game_info,
				char map_character, int pos_x, int pos_y)
{
	if (map_character == FLOOR_CHARACTER)
		mlx_put_image_to_window(game_info->mlx_connection,
			game_info->mlx_window, game_info->sprite_floor.image,
			pos_x * SPRITE_WIDTH, pos_y * SPRITE_HEIGHT);
	else if (map_character == WALL_CHARACTER)
		mlx_put_image_to_window(game_info->mlx_connection,
			game_info->mlx_window, game_info->sprite_wall.image,
			pos_x * SPRITE_WIDTH, pos_y * SPRITE_HEIGHT);
}

static void	parse_characters_to_images(t_dinodude *game_info,
				char map_character, int pos_x, int pos_y)
{
	if (map_character == FLOOR_CHARACTER
		|| map_character == WALL_CHARACTER)
		parse_floor_and_wall_to_images(game_info, map_character,
			pos_x, pos_y);
	else if (map_character == COLLECTIBLE_CHARACTER)
	{
		game_info->collectible_count++;
		mlx_put_image_to_window(game_info->mlx_connection,
			game_info->mlx_window, game_info->sprite_collectible.image,
			pos_x * SPRITE_WIDTH, pos_y * SPRITE_HEIGHT);
	}
	else if (map_character == PLAYER_CHARACTER)
	{
		game_info->player_position.pos_x = pos_x;
		game_info->player_position.pos_y = pos_y;
		game_info->map.map[pos_y][pos_x] = '0';
		mlx_put_image_to_window(game_info->mlx_connection,
			game_info->mlx_window, game_info->sprite_player.image,
			pos_x * SPRITE_WIDTH, pos_y * SPRITE_HEIGHT);
	}
	else if (map_character == EXIT_CHARACTER)
		mlx_put_image_to_window(game_info->mlx_connection,
			game_info->mlx_window, game_info->sprite_exit.image,
			pos_x * SPRITE_WIDTH, pos_y * SPRITE_HEIGHT);
}

void	draw_map(t_dinodude *game_info)
{
	int	row;
	int	col;

	if (!(game_info->map.map))
		ft_strerror(NULL_ADDRESS, NULL_MAP_ERROR, game_info);
	row = 0;
	while (row < game_info->map.y_count)
	{
		col = 0;
		while (col < game_info->map.x_count)
		{
			parse_characters_to_images(game_info,
				game_info->map.map[row][col], col, row);
			col++;
		}
		row++;
	}
	put_mlx_str_moves(game_info);
}

static void	create_grafics(t_dinodude *game_info)
{
	game_info->mlx_window = new_mlx_window(game_info,
			game_info->map.x_count * SPRITE_WIDTH,
			game_info->map.y_count * SPRITE_HEIGHT, GAME_TITLE);
	game_info->sprite_floor = xpm_to_mlx_image(game_info, SP_FLOOR);
	game_info->sprite_wall = xpm_to_mlx_image(game_info, SP_WALL);
	game_info->sprite_player = xpm_to_mlx_image(game_info, SP_PLAYER_RIGHT);
	game_info->sprite_collectible = xpm_to_mlx_image(game_info, SP_COLLECTIBLE);
	game_info->sprite_exit = xpm_to_mlx_image(game_info, SP_EXIT);
	draw_map(game_info);
}

void	play_game(t_dinodude *game_info)
{
	game_info->mlx_connection = new_mlx_connection();
	create_grafics(game_info);
	mlx_hook(game_info->mlx_window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		close_window_hook, game_info);
	mlx_hook(game_info->mlx_window, VISIBILITY_NOTIFY, VISIBILITY_CHANGE_MASK,
		focus_in_window, game_info);
	mlx_key_hook(game_info->mlx_window, key_hook, game_info);
	mlx_loop(game_info->mlx_connection);
	free_type_dinodude(game_info);
}
