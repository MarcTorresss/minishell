CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INCLUDE	=	-I./inc -I./readline
RM		=	rm -fr

NAME		=	minishell
COMP		=	./libft/libft.a

SRC			=	read.c enviroment.c
DIR_OBJ		=	obj/
DIR_SRC		=	src/
OBJ			=	$(addprefix $(DIR_OBJ),$(SRC:.c=.o))
RDLINE_ROOT =	readline/
LIBFT_ROOT	=	libft/

LIB_A		:=	$(RDLINE_ROOT)libreadline.a $(RDLINE_ROOT)libhistory.a $(LIBFT_ROOT)libft.a

LIB_ADD_DIR	:=	-L$(RDLINE_ROOT) -L$(LIBFT_ROOT)

LIB_SEARCH	:=	-lreadline -lhistory -ltermcap -lft

#=================HEADERS==================#
HEADERS		:=	$(INC_ROOT)
HEADERS		+=	$(addsuffix $(INC_ROOT),$(LIBFT_ROOT))

#=================COLORS===================#
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
BLUE		=	\033[0;34m
PURPLE		=	\033[0;35m
CYAN		=	\033[0;36m
RESET		=	\033[0m
#==================RULES===================#

all : librarys $(DIR_OBJ) $(NAME)

librarys :
	@$(MAKE) readline --no-print-directory
	@$(MAKE) -C $(LIBFT_ROOT) --no-print-directory

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) -o $@
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
