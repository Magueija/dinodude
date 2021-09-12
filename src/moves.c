/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:40:45 by tosilva           #+#    #+#             */
/*   Updated: 2021/09/12 18:02:48 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinodude.h"

static void	change_move_coordinates(int keycode, int *pos_x, int *pos_y)
{
	if (keycode == MOVE_UP_LINUX || keycode == MOVE_UP_MACOS)
		*pos_y -= 1;
	else if (keycode == MOVE_DOWN_LINUX || keycode == MOVE_DOWN_MACOS)
		*pos_y += 1;
	else if (keycode == MOVE_LEFT_LINUX || keycode == MOVE_LEFT_MACOS)
		*pos_x -= 1;
	else if (keycode == MOVE_RIGHT_LINUX || keycode == MOVE_RIGHT_MACOS)
		*pos_x += 1;
}

static void	add_one_move_or_collectible(t_dinodude *game_info)
{
	int	pos_x;
	int	pos_y;

	pos_x = game_info->player_position.pos_x;
	pos_y = game_info->player_position.pos_y;
	if (game_info->map.map[pos_y][pos_x] == COLLECTIBLE_CHARACTER)
	{
		game_info->map.map[pos_y][pos_x] = '0';
		game_info->collectible_count--;
	}
	game_info->move_count++;
	put_mlx_str_moves(game_info);
}

static void	change_left_right_sprites_direction(
				int keycode, t_dinodude *game_info)
{
	if (game_info->game_ended)
	{
		if (keycode == MOVE_LEFT_LINUX || keycode == MOVE_LEFT_MACOS)
			game_info->sprite_player = free_and_xpm_to_mlx_image(game_info,
					&(game_info->sprite_player), SP_WIN_LEFT);
		else
			game_info->sprite_player = free_and_xpm_to_mlx_image(game_info,
					&(game_info->sprite_player), SP_WIN_RIGHT);
		mlx_string_put(game_info->mlx_connection, game_info->mlx_window,
			(game_info->player_position.pos_x - .4) * SPRITE_WIDTH,
			(game_info->player_position.pos_y - .2) * SPRITE_HEIGHT,
			STRING_COLOR, "YOU WON!");
	}
	else if (keycode == MOVE_LEFT_LINUX || keycode == MOVE_LEFT_MACOS)
		game_info->sprite_player = free_and_xpm_to_mlx_image(game_info,
				&(game_info->sprite_player), SP_PLAYER_LEFT);
	else if (keycode == MOVE_RIGHT_LINUX || keycode == MOVE_RIGHT_MACOS)
		game_info->sprite_player = free_and_xpm_to_mlx_image(game_info,
				&(game_info->sprite_player), SP_PLAYER_RIGHT);
}

void	change_player_position(int keycode, t_dinodude *game_info)
{
	mlx_put_image_to_window(game_info->mlx_connection,
		game_info->mlx_window, game_info->sprite_floor.image,
		game_info->player_position.pos_x * SPRITE_WIDTH,
		game_info->player_position.pos_y * SPRITE_HEIGHT);
	change_move_coordinates(keycode,
		&(game_info->player_position.pos_x),
		&(game_info->player_position.pos_y));
	change_left_right_sprites_direction(keycode, game_info);
	add_one_move_or_collectible(game_info);
	mlx_put_image_to_window(game_info->mlx_connection,
		game_info->mlx_window, game_info->sprite_player.image,
		game_info->player_position.pos_x * SPRITE_WIDTH,
		game_info->player_position.pos_y * SPRITE_HEIGHT);
}

short	allowed_move(int keycode, t_dinodude *game_info)
{
	int		new_x;
	int		new_y;
	char	map_character;

	new_x = game_info->player_position.pos_x;
	new_y = game_info->player_position.pos_y;
	change_move_coordinates(keycode, &new_x, &new_y);
	if (new_x < 0 || new_y < 0
		|| new_x >= game_info->map.x_count
		|| new_y >= game_info->map.y_count)
		return (0);
	map_character = game_info->map.map[new_y][new_x];
	if (map_character == WALL_CHARACTER
		|| (map_character == EXIT_CHARACTER
			&& game_info->collectible_count != 0))
		return (0);
	else
	{
		if (map_character == EXIT_CHARACTER
			&& game_info->collectible_count == 0)
			game_info->game_ended = 1;
		return (1);
	}
}
