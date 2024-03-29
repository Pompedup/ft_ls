# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/03 18:57:57 by abezanni          #+#    #+#              #
#    Updated: 2019/03/03 17:02:46 by abezanni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			@gcc

CFLAGS =		-Wall -Wextra -Werror $(INCLUDE)

LIB_PATH =		libft

LIB =			libft/libft.a

OBJ =			$(SRC:.c=.o)

INCLUDE =		-I ./inc

GET =			file.c\
				folder.c\
				option_l.c\

STRUCT =		file.c\
				folder.c\
				error.c\

DISPLAY =		adjust.c\
				colomn.c\
				display.c\
				files.c\
				folder.c\
				right_size.c\

HANDLE =		args.c\
				options.c\

SORT =			files.c\
				folders.c\

RACINE =		ft_ls.c\
				$(addprefix display/, $(DISPLAY))\
				$(addprefix get/, $(GET))\
				$(addprefix handle/, $(HANDLE))\
				$(addprefix struct/, $(STRUCT))\
				$(addprefix sort/, $(SORT))\

SRC =			$(addprefix src/,$(RACINE))\
				#$(addprefix get_data/,$(ASM_GET_DATA))\

#$(patsubst %.c,%.o,x.c.c bar.c)

NAME =			ft_ls


all : libftcomp $(NAME)

$(NAME) : $(LIB) $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(LIB) $(OBJ)
	@echo "\033[1;32mSucced ft_ls\033[0m"


$(OBJ) : inc/ft_ls.h

libftcomp :
	@make -C $(LIB_PATH)

file_test :
	rm -rf directory
	touch file1
	mkdir directory
	touch file2

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
