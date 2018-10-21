# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/03 18:57:57 by abezanni          #+#    #+#              #
#    Updated: 2018/10/21 18:37:43 by abezanni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			@gcc

CFLAGS =		-Wall -Wextra -Werror $(INCLUDE)

LIB_PATH =		libft

LIB =			libft/libft.a

OBJ =			$(SRC:.c=.o)

INCLUDE =		-I ./inc

STRUCT =		data_file.c\
				data_folder.c\

SRC =			$(addprefix src/,ft_ls.c)\
				$(addprefix src/struct/, $(STRUCT))
				#$(addprefix get_data/,$(ASM_GET_DATA))\

NAME =			ft_ls


all : libftcomp $(NAME)

$(NAME) : $(LIB) $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(LIB) $(OBJ)
	@echo "\033[1;32mSucced ft_ls\033[0m"


$(OBJ) : inc/ft_ls.h

libftcomp :
	@make -C $(LIB_PATH)

clean :
	@make clean -C $(LIB_PATH)
	@/bin/rm -f $(OBJ)
	@echo "\033[1;32mSucced clean of '*.o' from ft_ls\033[0m"

fclean : clean
	@/bin/rm -f $(LIB)
	@echo "\033[1;32mSucced clean of libft.a\033[0m"
	@/bin/rm -f $(NAME) memory #remove memory
	@echo "\033[1;32mSucced clean ft_ls\033[0m"

re : fclean	all
	@echo "\033[1;32mSucced recompilation ft_ls\033[0m"
