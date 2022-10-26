# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/28 18:42:35 by sbrella           #+#    #+#              #
#    Updated: 2022/10/26 15:52:07 by mproveme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft/libft.a

LIBFT_OUT_FILES = ft_atoi.o \
ft_bzero.o \
ft_calloc.o \
ft_isalnum.o \
ft_isalpha.o \
ft_isascii.o \
ft_isdigit.o \
ft_isprint.o \
ft_itoa.o \
ft_memchr.o \
ft_memcmp.o \
ft_memcpy.o \
ft_memmove.o \
ft_memset.o \
ft_putchar_fd.o \
ft_putendl_fd.o \
ft_putnbr_fd.o \
ft_putstr_fd.o \
ft_split.o \
ft_strchr.o \
ft_strdup.o \
ft_striteri.o \
ft_strjoin.o \
ft_strlcat.o \
ft_strlcpy.o \
ft_strlen.o \
ft_strmapi.o \
ft_strncmp.o \
ft_strnstr.o \
ft_strrchr.o \
ft_strrstr.o \
ft_strtrim.o \
ft_substr.o \
ft_tolower.o \
ft_toupper.o \
ft_putchar.o \
ft_putnstr.o

LIBFT_OUT = $(addprefix ./libft/, $(LIBFT_OUT_FILES))

LEXER = f_create_token.c \
f_get_substr.c \
f_parser.c \
f_readers.c \
f_token_by_type.c \
main.c \
t_env.c \
t_word.c \
f_fill_content.c \
f_optimize_tokens.c \
f_parser_utils.c \
f_redefine_str.c \
f_token_to_cmd.c \
t_keysearch.c \
f_free_array.c \
f_optimize_tokens_utils.c \
f_readers2.c \
f_syntax_checker.c \
f_token_to_cmd_utils.c \
t_cmd.c \
t_token.c \
t_red.c
# f_utils.c \
# f_utils2.c

LEXER_SRCS = $(addprefix ./lexer/, $(LEXER))

SRCS =	main.c\
sort_env.c \
builtins_1.c \
builtins_2.c \
builtins_3.c

OUT = main.o \
builtins_1.o \
builtins_2.o \
builtins_3.o

INCLUDES = ./minishell.h

LIB_INC = ./libft/

FLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(LIBFT):
	make -C ./libft

#original make
#uncomment when libft issue is resolved
# $(NAME): $(OUT) $(INCLUDES) $(LIBFT)
# 	gcc $(FLAGS) $(SRCS) -o $(NAME) -I $(LIB_INC) $(LIBFT) -lreadline

$(NAME): $(OUT) $(INCLUDES) $(LIBFT)
	gcc $(FLAGS) $(SRCS) $(LEXER_SRCS) -o $(NAME) -I $(LIB_INC) $(LIBFT) -lreadline

clean:
	make -C libft/ fclean
	rm -f $(OUT)

fclean: clean
	rm -f $(NAME)

re: fclean all
