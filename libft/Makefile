NAME	= libft.a
CC		= gcc
AR		= ar rcs
CFLAGS	= -Wall -Werror -Wextra
INC		= -I includes
SRC		= ft_itoa.c	ft_putstr_fd.c	ft_strmapi.c \
			ft_atoi.c	ft_memchr.c	ft_split.c	ft_strncmp.c \
			ft_bzero.c	ft_memcmp.c	ft_strchr.c	ft_strnstr.c \
			ft_strcat.c ft_strcmp.c ft_strncat.c ft_strstr.c \
			ft_calloc.c	ft_memcpy.c	ft_strdup.c	ft_strrchr.c \
			ft_isalnum.c	ft_memmove.c	ft_striteri.c	ft_strtrim.c \
			ft_isalpha.c	ft_memset.c	ft_strjoin.c	ft_substr.c \
			ft_isascii.c	ft_putchar_fd.c	ft_strlcat.c	ft_tolower.c \
			ft_isdigit.c	ft_putendl_fd.c	ft_strlcpy.c	ft_toupper.c \
			ft_isprint.c	ft_putnbr_fd.c	ft_strlen.c \
			ft_lstadd_back.c	ft_lstlast.c \
			ft_lstadd_front.c \
			ft_lstclear.c	ft_lstnew.c \
			ft_lstdelone.c	ft_lstsize.c \
			ft_printf/ft_flags.c	  ft_printf/ft_print_ptr_pct.c	 ft_printf/utils_2.c \
			ft_printf/ft_printf.c	  ft_printf/ft_print_str_char.c  ft_printf/utils_3.c \
			ft_printf/ft_print_hex.c  ft_printf/ft_print_uint.c	 ft_printf/utils_4.c \
			ft_printf/ft_print_int.c  ft_printf/utils_1.c \
			get_next_line/get_next_char.c	     get_next_line/get_next_line_multi.c \
			get_next_line/get_next_char_utils.c  get_next_line/get_next_line_utils1.c \
			get_next_line/get_next_line.c	     get_next_line/get_next_line_utils2.c
OBJ		= $(SRC:.c=.o)
RM		= rm -f

all		: $(NAME)

$(NAME) : $(OBJ)
	$(AR) $@ $^

.c.o	:
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY	: all clean fclean re

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re		: fclean
	make all
