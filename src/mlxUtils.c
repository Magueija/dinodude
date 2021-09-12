/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxUtils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:20:43 by tosilva           #+#    #+#             */
/*   Updated: 2021/09/11 12:44:02 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinodude.h"

void	*new_mlx_connection(void)
{
	void	*mlx_connection;

	mlx_connection = mlx_init();
	if (!mlx_connection)
		ft_strerror(ALLOCATION_ERROR, MLX_CONNECTION_ERROR, NULL);
	return (mlx_connection);
}

void	free_mlx_connection(void **mlx_connection)
{
	if (!mlx_connection || !(*mlx_connection))
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR, NULL);
	mlx_destroy_display(*mlx_connection);
	ft_free(mlx_connection);
}

void	*new_mlx_window(t_dinodude *game_info,
			int size_x, int size_y, char *title)
{
	void	*mlx_window;

	if (!(game_info->mlx_connection))
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR, game_info);
	mlx_window = mlx_new_window(game_info->mlx_connection,
			size_x, size_y, title);
	if (!mlx_window)
		ft_strerror(ALLOCATION_ERROR, MLX_WINDOW_CREATION_ERROR, game_info);
	return (mlx_window);
}

void	free_mlx_window(void *mlx_connection, void **mlx_window)
{
	if (!mlx_connection)
		ft_strerror(NULL_ADDRESS, NULL_MLX_CONNECTION_ERROR, NULL);
	if (*mlx_window)
		mlx_destroy_window(mlx_connection, *mlx_window);
	*mlx_window = NULL;
}

void	put_mlx_str_moves(t_dinodude *game_info)
{
	int	col;

	col = 0;
	while (col < game_info->map.x_count / 2)
	{
		if (game_info->map.map[0][col] == WALL_CHARACTER)
		{
			mlx_put_image_to_window(game_info->mlx_connection,
				game_info->mlx_window, game_info->sprite_wall.image,
				col * SPRITE_WIDTH, 0 * SPRITE_HEIGHT);
		}
		col++;
	}
	game_info->moves_str = ft_itoa(game_info->move_count);
	mlx_string_put(game_info->mlx_connection, game_info->mlx_window,
		STR_MOVES_POS_X, STR_MOVES_POS_Y, STRING_COLOR, "Moves: ");
	mlx_string_put(game_info->mlx_connection, game_info->mlx_window,
		STR_MOVES_POS_X + 40, STR_MOVES_POS_Y,
		STRING_COLOR, game_info->moves_str);
	ft_free((void **)&(game_info->moves_str));
}
