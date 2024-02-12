# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: martorre <martorre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 12:48:11 by martorre          #+#    #+#              #
#    Updated: 2024/02/12 15:48:26 by martorre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address
INCLUDE	=	-I./inc -I./readline
RM		=	rm -fr

NAME		=	minishell
COMP		=	./libft/libft.a
INC			=	./inc/minishell.h

DIR_OBJ		=	obj/
DIR_SRC		=	src/
DIR_RL 		=	readline/
DIR_LIB		=	libft/
DIR_LXR		=	lexer/

DIR_BLT		=	builtins/
DIR_EXPAN	=	expansor/

# *******************************	FILES	******************************* #

FILES		=	main.c enviroment.c
LXR_FILES	=	lexer_utils.c lexer.c
BLT_FILES	=	builtins.c builtins_utils.c ft_unset.c ft_export1.c ft_export2.c ft_cd.c ft_echo.c
#EXPAN_FILES	=	expansor.c

FILES_SRC	=	$(addprefix $(DIR_SRC),$(FILES))
LXR_SRC		=	$(addprefix $(DIR_SRC),$(addprefix $(DIR_LXR),$(LXR_FILES)))
EXPAN_SRC	=	$(addprefix $(DIR_SRC),$(addprefix $(DIR_EXPAN),$(EXPAN_FILES)))
BLT_SRC		=	$(addprefix $(DIR_SRC),$(addprefix $(DIR_BLT),$(BLT_FILES)))

# *********************************	OBJECTS	****************************** #

OBJ			=	$(addprefix $(DIR_OBJ),$(FILES_SRC:.c=.o))
LXR_OBJ		=	$(addprefix $(DIR_OBJ),$(LXR_SRC:.c=.o))
EXPAN_OBJ	=	$(addprefix $(DIR_OBJ),$(EXPAN_SRC:.c=.o))
BLT_OBJ		=	$(addprefix $(DIR_OBJ),$(BLT_SRC:.c=.o))
LIB_A		:=	$(DIR_RL)libreadline.a $(DIR_RL)libhistory.a $(DIR_LIB)libft.a
LIB_ADD_DIR	:=	-L$(DIR_RL) -L$(DIR_LIB)
LIB_SEARCH	:=	-lreadline -lhistory -ltermcap -lft

# *******************************  HEADERS	******************************* #

HEADERS		:=	$(INC_ROOT)
HEADERS		+=	$(addsuffix $(INC_ROOT),$(DIR_LIB))

# *******************************  COLORS	******************************* #

RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
BLUE		=	\033[0;34m
PURPLE		=	\033[0;35m
CYAN		=	\033[0;36m
RESET		=	\033[0m
GREEN_BOLD	=	\033[1;32m
BLUE_BOLD	=	\033[1;34m
CYAN_BOLD	=	\033[1;36m

# *******************************  RULES ******************************* #

all : rdline library $(DIR_OBJ) $(NAME)

library :
	@$(MAKE) -C $(DIR_LIB) --no-print-directory

$(NAME) : $(OBJ) $(LXR_OBJ) $(BLT_OBJ) $(EXPAN_OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LXR_OBJ) $(BLT_OBJ) $(EXPAN_OBJ) $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) -o $@

	@echo "${BLUE_BOLD}minishell ${GREEN}compiled ✅\n${RESET}"

rdline:
ifeq ($(shell test -e $(DIR_RL)libreadline.a && echo exists),)
	@echo "${YELLOW}Configuring${RESET} and ${YELLOW}compiling ${RESET}readline..."
	@cd ./readline/ &> /dev/null && ./configure &> /dev/null
	@make -C ./readline/ &> /dev/null
	@echo "${BLUE_BOLD}readline ${GREEN}compiled ✅\n${RESET}"
endif

$(DIR_OBJ)%.o: %.c Makefile $(LIB_A) $(INC)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 $(INCLUDE) -c $< -o $@
	@echo "${YELLOW}Compiling ${RESET}$@...${RESET}"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

clean	:
	@$(MAKE) -C libft clean --no-print-directory
	@$(RM) $(DIR_OBJ)
	@echo "${RED}Deleting${RESET} all objects 🗑"

fclean	: clean
	@$(MAKE) -C libft fclean --no-print-directory
	@$(RM) $(NAME) 
	@echo "${BLUE_BOLD}minishell ${RED}deleted${RESET}"
	@$(MAKE) -C readline clean --no-print-directory

norm	:
	@printf "${PURPLE}SEARCHING FOR A PRINTF IN THE PROJECT: "
	@printf "%i \n${RESET}" $(shell grep "	printf" *.c | wc -l)
	@printf "${YELLOW}Norminette...\n${RESET}"
	@printf "${RED}"
	@norminette src/*/*.c src/*.c inc/*.h > test && printf "$(GREEN)\t[OK]\n" || grep Error test
	@printf "${RESET}"
	@rm test

re		: fclean
	@$(MAKE) all

.PHONY : all clean fclean re librarys rdline
