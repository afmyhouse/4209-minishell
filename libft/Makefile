# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/22 12:51:39 by myoung            #+#    #+#              #
#    Updated: 2024/02/02 20:26:05 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I .
AR = ar

# INT TESTING FUNCTIONS
FILES	+= ft_intcmp.c
FILES	+= ft_intmax.c
FILES	+= ft_intmin.c
# CHARACTERS TESTING & MANIPULATION FUNCTIONS
FILES	+= ft_isalnum.c
FILES	+= ft_isalpha.c
FILES	+= ft_isascii.c
FILES	+= ft_isdigit.c
FILES	+= ft_isprint.c
FILES	+= ft_issign.c
FILES	+= ft_isspace.c
FILES	+= ft_tolower.c
FILES	+= ft_toupper.c
# NUMBER TO STRING TO NUMBER FUNCTIONS
FILES	+= ft_atoi.c
FILES	+= ft_atol.c
FILES	+= ft_itoc_base.c
FILES	+= ft_itoa.c
FILES	+= ft_ftoa.c
# LIST MANAGEMENT FUNCTIONS
FILES	+= ft_lstadd_back.c
FILES	+= ft_lstadd_front.c
FILES	+= ft_lstclear.c
FILES	+= ft_lstdelone.c
FILES	+= ft_lstiter.c
FILES	+= ft_lstlast.c
FILES	+= ft_lstmap.c
FILES	+= ft_lstnew.c
FILES	+= ft_lstsize.c
# MEMORY MANAGEMENT FUNCTIONS
FILES	+= ft_calloc.c
FILES	+= ft_memcpy.c
FILES	+= ft_memchr.c
FILES	+= ft_memcmp.c
FILES	+= ft_memcpy.c
FILES	+= ft_memmove.c
FILES	+= ft_memset.c
FILES	+= ft_bzero.c
FILES	+= ft_free_arr.c
FILES	+= ft_free.c
# PUT STDOUT & FD FUNCTIONS
FILES	+= ft_charjoin.c
FILES	+= ft_putchar.c
FILES	+= ft_putchar_fd.c
FILES	+= ft_putendl.c
FILES	+= ft_putendl_fd.c
FILES	+= ft_putnbr.c
FILES	+= ft_putnbr_fd.c
FILES	+= ft_putstr.c
FILES	+= ft_putstr_fd.c
FILES	+= ft_split_set.c\
# STRING MANIPULATION FUNCTIONS
FILES	+= ft_split.c
FILES	+= ft_strchr.c
FILES	+= ft_strdup.c
FILES	+= ft_striteri.c
FILES	+= ft_strjoin_free.c
FILES	+= ft_strjoin.c
FILES	+= ft_strlcat.c
FILES	+= ft_strlcpy.c
FILES	+= ft_strlen.c
FILES	+= ft_strmapi.c
FILES	+= ft_strncmp.c
FILES	+= ft_strnstr.c
FILES	+= ft_strrev.c
FILES	+= ft_strrchr.c
FILES	+= ft_strtrim.c
FILES	+= ft_substr.c
FILES	+= ft_strtrim_free.c
# GET NEXT LINE FUNCTIONS
FILES	+= get_next_line.c
# PRINTF FUNCTIONS
FILES	+= pf_printf.c
FILES	+= pf_all2s_1.c
FILES	+= pf_all2s_2.c
FILES	+= pf_fwp2f.c
FILES	+= pf_fwp2s.c
FILES	+= pf_tools.c
FILES	+= pf_type_n.c
FILES	+= pf_type_scp.c

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

_INFO		=	$(WTH)[$(YLW) INFO$(WTH)]
_SUCCESS	=	$(WTH)[$(GRN)READY$(WTH)]

all: $(NAME)

clean:
	@rm -rf build

fclean: clean
	@rm -f $(NAME)

re: fclean all

$(NAME): $(OBJECTS)
	@echo
	@echo "$(_SUCCESS) $(GRN)$@ objects ready!                          $(WTH)"
#	@echo "$(_INFO) $(CYN)Creating $@"
	@$(AR) crs $@ $(OBJECTS)
	@echo "$(_SUCCESS) $(GRN)$(NAME) ready!!$(WTH)"

build:
	@mkdir -p build/

build/%.o: srcs/%.c | build
#	@printf "$(CYN)Generating libft objects... %-33.33s\r" $@
	@printf "$(RED)█$(WHT)"
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
