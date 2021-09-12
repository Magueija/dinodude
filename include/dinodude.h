/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinodude.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 11:32:11 by tosilva           #+#    #+#             */
/*   Updated: 2021/09/12 17:57:47 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DINODUDE_H
# define DINODUDE_H

////# include <mlx.h>
# include "mlx.h"
# include "libft.h"
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>

/**
 * X11 events and masks
 */
# define KEY_PRESS			02
# define KEY_RELEASE		03
# define BUTTON_PRESS		04
# define BUTTON_RELEASE		05
# define MOTION_NOTIFY		06
# define ENTER_NOTIFY		07
# define LEAVE_NOTIFY		08
# define FOCUS_IN			09
# define FOCUS_OUT			10
# define KEY_MAP_NOTIFY		11
# define EXPOSE				12
# define VISIBILITY_NOTIFY	15
# define DESTROY_NOTIFY		17
# define NO_EVENT_MASK				0L
# define KEY_PRESS_MASK				1L
# define KEY_RELEASE_MASK			2L
# define BUTTON_PRESS_MASK			4L
# define BUTTON_RELEASE_MASK		8L
# define ENTER_WINDOW_MASK			16L
# define LEAVE_WINDOW_MASK			32L
# define KEY_MAP_STATE_MASK			16384L
# define EXPOSURE_MASK				32768L
# define VISIBILITY_CHANGE_MASK		65536L
# define STRUCTURE_NOTIFY_MASK		131072L

/**
 * Errors - use in ft_strerror
 */
# define NO_FILE_OR_DIRECTORY	2
# define BAD_INPUT				5
# define TOO_MUCH_ARGUMENTS		7
# define BAD_FILE_DESCRIPTOR	9
# define NULL_ADDRESS			6
# define ALLOCATION_ERROR		12
# define INVALID_ARGUMENT		22

# define FILE_NOT_PROVIDED			"File not provider"
# define FILE_OPEN_ERROR			"Error opening file"
# define BAD_FILE_EXTENTION			"File extension must be '.ber'"
# define MORE_THAN_ONE_MAP_GIVEN	"Only a map file is allowed"
# define MAP_WALL_INCOMPLETE		"Map wall incomplete"
# define MAP_CHARACTER_INVALID		"Map character invalid"
# define MAP_NOT_A_RECTANGULAR		"Map ins't a rectangular"
# define MAP_WITH_MISSING_CHARACTERS	"Map must have C, E, and P characters"
# define MAP_ALLOCATION_FALIED		"Error allocating memory for map creation"
# define NULL_MAP_ERROR				"No map information provided"
# define MLX_CONNECTION_ERROR		"Error connecting with MinilibX"
# define MLX_WINDOW_CREATION_ERROR	"Error creating a new window with MinilibX"
# define MLX_IMAGE_CREATION_ERROR	"Error creating a new image with MinilibX"
# define NULL_MLX_CONNECTION_ERROR	"No mlx connection provided"
# define NULL_TYPE_DINODUDE_ERROR	"No game information provided"

/**
 * Linux and MacOS keycodes
 */
/* // Arrows keys
# define MOVE_UP_LINUX		65362
# define MOVE_DOWN_LINUX	65364
# define MOVE_LEFT_LINUX	65361
# define MOVE_RIGHT_LINUX	65363
*/
# define ESC_LINUX			65307
# define MOVE_UP_LINUX		119
# define MOVE_DOWN_LINUX	115
# define MOVE_LEFT_LINUX	97
# define MOVE_RIGHT_LINUX	100
# define ESC_MACOS				53
# define MOVE_UP_MACOS			13
# define MOVE_DOWN_MACOS		1
# define MOVE_LEFT_MACOS		0
# define MOVE_RIGHT_MACOS		2

/**
 * Default window and sprite sizes
 */
# define WINDOW_SIZE_X	600
# define WINDOW_SIZE_Y	300 

# define GAME_TITLE				"DinoDude"
# define FLOOR_CHARACTER		'0'
# define WALL_CHARACTER			'1'
# define PLAYER_CHARACTER		'P'
# define COLLECTIBLE_CHARACTER	'C'
# define EXIT_CHARACTER			'E'
# define STR_MOVES_POS_X		10
# define STR_MOVES_POS_Y		17
# define STRING_COLOR			0x00FFFFFF
# define SPRITE_WIDTH		25
# define SPRITE_HEIGHT		25
# define SP_FLOOR			"./sprite/grass.xpm"
# define SP_WALL			"./sprite/rock.xpm"
# define SP_PLAYER_LEFT		"./sprite/dino_left.xpm"
# define SP_PLAYER_RIGHT	"./sprite/dino_right.xpm"
# define SP_COLLECTIBLE		"./sprite/chicken.xpm"
# define SP_EXIT			"./sprite/dino_girl.xpm"
# define SP_WIN_LEFT		"./sprite/dino_and_girl_left.xpm"
# define SP_WIN_RIGHT		"./sprite/dino_and_girl_right.xpm"

typedef struct s_map
{
	char	**map;
	char	must_have[4];
	int		x_count;
	int		y_count;
}				t_map;

typedef struct s_playerpos
{
	int	pos_x;
	int	pos_y;
}				t_playerpos;

typedef struct s_mlximage
{
	void	*image;
	void	*image_address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_mlximage;

typedef struct s_dinodude
{
	t_map		map;
	void		*mlx_connection;
	void		*mlx_window;
	char		*moves_str;
	int			move_count;
	int			collectible_count;
	short		game_ended;
	t_playerpos	player_position;
	t_playerpos	new_player_position;
	t_mlximage	sprite_floor;
	t_mlximage	sprite_wall;
	t_mlximage	sprite_player;
	t_mlximage	sprite_collectible;
	t_mlximage	sprite_exit;
}				t_dinodude;

void		free_type_dinodude(t_dinodude *game_info);
void		ft_strerror(int index, char *message, t_dinodude *info);

void		check_and_save_map(char *map_name, t_dinodude *info);
void		play_game(t_dinodude *info);
void		draw_map(t_dinodude *game_info);
short		allowed_move(int keycode, t_dinodude *game_info);
void		change_player_position(int keycode, t_dinodude *game_info);

void		*new_mlx_connection(void);
void		free_mlx_connection(void **mlx_connection);
void		*new_mlx_window(t_dinodude *game_info,
				int size_x, int size_y, char *title);
void		free_mlx_window(void *mlx_connection, void **mlx_window);
t_mlximage	xpm_to_mlx_image(t_dinodude *game_info, char *file);
void		free_t_mlximage(void *mlx_connection, t_mlximage *mlx_image);
t_mlximage	free_and_xpm_to_mlx_image(t_dinodude *game_info,
				t_mlximage *mlx_image, char *file);
void		put_mlx_str_moves(t_dinodude *game_info);

void		move_player(int keycode, t_dinodude *game_info);
int			key_hook(int keycode, t_dinodude *game_info);
int			close_window_hook(t_dinodude *game_info);
int			focus_in_window(t_dinodude *game_info);

int			argb_to_hex(int alpha, int red, int green, int blue);
int			hex_to_alpha(int hex);
int			hex_to_red(int hex);
int			hex_to_green(int hex);
int			hex_to_blue(int hex);

//* FT_DINODUDE_H
#endif 
