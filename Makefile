#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: barnout <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/11 09:10:24 by barnout           #+#    #+#              #
#    Updated: 2018/09/26 16:05:53 by barnout          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

C_GREEN = "\033[32m"
C_YELLOW = "\033[33m"
C_RESET = "\033[0m"

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME = libft_malloc_$(HOSTTYPE).so
CC = gcc
LIBFT = ./libft
LIBFT_A = ./libft/libft.a
LINK_NAME = libft_malloc.so
INC_DIR = ./includes
C_FLAGS = -Wall -Wextra -Werror
I_FLAGS = -I$(INC_DIR) -I$(LIBFT)
SRC = malloc.c ini.c free.c realloc.c distribute.c page.c show_mem.c visu.c
O_DIR = ./objs
S_DIR = ./srcs
INCLUDES = malloc.h
OBJ = $(addprefix $(O_DIR)/, $(addsuffix .o, $(basename $(SRC))))
DEP = $(addprefix $(INC_DIR)/, $(INCLUDES))

all: $(NAME)

$(NAME): $(OBJ) $(DEP)
	@make -C $(LIBFT)
	@echo Compiling $(NAME) ...
	$(CC) -shared $(C_FLAGS) $(OBJ) $(LIBFT_A) -o $@ $(I_FLAGS)
	$(shell ln -s $(NAME) $(LINK_NAME))
	@echo $(C_GREEN)$(NAME) Compilation Completed$(C_RESET)

clean:
	@make clean -C $(LIBFT)
	@rm -rf $(O_DIR)
	@echo $(C_YELLOW)$(NAME) Object Files Deleted$(C_RESET)

fclean: clean
	@rm -f $(NAME) $(LINK_NAME)
	@make clearexe -C $(LIBFT)
	@echo $(C_YELLOW)$(NAME) Library Deleted$(C_RESET)

re: fclean all

$(O_DIR)/%.o: $(S_DIR)/%.c $(DEP)
	@mkdir -p $(O_DIR)
	@$(CC) -c -o $@ $< $(C_FLAGS) $(I_FLAGS)

.PHONY: fclean clean all re