# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 21:23:27 by antoda-s          #+#    #+#              #
#    Updated: 2023/12/06 10:47:51 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name
NAME 		= minishell
NAMET 		= test

# libs and includes
LIBFT 		= libft.a


LFT_PATH 	= ./libft/

# includes dir
INCLUDES 	= ./include/

# sources and objects dirs
SRCDIR 	= srcs/
OBJDIR 	= build/

SRCDIRT 	= s-tester/
OBJDIRT 	= builder/

# sources and objects base project
# FILES	=	main.c 				# Top level function
FILES 	=	1ms_main.c
FILES	+=	2ms_signal.c
FILES	+=	3ms_parser.c
FILES 	+=	4ms_quotes.c
FILES 	+=	5ms_tokens.c
FILES 	+=	6ms_env.c
FILES 	+=	7ms_exec.c
FILES	+=	99ms_error.c
FILES	+=	999ms_free.c
FILES	+=	9999ms_debug.c

TEST	=	test.c
TEST	+=	test1.c
TEST	+=	test2.c

SRC = $(addprefix $(SRCDIR), $(FILES))
OBJ = $(addprefix $(OBJDIR), $(FILES:.c=.o))

SRCT = $(addprefix $(SRCDIRT), $(TEST))
OBJT = $(addprefix $(OBJDIRT), $(TEST:.c=.o))

#compilation
CC 			= cc
CF 			= -Wall -Wextra -Werror -g
I_HEADER	= -I include
I_LIBFT 	= -I libft
LNK_LIBFT 	= -L $(LFT_PATH) -lft
LNK_READLINE = -lreadline


LEAKS 		= valgrind
LEAKS_FILE	= valgrind-log.txt
LF 			= --leak-check=full \
        		--show-leak-kinds=all \
        		--track-origins=yes \
        		--verbose \
        		--log-file=$(LEAKS_FILE) \
        		./$(NAME) # args??

# common commands
RM 			= rm -f

#Colors:
GRN		=	\e[38;5;118m
YLW		=	\e[38;5;226m
RED		=	\e[38;5;196m
BLU		=	\e[38:5:31m
WTH		=	\e[0m
CYN		= \33[1;36m
RESET	= \033[0m
BOLD	= \033[1m

# messages
_INFO		=	$(WTH)[$(CYN)INFO$(WTH)]
_SUCCESS	=	$(WTH)[$(GRN)$(BOLD)READY$(WTH)]
_WARNING	=	$(WTH)[$(YLW)WARNING$(WTH)]
_ERROR		=	$(WTH)[$(RED)ERROR$(WTH)]

# rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@printf "\n$(_SUCCESS) $(GRN)$(NAME) objects!$(WTH)\n"
	@printf "$(_INFO) $(CYN)Generating $(NAME) executable...$(WTH)\n"
	@$(CC) $(CF) $(OBJ) $(LNK_LIBFT) $(LNK_READLINE) -o $@
	@printf "$(GRN)█$(WHT)"
	@printf "\n$(_SUCCESS) $(GRN)$(NAME) executable!$(WTH)\n\n"

mkbuilddir:
	@mkdir -p $(OBJDIR)
	@printf "$(_INFO) $(CYN)Compiling source files...$(WTH)\n"

$(OBJDIR)%.o: $(SRCDIR)%.c | mkbuilddir
	@$(CC) $(CF) -c $(I_LIBFT) $(I_HEADER) $< -o $@
	@printf "$(YLW)█$(WHT)"

test: $(NAMET)

$(NAMET): $(LIBFT) $(OBJT)
	@printf "\n$(GRN)$(NAMET) objects ready!$(WTH)\n\n"
	@printf "\n$(CYN)Generating $(NAMET) executable...$(WTH)\n"
	@$(CC) $(CF) $(OBJT) $(LNK_LIBFT) $(LNK_READLINE) -o $@
	@printf "$(GRN)█$(WHT)"
	@printf "\n$(GRN)$(NAMET) ready!$(WTH)\n\n"


buildt:
	@mkdir -p $(OBJDIRT)
	@printf "\n$(CYN)Compiling test files...$(WTH)\n"

$(OBJDIRT)%.o: $(SRCDIRT)%.c | buildt
	@$(CC) $(CF) -c $(I_LIBFT) $(I_HEADER) $< -o $@
	@printf "$(YLW)█$(WHT)"

$(LIBFT):
	@printf "\n$(_INFO) $(CYN)Generating Libft...$(WTH)\n"
	@make -C $(LFT_PATH)
	@printf "$(_INFO) $(GRN)Libft created!$(WTH)\n\n"

re: fclean all

# rebonus: fclean bonus

leaks:
	$(LEAKS) $(LF)
	@printf "$(GRN)Leaks log ready! Check valgrind-out.txt $(WTH)\n\n"

cleanleaks:
	@$(RM) $(LEAKS_FILE)

clean:
	@printf "\n$(YLW)Cleaning all object files from project...$(WTH)\n"
	$(RM) -rf $(OBJ) $(OBJDIR)
	@printf "$(GRN)All object files removed!$(WTH)\n\n"

fclean: clean
	@printf "\n$(YLW)Cleaning $(NAME) and additional files...$(WTH)\n"
	@$(RM) -rf $(NAME)
	@printf "$(GRN)$(NAME) and additional files removed!$(WTH)\n\n"
	@printf "$(YLW)Cleaning Libft...$(WTH)\n"
	@make fclean -C $(LFT_PATH)
	@printf "$(GRN)All libraries removed!$(WTH)\n\n"
	@printf "$(YLW)Cleaning Leaks log file.$(WTH)\n"
	@make cleanleaks
	@printf "$(GRN)Leaks log file deleted.$(WTH)\n\n"

fcleant:
	@printf "\n$(YLW)Cleaning all object files from project...$(WTH)\n"
	@$(RM) -rf $(OBJT) $(OBJDIRT)
	@printf "$(GRN)All object files removed!$(WTH)\n\n"
	@printf "\n$(YLW)Cleaning $(NAMET) and additional files...$(WTH)\n"
	@$(RM) -rf $(NAMET)
	@printf "$(GRN)$(NAMET) and additional files removed!$(WTH)\n\n"


# install:
# 	sudo apt-get install gcc make xorg libxext-dev libbsd-dev -y
# 	@printf "$(GRN)All dependencies ready!$(WTH)\n\n"

.PHONY: show clean fclean re rebonus all bonus build

show:
	@echo ""
	@echo "$(YLW)ALL PATHS (*invoked with > make show*) $(WTH)]"
	@echo ""
	@echo "$(YLW)██ Current directory    : $(WTH)$(CURDIR) $(WTH)"
	@echo "$(GRN)██ LIBFT Directory      : $(WTH)$(LFT_PATH)$(WTH) $(WTH)"
	@echo "$(RED)██ Sources directory    : $(WTH)./$(SRCDIR)$(WTH)"
	@echo "$(YLW)██ Include directory    : $(WTH)$(INCLUDES)"
	@echo "$(CYN)██ Objects Directory    : $(WTH)./$(OBJDIR)$(WTH)"
	@echo "$(YLW)██ Executable directory : $(WTH)$(CURDIR) $(WTH)"
	@echo ""
	@echo "$(GRN)██ LIBFT File           : $(WTH)$(LIBFT) $(WTH)"
	@echo "$(RED)██ Sources files        : $(WTH)$(notdir $(FILES))"
	@echo "$(CYN)██ Objects files        : $(WTH)$(notdir $(OBJ))"
	@echo "$(YLW)██ Executable file      : $(WTH)$(notdir $(NAME))"
	@echo ""

.SILENT:
