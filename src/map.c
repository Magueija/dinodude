/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 15:50:35 by tosilva           #+#    #+#             */
/*   Updated: 2021/09/11 11:32:07 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinodude.h"

static void	check_map_line(char *line, t_dinodude *game_info, short is_wall)
{
	int	line_length;
	int	i;

	line_length = ft_strlen(line);
	i = 0;
	while (i < line_length)
	{
		if ((is_wall || i == 0) && line[i] != WALL_CHARACTER)
			ft_strerror(INVALID_ARGUMENT, MAP_WALL_INCOMPLETE, NULL);
		else if (line[i] == COLLECTIBLE_CHARACTER)
			game_info->map.must_have[0] = 'C';
		else if (line[i] == EXIT_CHARACTER)
			game_info->map.must_have[1] = 'E';
		else if (line[i] == PLAYER_CHARACTER)
			game_info->map.must_have[2] = 'P';
		else if (line[i] != FLOOR_CHARACTER && line[i] != WALL_CHARACTER)
			ft_strerror(INVALID_ARGUMENT, MAP_CHARACTER_INVALID, NULL);
		i++;
	}
	if (line[i - 1] != WALL_CHARACTER)
		ft_strerror(INVALID_ARGUMENT, MAP_WALL_INCOMPLETE, NULL);
	if (game_info->map.x_count == 0)
		game_info->map.x_count = line_length;
	else if (game_info->map.x_count != line_length)
		ft_strerror(INVALID_ARGUMENT, MAP_NOT_A_RECTANGULAR, NULL);
}

static void	save_map(char *map_name, t_dinodude *game_info)
{
	int		fd;
	char	*line;
	short	not_last_line;
	int		row;

	fd = open(map_name, O_RDONLY);
	if (fd < 3)
		ft_strerror(BAD_FILE_DESCRIPTOR, FILE_OPEN_ERROR, NULL);
	game_info->map.map = ft_calloc(game_info->map.y_count + 1, sizeof(char *));
	if (!(game_info->map.map))
		ft_strerror(ALLOCATION_ERROR, MAP_ALLOCATION_FALIED, NULL);
	row = 0;
	not_last_line = 1;
	while (not_last_line)
	{
		not_last_line = get_next_line(fd, &line);
		game_info->map.map[row++] = line;
	}
	close(fd);
}

void	check_and_save_map(char *map_name, t_dinodude *game_info)
{
	ssize_t	file_ext_index;
	char	*line;
	int		fd;
	short	not_last_line;

	file_ext_index = ft_strlen(map_name) - 4;
	if (file_ext_index < 1
		|| ft_strncmp(&map_name[file_ext_index], ".ber", 5) != 0)
		ft_strerror(INVALID_ARGUMENT, BAD_FILE_EXTENTION, NULL);
	fd = open(map_name, O_RDONLY);
	if (fd < 3)
		ft_strerror(BAD_FILE_DESCRIPTOR, FILE_OPEN_ERROR, NULL);
	not_last_line = 1;
	while (not_last_line)
	{
		not_last_line = get_next_line(fd, &line);
		check_map_line(line, game_info,
			ft_ternint(game_info->map.y_count == 0 || !not_last_line, 1, 0));
		game_info->map.y_count += 1;
		free(line);
	}
	close(fd);
	if (ft_strncmp(game_info->map.must_have, "CEP", 4) != 0)
		ft_strerror(INVALID_ARGUMENT, MAP_WITH_MISSING_CHARACTERS, NULL);
	save_map(map_name, game_info);
}
