# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/14 11:22:08 by tosilva           #+#    #+#              #
#    Updated: 2021/09/12 21:14:55 by tosilva          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## sudo apt-get install gcc make xorg libxext-dev libbsd-dev xdotool

##########################################################################################################################################
## Variables
##########################################################################################################################################

###########################################
## Target
###########################################

NAME	=	dinodude

###########################################
## Commands & Flags
###########################################

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -O3 # -std=gnu99
DEBFLAGS	= -g -fsanitize=address

NORM	= norminette
NORM_COLORS	= sed -E "s/OK!/[32mOK!$/[0m/g;s/Warning(!|:)/[33mWarning\1$/[0m/g;s/Error(!|:)/[31mError\1$/[0m/g"

MKDIR	= mkdir -p
RM		= rm -fr

###########################################
## Folders & Files
###########################################

# Current dir
CURRENT := ${shell pwd}/

LIBFT_ROOT	= libft/
LIBMLX_ROOT	= minilibx/

BIN_ROOT	= bin/
INC_ROOT	= include/
SRC_ROOT	= src/
OBJ_ROOT	= obj/
DEP_ROOT	= dep/

# Libs path
LIBFT_FILE	= libft.a
LIBFT		:= ${addprefix $(LIBFT_ROOT)$(BIN_ROOT), $(LIBFT_FILE)}
LIBMLX_FILE	:= libmlx.a
LIBMLX		:= ${addprefix $(LIBMLX_ROOT), $(LIBMLX_FILE)}

DEBUG_FILES	= a.out a.out.dSYM/

#- *.h and *.c files
HFILES		:= dinodude.h
CFILES		:= dinodude.c main.c map.c mlxHooks.c mlxImages.c mlxUtils.c moves.c

# Files with their path divided by their folders (INC_ROOT and SRC_ROOT)
HFILES_SRC	:= ${foreach file, $(INC_ROOT), ${addprefix $(INC_ROOT), $(HFILES)}}
CFILES_SRC	:= ${foreach file, $(SRC_ROOT), ${addprefix $(SRC_ROOT), $(CFILES)}}

# All files in *_ROOT's
# (Linux) -> sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev
#LIBS	:= -L./$(LIBFT_ROOT)$(BIN_ROOT) -lft -lX11 -lGL -lXext -L./$(LIBMLX_ROOT) -lmlx # -lGLU -pthread
LIBS	:= -L./$(LIBFT_ROOT)$(BIN_ROOT) -lft -L./$(LIBMLX_ROOT) -lmlx -L/usr/lib -lXext -lX11 -lm -lz 
# (MacOS) LIBS	:= -L./$(LIBFT_ROOT)$(BIN_ROOT) -lft -L./$(LIBMLX_ROOT) -lmlx -framework OpenGL -framework AppKit 
INCS	:= $(HFILES_SRC)
SRCS	:= $(CFILES_SRC)
OBJS	:= ${subst $(SRC_ROOT), $(OBJ_ROOT), $(SRCS:.c=.o)}
DEPS	:= ${subst $(SRC_ROOT), $(DEP_ROOT), $(SRCS:.c=.d)}

###########################################
## User input
###########################################

f	:=

##########################################################################################################################################
## Rules
##########################################################################################################################################

.DELETE_ON_ERROR:

###########################################
## Compile
###########################################

all: all_bin

all_bin: libft libmlx solong

libft: | $(LIBFT_ROOT)
	@$(MAKE) -C $(LIBFT_ROOT)

libmlx: | $(LIBMLX_ROOT)
	@$(MAKE) -C $(LIBMLX_ROOT)

solong: $(NAME)

$(LIBFT):
	${error $(CURRENT)$(LIBFT) does not exist! Use `make libft`!}

$(LIBMLX):
	${error $(CURRENT)$(LIBMLX) does not exist! Use `make libmlx`!}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I/usr/include -I./$(LIBFT_ROOT)$(INC_ROOT) -I./$(LIBMLX_ROOT) -I./$(INC_ROOT) $^ $(LIBS) -o $@

$(OBJS): $(OBJ_ROOT)%.o: $(SRC_ROOT)%.c $(DEP_ROOT)%.d | $(OBJ_ROOT) 
	$(CC) $(CFLAGS) -I/usr/include -I./$(LIBFT_ROOT)$(INC_ROOT) -I./$(LIBMLX_ROOT) -I./$(INC_ROOT) -c $< -o $@

$(DEPS): $(DEP_ROOT)%.d: $(SRC_ROOT)%.c $(LIBFT) $(LIBMLX) | $(DEP_ROOT)
	@$(CC) $(CFLAGS) -I/usr/include -I./$(LIBFT_ROOT)$(INC_ROOT) -I./$(LIBMLX_ROOT) -I./$(INC_ROOT) -M \
		-MT '${patsubst $(SRC_ROOT)%.c,$(OBJ_ROOT)%.o,$<} ${patsubst $(SRC_ROOT)%.c,$(DEP_ROOT)%.d,$<}' $< \
		-MF ${patsubst $(SRC_ROOT)%.c,$(DEP_ROOT)%.d,$<}

###########################################
## Debug
###########################################

debug: CFLAGS += $(DEBFLAGS)
debug: debug_libft libmlx solong

debug_libft:
	@$(MAKE) debug -C $(LIBFT_ROOT)

###########################################
## Make dirs
###########################################

$(OBJ_ROOT) $(DEP_ROOT):
	@$(MKDIR) $@

###########################################
## Norm
###########################################

norm:
	@echo "»»»»» HEADERS «««««"
	@$(NORM) $(INCS) | $(NORM_COLORS)
	@echo 
	@echo "»»»»» SOURCES  «««««"
	@$(NORM) $(SRCS) | $(NORM_COLORS)

norm_libft:
	@$(MAKE) norm f=$(f) -C $(LIBFT_ROOT)

###########################################
## Clear
###########################################

clean:
	@$(MAKE) clean -C $(LIBFT_ROOT)
	@$(MAKE) clean -C $(LIBMLX_ROOT)
	$(RM) $(OBJ_ROOT)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_ROOT)
	@$(MAKE) fclean -C $(LIBMLX_ROOT)
	$(RM) $(BIN_ROOT) $(NAME)

clean_dep:
	@$(MAKE) clean_dep -C $(LIBFT_ROOT)
	$(RM) $(DEP_ROOT)

clean_debug:
	@$(MAKE) clean_debug -C $(LIBFT_ROOT)
	@$(MAKE) clean_debug -C $(LIBMLX_ROOT)
	$(RM) $(DEBUG_FILES)

clean_all: fclean clean_debug clean_dep

###########################################
## Reload
###########################################

re_debug: fclean debug

re: fclean all

bonus: all

##########################################################################################################################################
## Phony
##########################################################################################################################################

.PHONY: all all_bin solong libmlx libft debug norm norm_libft clean fclean clean_dep clean_debug clean_all re_debug re bonus

##########################################################################################################################################
# Includes
##########################################################################################################################################

-include ${shell find . -maxdepth 3 -type f -name '*.d'}
