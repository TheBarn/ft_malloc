#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: barnout <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/11 09:10:24 by barnout           #+#    #+#              #
#    Updated: 2018/09/11 16:44:53 by barnout          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

C_GREEN = "\033[32m"
C_YELLOW = "\033[33m"
C_RESET = "\033[0m"

NAME = malloc
CC = gcc
LIBFT = ./libft
LIBFT_A = ./libft/libftprintf.a
INC_DIR = ./includes
C_FLAGS = -Wall -Wextra -Werror
I_FLAGS = -I$(INC_DIR) -I$(LIBFT)
SRC = malloc.c power.c dump.c
O_DIR = ./objs
S_DIR = ./srcs
INCLUDES = malloc.h
OBJ = $(addprefix $(O_DIR)/, $(addsuffix .o, $(basename $(SRC))))
DEP = $(addprefix $(INC_DIR)/, $(INCLUDES))

all: $(NAME)

$(NAME): $(OBJ) $(DEP)
	@make -C $(LIBFT)
	@echo Compiling $(NAME) ...
	@$(CC) $(C_FLAGS) $(OBJ) $(LIBFT_A) -o $@ $(I_FLAGS)
	@echo $(C_GREEN)$(NAME) Compilation Completed$(C_RESET)

clean:
	@make clean -C $(LIBFT)
	@rm -rf $(O_DIR)
	@echo $(C_YELLOW)$(NAME) Object Files Deleted$(C_RESET)

fclean: clean
	@rm -f $(NAME)
	@make clearexe -C $(LIBFT)
	@echo $(C_YELLOW)$(NAME) Executable Deleted$(C_RESET)

re: fclean all

$(O_DIR)/%.o: $(S_DIR)/%.c $(DEP)
	@mkdir -p $(O_DIR)
	@$(CC) -c -o $@ $< $(C_FLAGS) $(I_FLAGS)

.PHONY: fclean clean all re