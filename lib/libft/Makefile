# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/22 12:51:39 by myoung            #+#    #+#              #
#    Updated: 2023/11/29 00:09:48 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I .
AR = ar

FILES	+= ft_atoi.c ft_atol.c ft_bzero.c ft_calloc.c ft_charjoin.c \
	ft_free_str.c ft_intcmp.c \
	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_issign.c ft_isspace.c \
	ft_itoc_base.c ft_itoa.c ft_ftoa.c \
	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
	ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_split_set.c\
	ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
	ft_strnstr.c ft_strrev.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c\
	ft_toupper.c ft_strtrim_free.c\
	get_next_line.c \
	pf_all2s_1.c pf_all2s_2.c pf_fwp2f.c pf_fwp2s.c pf_printf.c \
	pf_tools.c pf_type_n.c pf_type_scp.c


SOURCES		=	$(addprefix srcs/, $(FILES))
OBJECTS		=	$(addprefix build/, $(FILES:.c=.o))

#Colors:
GRN		=	\e[38;5;118m
YLW		=	\e[38;5;226m
RED		=	\e[38;5;196m
BLU		=	\e[38:5:31m
WTH		=	\e[0m
CYN		:= \33[1;36m
RESET	:= \033[0m
BOLD	:= \033[1m

_INFO		=	$(WTH)[$(YLW)INFO$(WTH)]
_SUCCESS	=	$(WTH)[$(GRN)READY$(WTH)]

all: $(NAME)

clean:
	@rm -rf build

fclean: clean
	@rm -f $(NAME)

re: fclean all

$(NAME): $(OBJECTS)
	@echo
	@echo "$(_SUCCESS) $(GRN)$@ objects ready!$(WTH)"
	@echo "$(_INFO) $(CYN)Creating $@"
	@$(AR) crs $@ $(OBJECTS)
	@echo "$(_SUCCESS) $(GRN)$(NAME) ready!!$(WTH)"

build:
	@mkdir -p build/

build/%.o: srcs/%.c | build
	@printf "$(RED)█$(WHT)"
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re