# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 15:38:37 by qmennen           #+#    #+#              #
#    Updated: 2025/03/26 15:38:38 by qmennen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			=	cc
CCFLAG		=	-Wall -Wextra -Werror

HDR_DIR		=	./includes/


SRC_DIR		=	./src/
SRC_FILE	=	util.c thread.c routine.c program.c philosopher.c main.c fork.c

SOURCES		=	$(addprefix $(SRC_DIR), $(SRC_FILE))


OBJ_DIR		=	./obj/
OBJ_FILE	=	$(patsubst %.c, %.o, $(SRC_FILE))
OBJECTS		=	$(addprefix $(OBJ_DIR), $(OBJ_FILE))


all			:	$(NAME)

$(NAME)		:	$(OBJ_DIR) $(OBJECTS)
		$(CC) $(CCFLAG) $(OBJECTS) -o $(NAME) -I$(HDR_DIR)
		@echo "\033[0;92m* $(NAME) program file was created\033[0m *"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(CCFLAG) -c $< -o $@ -I$(HDR_DIR)
clean		:
		@rm -rf $(OBJECTS)
		@echo "\033[0;91m* $(NAME) object files was deleted *\033[0m"

fclean		:	clean
		@rm -rf $(NAME)
		@echo "\033[0;91m* $(NAME) was deleted *\033[0m"

re: fclean
	@make all

.PHONY: all clean fclean re
