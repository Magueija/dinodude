# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/12 18:48:36 by tosilva           #+#    #+#              #
#    Updated: 2021/09/12 19:24:56 by tosilva          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## sudo apt-get install gcc make xorg libxext-dev libbsd-dev xdotool

##########################################################################################################################################
## Variables
##########################################################################################################################################

###########################################
## Target
###########################################

NAME		=	libmlx.a
NAME_UNAME	=	libmlx_$(shell uname).a

###########################################
## Commands & Flags
###########################################

CC			= gcc
CFLAGS		= -O3
IFLAGS		= -I.
DEBFLAGS	= -g -fsanitize=address

AR		= ar rcs

MKDIR	= mkdir -p
RM		= rm -fr

###########################################
## Folders & Files
###########################################

# Current dir
CURRENT := ${shell pwd}/

LIBFT_ROOT	= ../libft/

# Libs path
LIBFT_FILE	= libft.a
LIBFT		:= ${addprefix $(LIBFT_ROOT)$(BIN_ROOT), $(LIBFT_FILE)}

DEBUG_FILES	= a.out a.out.dSYM/

OBJ_DIR = obj/

SRC	= mlx_init.c mlx_new_window.c mlx_pixel_put.c mlx_loop.c \
			mlx_mouse_hook.c mlx_key_hook.c mlx_expose_hook.c mlx_loop_hook.c \
			mlx_int_anti_resize_win.c mlx_int_do_nothing.c \
			mlx_int_wait_first_expose.c mlx_int_get_visual.c \
			mlx_flush_event.c mlx_string_put.c mlx_set_font.c \
			mlx_new_image.c mlx_get_data_addr.c \
			mlx_put_image_to_window.c mlx_get_color_value.c mlx_clear_window.c \
			mlx_xpm.c mlx_int_str_to_wordtab.c mlx_destroy_window.c \
			mlx_int_param_event.c mlx_int_set_win_event_mask.c mlx_hook.c \
			mlx_rgb.c mlx_destroy_image.c mlx_mouse.c mlx_screen_size.c \
			mlx_destroy_display.c
OBJ	= $(addprefix $(OBJ_DIR),$(SRC:%.c=%.o))

##########################################################################################################################################
## Rules
##########################################################################################################################################

.DELETE_ON_ERROR:

###########################################
## Compile
###########################################

all: all_bin

all_bin: libft libmlx

libft: | $(LIBFT_ROOT)
	@$(MAKE) -C $(LIBFT_ROOT)

$(LIBFT):
	${error $(CURRENT)$(LIBFT) does not exist! Use `make libft`!}

libmlx: $(NAME)

$(OBJ): $(OBJ_DIR)%.o: %.c
	@$(MKDIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME)	: $(OBJ)
	$(AR) $(NAME) $(OBJ)
	@cp $(NAME) $(NAME_UNAME)

###########################################
## Debug
###########################################

debug: CFLAGS += $(DEBFLAGS)
debug: debug_libft libmlx

debug_libft:
	@$(MAKE) debug -C $(LIBFT_ROOT)

test: all
	@test/run_tests.sh

###########################################
## Clear
###########################################

clean:
	@$(MAKE) clean -C $(LIBFT_ROOT)
	$(RM) $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_ROOT)
	$(RM) $(NAME_UNAME) $(NAME)

clean_debug:
	$(RM) $(DEBUG_FILES)
	$(RM) test/main.o test/mlx-test

clean_all: fclean clean_debug

###########################################
## Reload
###########################################

re_debug: fclean debug

re: fclean all

bonus: all

##########################################################################################################################################
## Phony
##########################################################################################################################################

.PHONY: all all_bin libft libmlx debug test clean fclean clean_debug clean_all re_debug re bonus

