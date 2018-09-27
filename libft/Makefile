# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: barnout <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/09 20:20:32 by barnout           #+#    #+#              #
#    Updated: 2018/09/24 17:20:52 by barnout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_GREEN = "\033[32m"
C_CYAN = "\033[36m"
C_RESET = "\033[0m"
NAME	=	libft.a
CC = gcc
INC_DIR = ./includes
C_FLAGS = -Wall -Wextra -Werror
I_FLAGS = -I$(INC_DIR) -I./
SRC=		ft_atoi.c		\
			ft_bzero.c	\
			ft_isalnum.c	\
			ft_isalpha.c	\
			ft_isascii.c	\
			ft_isdigit.c	\
			ft_isprint.c	\
			ft_memccpy.c	\
			ft_memchr.c	\
			ft_memcmp.c	\
			ft_memcpy.c	\
			ft_memccpy.c	\
			ft_memmove.c	\
			ft_memset.c	\
			ft_putchar.c	\
			ft_putnbr.c	\
			ft_putstr.c	\
			ft_strcat.c	\
			ft_strcpy.c	\
			ft_strlcat.c	\
			ft_strlen.c	\
			ft_strncat.c	\
			ft_strcmp.c	\
			ft_strncmp.c	\
			ft_strncpy.c	\
			ft_strnstr.c	\
			ft_strstr.c	\
			ft_tolower.c	\
			ft_toupper.c	\
			ft_strclr.c	\
			ft_striter.c	\
			ft_striteri.c	\
			ft_strmap.c	\
			ft_strmapi.c	\
			ft_strequ.c	\
			ft_strnequ.c	\
			ft_strtrim.c	\
			ft_putendl.c	\
			ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c	\
			ft_put_size_t.c
O_DIR = ./objs
OBJS = $(addprefix $(O_DIR)/, $(addsuffix .o, $(basename $(SRC))))
DEP = libft.h

all	: pre_build

pre_build:
	@echo Compiling $(NAME) ...
	@make $(NAME)

$(NAME): $(OBJS) $(DEP)
	@ar rc $@ $(OBJS) 
	@ranlib $(NAME)
	@echo $(C_GREEN)$(NAME) Compilation Completed$(C_RESET)

clean	:	
	@rm -rf $(O_DIR)
	@echo $(C_CYAN)$(NAME) Object Files Deleted$(C_RESET)

fclean	:	clean
	@rm -f $(NAME)
	@echo $(C_CYAN)$(NAME) Executable Deleted$(C_RESET)

clearexe :
	@rm -f $(NAME)
	@echo $(C_CYAN)$(NAME) Executable Deleted$(C_RESET)

re		:	fclean all

$(O_DIR)/%.o : %.c $(DEP)
	@mkdir -p $(O_DIR)
	@$(CC) -c -o $@ $< $(C_FLAGS) $(I_FLAGS)

.PHONY: clean all re fclean pre_build
