NAME	= pipex
BONUS	= ./bonus/../pipex
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
INC		= -I libft/includes/ -I includes
SRC		= mandatory/pipex.c mandatory/pipex_process.c mandatory/pipex_parse.c
SRC_BNS	= bonus/pipex_bonus.c bonus/pipex_process_bonus.c bonus/pipex_parse_bonus.c
LIB		= -L libft -lft
OBJ		= $(SRC:.c=.o)
OBJ_BNS	= $(SRC_BNS:.c=.o)
RM		= rm -f

all			: $(NAME)

bonus		: $(BONUS)

$(NAME) 	: $(OBJ)
	make -C libft
	$(CC) -o $@ $^ $(LIB)

$(BONUS) 	: $(OBJ_BNS)
	make -C libft
	$(CC) -o $@ $^ $(LIB)

.c.o		:
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY		: all bonus clean fclean re

clean		:
	make clean -C libft
	$(RM) $(OBJ)
	$(RM) $(OBJ_BNS)

fclean		: clean
	$(RM) libft/libft.a
	$(RM) $(NAME)

re			: fclean
	make all

re_bonus	: fclean
	make bonus
