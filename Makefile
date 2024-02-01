# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: martorre <martorre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 12:48:11 by martorre          #+#    #+#              #
#    Updated: 2024/02/01 15:08:19 by martorre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INCLUDE	=	-I./inc -I./readline
RM		=	rm -fr

NAME		=	minishell
COMP		=	./libft/libft.a

DIR_OBJ		=	obj/
DIR_SRC		=	src/
DIR_RL 		=	readline/
DIR_LIB		=	libft/
DIR_LXR		=	lexer/

# *******************************	FILES	******************************* #

FILES		=	read.c
LXR_FILES	=	string_to_list.c

FILES_SRC	=	$(addprefix $(DIR_SRC), $(FILES));
LXR_SRC		=	$(addprefix $(DIR_SRC), $(addprefix $(DIR_LXR), $(LXR_FILES)));

# *********************************	OBJECTS	****************************** #

OBJ			=	$(addprefix $(DIR_OBJ), $(FILES_SRC:.c=.o))
LXR_OBJ		=	$(addprefix $(DIR_OBJ), $(LXR_SRC:.c=.o))

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

# *******************************  RULES ******************************* #

all : librarys $(DIR_OBJ) $(NAME)

librarys :
	@$(MAKE) readline --no-print-directory
	@$(MAKE) -C $(DIR_LIB) --no-print-directory

$(NAME) : $(OBJ) $(LXR_OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LXR_OBJ) $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) -o $@
	@echo "Compiled"

rdline :
	@cd ./readline/ &> /dev/null && ./configure &> /dev/null
	@make -C ./readline/ &> /dev/null

$(DIR_OBJ)%.o: $(DIR_SRC)%.c Makefile $(LIB_A)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 $(INCLUDE) -c $< -o $@
	@echo "${YELLOW}Compiling obj $@...${RESET}"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

clean	:
#	@$(MAKE) -C libft clean --no-print-directory
	@$(RM) $(DIR_OBJ)
	@printf "${RED}Objs deleted\n${RESET}"

fclean	: clean
#	@$(MAKE) -C libft cleaname --no-print-directory
	@$(RM) $(NAME)
	@printf "${RED}Minishell deleted\n${RESET}"
	@$(MAKE) -C readline clean --no-print-directory

norm	:
	@printf "${PURPLE}SEARCHING FOR A PRINTF IN THE PROJECT: "
	@printf "%i \n${RESET}" $(shell grep "	printf" *.c | wc -l)
	@printf "${YELLOW}Norminette...\n${RESET}"
	@printf "${RED}"
	@norminette src/*/*.c src/*.c inc/*.h > test && printf "$(GREEN)\t[OK]\n" || grep Error test
	@printf "${RESET}"
	@rm test

re		: fclean all

.PHONY : all clean fclean re librarys rdline
