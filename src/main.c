/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 11:30:49 by tosilva           #+#    #+#             */
/*   Updated: 2021/09/11 15:07:29 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinodude.h"

void	free_type_dinodude(t_dinodude *game_info)
{
	int	row;

	if (!game_info)
		return ;
	if (game_info->map.map)
	{
		row = 0;
		while (row < game_info->map.y_count)
		{
			ft_free((void **)&(game_info->map.map[row]));
			row++;
		}
		ft_free((void **)(game_info->map.map));
	}
	if (game_info->mlx_connection)
	{
		free_t_mlximage(game_info->mlx_connection, &(game_info->sprite_floor));
		free_t_mlximage(game_info->mlx_connection, &(game_info->sprite_wall));
		free_t_mlximage(game_info->mlx_connection, &(game_info->sprite_player));
		free_t_mlximage(game_info->mlx_connection,
			&game_info->sprite_collectible);
		free_t_mlximage(game_info->mlx_connection, &(game_info->sprite_exit));
		free_mlx_window(game_info->mlx_connection, &(game_info->mlx_window));
		free_mlx_connection(&(game_info->mlx_connection));
	}
}

void	ft_strerror(int index, char *message, t_dinodude *game_info)
{
	printf("Error\n");
	printf("%s: %s\n", strerror(index), message);
	if (game_info)
		free_type_dinodude(game_info);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_dinodude	game_info;

	if (argc == 2)
	{
		ft_bzero(&game_info, sizeof(t_dinodude));
		check_and_save_map(argv[1], &game_info);
		play_game(&game_info);
	}
	else if (argc == 1)
		ft_strerror(NO_FILE_OR_DIRECTORY, FILE_NOT_PROVIDED, NULL);
	else
		ft_strerror(TOO_MUCH_ARGUMENTS, MORE_THAN_ONE_MAP_GIVEN, NULL);
	return (0);
}
