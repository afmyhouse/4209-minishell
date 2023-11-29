# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/13 14:58:45 by sgoffaux          #+#    #+#              #
#    Updated: 2022/09/20 11:18:46 by sgoffaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

LIBFT_A		=	libft.a
LIBFT_DIR	=	libft/
LIBFT		=	$(addprefix $(LIBFT_DIR), $(LIBFT_A))

CC			=	gcc
INCLUDE		=	includes
CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDE)
RM			=	rm -f

EXEC_DIR	=	srcs/execution
PARSING_DIR	=	srcs/parsing
BUILTIN_DIR	=	srcs/builtin

SRCS		=	main.c \
				$(BUILTIN_DIR)/builtin_cd.c \
				$(BUILTIN_DIR)/builtin_echo.c \
				$(BUILTIN_DIR)/builtin_env.c \
				$(BUILTIN_DIR)/builtin_exit.c \
				$(BUILTIN_DIR)/builtin_export.c \
				$(BUILTIN_DIR)/builtin_pwd.c \
				$(BUILTIN_DIR)/builtin_unset.c \
				$(BUILTIN_DIR)/builtin_utils_2.c \
				$(BUILTIN_DIR)/builtin_utils.c \
				$(EXEC_DIR)/exec_errors.c \
				$(EXEC_DIR)/exec_onecmd_pipex.c \
				$(EXEC_DIR)/exec_pipes_forks.c \
				$(EXEC_DIR)/exec_pipes_utils.c \
				$(EXEC_DIR)/exec_pipes.c \
				$(EXEC_DIR)/exec.c \
				$(EXEC_DIR)/heredoc.c \
				$(EXEC_DIR)/path_handling.c \
				$(PARSING_DIR)/parsing_utils.c \
				$(PARSING_DIR)/parsing.c \
				$(PARSING_DIR)/replace_env_utils.c \
				$(PARSING_DIR)/replace_env.c \
				$(PARSING_DIR)/tokenizer_utils.c \
				$(PARSING_DIR)/tokenizer.c \
				srcs/free.c \
				srcs/signal.c \
				srcs/utils.c \

OBJS		=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -ltermcap
			@echo "\nLinked into executable \033[0;32mminishell\033[0m."

$(LIBFT):
			@echo "Compiling libft.a"
			@$(MAKE) bonus -s -C $(LIBFT_DIR)

.c.o:
			@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

localclean:
			@$(RM) $(OBJS)
			@echo "Removed object files."

clean:		localclean
			@$(MAKE) clean -s -C $(LIBFT_DIR)
			@echo "Clean libft."

fclean:		localclean
			@$(MAKE) fclean -s -C $(LIBFT_DIR)
			@echo "Full clean libft."
			@$(RM) $(NAME)
			@echo "Removed executable."

re:			fclean all

.PHONY:		all clean fclean localclean re