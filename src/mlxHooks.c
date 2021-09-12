/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxHooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:47:52 by tosilva           #+#    #+#             */
/*   Updated: 2021/09/12 17:57:06 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinodude.h"

void	move_player(int keycode, t_dinodude *game_info)
{
	if (!game_info)
		ft_strerror(NULL_ADDRESS, NULL_TYPE_DINODUDE_ERROR, NULL);
	if (!(game_info->game_ended) && allowed_move(keycode, game_info))
		change_player_position(keycode, game_info);
}

int	key_hook(int keycode, t_dinodude *game_info)
{
	if (keycode == ESC_LINUX
		|| keycode == ESC_MACOS)
	{
		if (!game_info)
			ft_strerror(NULL_ADDRESS, NULL_TYPE_DINODUDE_ERROR, NULL);
		free_type_dinodude(game_info);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == MOVE_UP_LINUX
		|| keycode == MOVE_DOWN_LINUX
		|| keycode == MOVE_RIGHT_LINUX
		|| keycode == MOVE_LEFT_LINUX
		|| keycode == MOVE_UP_MACOS
		|| keycode == MOVE_DOWN_MACOS
		|| keycode == MOVE_RIGHT_MACOS
		|| keycode == MOVE_LEFT_MACOS)
		move_player(keycode, game_info);
	return (1);
}

int	close_window_hook(t_dinodude *game_info)
{
	if (!game_info)
		ft_strerror(NULL_ADDRESS, NULL_TYPE_DINODUDE_ERROR, NULL);
	game_info->mlx_window = NULL;
	return (key_hook(ESC_LINUX, game_info));
}

int	focus_in_window(t_dinodude *game_info)
{
	int	pos_x;
	int	pos_y;

	pos_x = game_info->player_position.pos_x;
	pos_y = game_info->player_position.pos_y;
	game_info->map.map[pos_y][pos_x] = 'P';
	game_info->collectible_count = 0;
	draw_map(game_info);
	if (game_info->game_ended)
		mlx_string_put(game_info->mlx_connection, game_info->mlx_window,
			(pos_x - .4) * SPRITE_WIDTH, (pos_y - .2) * SPRITE_HEIGHT,
			STRING_COLOR, "YOU WON!");
	return (1);
}
