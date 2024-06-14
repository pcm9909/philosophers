# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/14 17:13:16 by chunpark          #+#    #+#              #
#    Updated: 2024/06/14 20:20:49 by chunpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
ADDRESS = -g -fsanitize=address
THREAD = -g -fsanitize=thread

NAME = philo
SRCS = check.c \
	  free.c \
	  handle_thread.c \
	  main.c \
	  preprocess.c \
	  print_msg.c \
	  routine.c \
	  time.c \
	  utils.c \
	  validate.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
		   @$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

thread: fclean $(OBJS)
	$(CC) $(CFLAGS) $(ADDRESS) -o $(NAME) $(OBJS)

address: fclean $(OBJS)
	$(CC) $(CFLAGS) $(THREAD) -o $(NAME) $(OBJS)

.PHONY: all clean fclean re



