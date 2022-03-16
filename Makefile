# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/12 18:22:39 by ehosu             #+#    #+#              #
#    Updated: 2022/03/16 13:00:13 by aricholm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = phil.h
SRCS = phil.c helpers/get_data_helpers.c helpers/helpers.c helpers/activity.c
OBJS = ${SRCS:.c=.o}
RM = rm -rf

CC = gcc
# -pthread
# -lpthread
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=thread

all:	$(NAME)

%.o: %.c
	$(CC) -pthread -c $(CFLAGS) -o $@ $<

$(NAME): $(OBJS)
	$(CC) -pthread -o $(NAME) $(CFLAGS) $(OBJS)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} $(NAME)

re:	fclean all

.PHONY:
	all clean fclean re