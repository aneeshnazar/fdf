# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anazar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 19:19:24 by anazar            #+#    #+#              #
#    Updated: 2017/11/29 20:30:19 by anazar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
INC_DIR = includes/
LIB_DIR = libft/
SRC_DIR = srcs/
MLX_DIR = minilibx/
FILES = draw_line get_num_lines iabs init_bres init_coord init_tricoord init_wf \
	   	main sign init_img place_at mouse_events redraw zoom center \
		apply_zoom translate key_events	
SRC = $(addprefix $(SRC_DIR), $(patsubst %, %.c, $(FILES)))
OBJ = $(patsubst %, %.o, $(FILES))
FLAGS = -Wall -Werror -Wextra -c -I$(INC_DIR) -I$(LIB_DIR)$(INC_DIR) -I$(MLX_DIR) 
LFLAG = -framework OpenGL -framework Appkit -L $(LIB_DIR) -lft -L $(MLX_DIR) -lmlx

all:		$(NAME)

lib:
	@make -C libft/ re

$(NAME):	$(OBJ)
	@$(MAKE) lib
	@make -C $(MLX_DIR)
	@gcc $(OBJ) $(LFLAG) -o $(NAME)

$(OBJ):		$(SRC)
	@gcc $(FLAGS) -c $(SRC)

clean:
	@make -C libft/ clean
	@make -C minilibx/ clean
	@rm -rf *.o

fclean:
	@make -C libft/ fclean
	@$(MAKE) clean
	@rm -rf $(NAME)

re: fclean all
