# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/13 17:48:46 by linyao            #+#    #+#              #
#    Updated: 2024/09/14 15:17:01 by linyao           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDE = libft.h ft_printf.h get_next_line.h get_next_line_bonus.h

SRC = ft_atoi.c  ft_memchr.c ft_split.c ft_strncmp.c \
      ft_bzero.c ft_memcmp.c ft_strchr.c ft_strnstr.c \
      ft_calloc.c ft_memcpy.c ft_strdup.c ft_strrchr.c \
      ft_isalnum.c ft_memmove.c ft_striteri.c ft_strtrim.c \
      ft_isalpha.c ft_memset.c ft_strjoin.c ft_substr.c \
      ft_isascii.c ft_putchar_fd.c ft_strlcat.c ft_tolower.c \
      ft_isdigit.c ft_putendl_fd.c ft_strlcpy.c ft_toupper.c \
      ft_isprint.c ft_putnbr_fd.c ft_strlen.c \
	ft_strcmp.c ft_getinx.c ft_realloc.c \
      ft_itoa.c ft_putstr_fd.c ft_strmapi.c ft_printf.c ft_convert.c ft_convert2.c \
		get_next_line.c get_next_line_utils.c

BONUS_FILES = ft_lstlast.c ft_lstadd_front.c ft_lstadd_back.c \
              ft_lstnew.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c \
              ft_lstsize.c ft_lstclear.c \
				get_next_line_bonus.c get_next_line_utils_bonus.c

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_FILES:.c=.o)

ALL_OBJ = $(OBJ) $(BONUS_OBJ)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(ALL_OBJ)
	ar rc $(NAME) $(ALL_OBJ)
	ranlib $(NAME)

%.o: %.c $(INCLUDE) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus
