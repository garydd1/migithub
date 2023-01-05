# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 17:04:18 by dgarizad          #+#    #+#              #
#    Updated: 2023/01/04 17:04:30 by dgarizad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
SRC = get_next_line.c get_next_line_utils.c

OBJS = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

.c.o:
	@gcc -Wall -Wextra -Werror $< -c $(<:.c.o)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	
clean :
	rm  -f *.o
fclean: clean
		rm -f $(NAME)
re: fclean all
.PHONY : all clean fclean re 
