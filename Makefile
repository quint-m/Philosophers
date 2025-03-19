# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmennen <qmennen@student.codam.nl>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 15:13:28 by qmennen           #+#    #+#              #
#    Updated: 2025/03/19 14:03:25 by qmennen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH=src/
NAME=philo

CC=cc
# FLAGS=-Wall -Wextra -Werror -Wundef -fsanitize=address
FLAGS=-Werror -g

INC=./inc
SRCS=main.c philosopher.c util.c thread.c fork.c program.c routine.c
OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -I$(INC) -lpthread $^ -o $@

%.o: %.c
	$(CC) $(FLAGS) -I$(INC) -c $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
