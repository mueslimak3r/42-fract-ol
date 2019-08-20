# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: calamber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/01 18:22:54 by calamber          #+#    #+#              #
#    Updated: 2019/07/01 18:22:56 by calamber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC_DIR = ./src/
SRC_FILES = main.c image.c window.c input.c draw.c sierpinski.c mandelbrot.c julia.c line.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR = ./includes/
INCLUDES =  -I $(INC_DIR) $(FT_INC) $(MLX_INC)

OBJ_DIR = ./obj/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

FT	= ./libft/
FT_LNK	= -L $(FT) -l ft
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I $(FT)includes

ifeq ($(shell uname), Linux)
	MLX	= ./minilibx_X11/
	MLX_LNK	= -L $(MLX) -lmlx -lXext -lX11 -lpthread -lm
	#echo LINUX_MACHINE
else
	MLX	= ./minilibx/
	MLX_LNK	= -L $(MLX) -lmlx -framework OpenGL -framework AppKit
	#echo MACH_MACHINE
endif
MLX_LIB	= $(addprefix $(MLX),libmlx.a)
MLX_INC	= -I $(MLX)


all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(FT_LIB):
	#if [[ ! -e $(FT_LIB) ]]; then echo "found libft" else make -C $(FT) fi
	make -C ./libft/ #$(FT)

$(MLX_LIB):
	#if [[ ! -e $(MLX_LIB) ]]; then echo "found mlx" else make -C $(MLX) fi
	make -C $(MLX)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(FT_LNK) $(MLX_LNK) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(FT) fclean
	make -C $(MLX) clean
	rm -rf $(NAME)

re: fclean all

do:
	make clean
	make
	make clean

.PHONY: all obj $(NAME) clean fclean re do