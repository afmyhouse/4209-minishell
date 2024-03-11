# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 21:23:27 by antoda-s          #+#    #+#              #
#    Updated: 2024/03/11 00:47:44 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name
NAME 		= minishell
NAME_A 		= minishell
NAME_L 		= minishell

# libs and includes
LIBFT 		= libft.a


LFT_PATH 	= ./libft/

# includes dir
INCLUDES 	= ./include/

# sources and objects dirs
SRCDIR 	= srcs/
OBJDIR 	= build/

# sources and objects base project
# FILES	=	main.c 				# Top level function
FILES	=	100_main.c
FILES	+=	200_signal.c
FILES	+=	300_parser.c
FILES	+=	301_parser_syntax.c
FILES	+=	302_parser_cmd.c
FILES	+=	303_parser_argc.c
FILES	+=	304_parser_redir.c
FILES	+=	305_parser_heredoc.c
FILES	+=	400_termios.c
FILES	+=	501_tk_builder.c
FILES	+=	502_tk_xpd.c
FILES	+=	503_tk_xpd_lst.c
FILES	+=	504_tk_xpd_count.c
FILES	+=	505_tk_xpd_filler.c
FILES	+=	506_tk_xpd_split.c
FILES	+=	507_tk_quotes.c
FILES	+=	600_env_setter.c
FILES	+=	610_env_getter.c
FILES	+=	700_exec_start.c
FILES	+=	705_exec_type.c
FILES	+=	710_exec_one.c
FILES	+=	711_exec_bi.c
FILES	+=	712_exec_ve.c
FILES	+=	720_exec_many.c
FILES	+=	730_exec_childs.c
FILES	+=	731_exec_go.c
FILES	+=	740_exec_redirs.c
FILES	+=	750_exec_heredoc.c
FILES	+=	760_exec_pipes.c
FILES	+=	799_exec_errors.c
FILES	+=	810_bi_echo.c
FILES	+=	820_bi_cd.c
FILES	+=	830_bi_pwd.c
FILES	+=	840_bi_export.c
FILES	+=	845_bi_export_status.c
FILES	+=	850_bi_unset.c
FILES	+=	860_bi_env.c
FILES	+=	870_bi_exit.c
FILES	+=	880_bi_equal.c
FILES	+=	890_bi_append.c
FILES	+=	900_free.c
FILES	+=	910_errors.c
FILES	+=	999_debug.c

SRC = $(addprefix $(SRCDIR), $(FILES))
OBJ = $(addprefix $(OBJDIR), $(FILES:.c=.o))

#compilation
CC 			= cc
CF 			= -Wall -Wextra -Werror -g
CFA 			= -Wall -Wextra -Werror -g -fsanitize=address
CFL 			= -Wall -Wextra -Werror -g -fsanitize=leak
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
_INFO		=	$(WTH)[$(CYN) INFO$(WTH)]
_SUCCESS	=	$(WTH)[$(GRN)$(BOLD)READY$(WTH)]
_WARNING	=	$(WTH)[$(YLW)WARNING$(WTH)]
_ERROR		=	$(WTH)[$(RED)ERROR$(WTH)]

# rules
all: $(LIBFT) $(OBJ) $(NAME)
	@printf "\n$(_SUCCESS) $(GRN)$(NAME) executable ready!$(WTH)\n\n"

$(NAME):
	@printf "\n$(_SUCCESS) $(GRN)$(NAME) objects ready!                $(WTH)\n"
	@printf "\n$(_INFO) $(CYN)Generating $(NAME) executable...$(WTH)\n"
	$(CC) $(CFL) $(OBJ) $(LNK_LIBFT) $(LNK_READLINE) -o $@
	@printf "$(GRN)█$(WHT)"

mkbuilddir:
	@mkdir -p $(OBJDIR)
	@printf "\n$(_INFO) $(CYN)Compiling source files...$(WTH)\n"

$(OBJDIR)%.o: $(SRCDIR)%.c | mkbuilddir
#	@printf "$(_INFO) $(CYN)Compiling source files...$(WTH)%-33.33s\r" $@
	$(CC) $(CF) -c $(I_LIBFT) $(I_HEADER) $< -o $@
	@printf "$(YLW)█$(WHT)"

sana: $(LIBFT) $(OBJ) $(NAME_A)
	@printf "\n$(_SUCCESS) $(GRN)$(NAME) executable ready!$(WTH)\n\n"

$(NAME_A):
	@printf "\n$(_SUCCESS) $(GRN)$(NAME) objects ready!                $(WTH)\n"
	@printf "\n$(_INFO) $(CYN)Generating $(NAME) address sanitizer executable...$(WTH)\n"
	$(CC) $(CFA) $(OBJ) $(LNK_LIBFT) $(LNK_READLINE) -o $@
	@printf "$(GRN)█$(WHT)"

sanl: $(LIBFT) $(OBJ) $(NAME_L)
	@printf "\n$(_SUCCESS) $(GRN)$(NAME) executable ready!$(WTH)\n\n"

$(NAME_L):
	@printf "\n$(_SUCCESS) $(GRN)$(NAME) objects ready!                $(WTH)\n"
	@printf "\n$(_INFO) $(CYN)Generating $(NAME) leak sanitizer executable...$(WTH)\n"
	$(CC) $(CFL) $(OBJ) $(LNK_LIBFT) $(LNK_READLINE) -o $@
	@printf "$(GRN)█$(WHT)"

$(LIBFT):
	@printf "\n$(_INFO) $(CYN)Generating Libft...$(WTH)\n"
	@make -s -C $(LFT_PATH)
#	@printf "$(_INFO) $(GRN)Libft created!$(WTH)\n\n"

re: fclean all

rea: fclean sana

rel: fclean sanl

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
	@make fclean -s -C $(LFT_PATH)
	@printf "$(GRN)All libraries removed!$(WTH)\n\n"
	@printf "$(YLW)Cleaning Leaks log file.$(WTH)\n"
	@make -s cleanleaks
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
