/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f03.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:11:26 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/14 17:32:33 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



Lista de ficheiros e observaçoes quanto ao return_error:

void 100_main.c () 
{

/*#######################################################*/


	char	**envp_init(char **envp)

		if (!ms_envp) -> return_error("", errno, 1); // ja estava
		if (!ms_envp[i]) -> return_error("", errno, 1); // adicionada por mim


#######################################################

	int	ms_loop(t_script *s) 

#######################################################

	int	main(int argc, char **argv, char **envp) 

######################################################

}


void 200_signal.c ()
{

######################################################

void	signal_setter(void) /

#######################################################

void	sig_handler(int signum)

#######################################################

void	sig_handler_fork(int signum)

#######################################################

void	sig_handler_heredoc(int signum)

#######################################################

}


void 300_parser.c ()
{
######################################################

int	parse_commands(t_token *tk, t_command *cmd, int i, int j)

	estava: 	
	
	if (!cmd[i].argv)
		return (1);

	alterei:
	
	if (!cmd[i].argv)
		{
			return_error("", errno, 1); // adicionada Filipe 19fev
			return (ERROR);
		}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

	estava: 

		return (0);

	alterei:

		return (SUCCESS);		


######################################################

int	parser(t_script *s, char **line_buffer)

	if (!*line_buffer)
		return (return_error("readline error\n", 2, 0)); // já estava


	estava: 
	s->cmds = malloc(sizeof(t_command) * s->cmd_count);
	if (!s->cmds || s->cmd_count <= 0)
		return (free_tokens(&tk));

	alterei:

	if (!s->cmds || s->cmd_count <= 0)
	{
		return_error("", errno, 1);
		return (free_tokens(&tk));
	}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

	estava: 

		return (0);

	alterei:

		return (SUCCESS);

#######################################################
}


void 301_parser_syntax.c ()
{

######################################################


int	syntax_error_msg(char *tk_content, int errms, int errsys) -> exemplo a seguir ao recorrer a malloc

	status = return_error(msgr, errms, errsys); // ja estava


######################################################


int	syntax_checker(t_token *tk)

	uso na função de chamada do syntax_error_msg o qual recorre ao return_error


#######################################################

}


void 302_parser_cmd.c ()
{

######################################################

int	cmds_counter(t_token *tk)

#######################################################

}


void 303_parser_argc.c ()
{

######################################################

void	args_counter(t_token *tk, t_script *s)

#######################################################

}


void 304_parser_redir.c ()
{

######################################################


void	fnames_clear(t_command *cmds, int max, t_token *tk)


######################################################


int	redir(t_token *tk, t_redirection *file)

	ret = open(file->name, file->flag, 0644);
	if (ret == -1)
		return (return_error(file->name, 0, 1)); // já estava

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

	nas linhas 48, 59 e 64

		return (0);

	alterado para 

		return (SUCCESS);

#######################################################

}


void 305_parser_heredoc.c ()
{

######################################################

void	fill_heredoc(t_redirection *file)

#######################################################

}


void 400_termios.c ()
{

######################################################

void	termios_getter(struct termios *termios_p)

	err = tcgetattr(STDIN_FILENO, termios_p);
	if (err != 0)
		return_error("tcgetattr() error", err, 1); // já estava tratado

######################################################

void	termios_setter(struct termios *termios_p)

	err = tcsetattr(STDIN_FILENO, TCSAFLUSH, termios_p);
	if (err != 0)
		return_error("tcsetattr() error", err, 1); // já estava tratado

#######################################################

}


void 501_tk_builder.c ()
{

######################################################

void	tk_rm_blank(t_token *head)



######################################################

t_ops	tk_type_getter(const char *s)



######################################################

int	tk_getter(char *str, t_token **tk_lst)

	else if ((*str == '\"' || *str == '\'') && tk_quotes_checker(&str))
			return (ERROR); // nao preciso de fazer return (return_error("", ms_error, basherr)) pq é feito na chamada em tk_builder, certo?

######################################################

int	tk_builder(char **line, t_token **tk, t_script *s)

	if (tk_getter(*line, tk) == ERROR)
	{
		return_error("Syntax Error", 1, 0); 
		return (ERROR); // já estava feito
	}


#######################################################

}


void 502_tk_xpd.c ()
{

######################################################

int	tk_var_xpd_splits_count(char *otk)

	
#######################################################

char	**tk_var_xpd_init(char *otk)

	estava:

			ntks = (char **)malloc(sizeof(char *) * (spl + 1));

	adicionei

			ntks = (char **)malloc(sizeof(char *) * (spl + 1));
			if (!ntks)
			{
				return_error("", errno, 1);
				return (NULL);
			}


#######################################################

char	**tk_var_xpd(char *otk)


#######################################################

char	*tk_env_var_expander(char *otk, t_script *s)

#######################################################

}


void 503_tk_xpd_lst.c ()
{

######################################################

int	var_name_checker(char c)

	
#######################################################

int	var_firstchar(char c)

#######################################################

t_token	*tk_addnew(const char *str, int size, t_token_type type)

	estava:

	if (!tk)
		return (NULL);


	alterei:

	if (!tk)
	{
		return_error("", errno, 1);
		return (NULL);
	}


#######################################################

t_token	*tk_lst_last_getter(t_token *ltk)

	if (!ltk)
		return (NULL); // nap utilizei o return_error pq nao sei se o sistema trata este erro de nao ser passada lista


#######################################################

void	tk_lst_addback(t_token **ltk, t_token *ntk)

#######################################################

}


void 504_tk_xpd_count.c ()
{

######################################################

void	tk_var_xpd_dolar_c(char *otk, int *i)

#######################################################

void	tk_var_xpd_dquote_c(char *otk, int *spl, int *i)

#######################################################

void	tk_var_xpd_squote_c(char *otk, int *i)

#######################################################

void	tk_var_xpd_else_c(char *otk, int *i)

#######################################################

}


void 505_tk_xpd_filler.c ()
{

######################################################

char	*tk_xpd_var_filler(char *ntk, t_script *s)

#######################################################

char	*tk_xpd_filler(char ***ntks, t_script *s)

#######################################################

}


void 506_tk_xpd_split.c ()
{

######################################################

char	*tk_var_xpd_dolar(char *otk, int *i)

#######################################################

void	tk_var_xpd_dquote(char *otk, char ***ntks, int *spl, int *i)

#######################################################

void	tk_var_xpd_squote(char *otk, char ***ntks, int *spl, int *i)

#######################################################

void	tk_var_xpd_else(char *otk, char ***ntks, int *spl, int *i)

#######################################################

}


void 507_tk_quotes.c ()
{

######################################################

int	tk_quotes_checker(char **str)

	if (!(*str))
	{
		(*str) = tmp + ft_strlen(tmp);
		return (ERROR); 
		/*
		pelo que percebi a *str é " e vai procurar na str pela " que falta e 
		retornar ponteiro para essa posiçao, em caso de erro acho que basta o return(ERROR) 
		*/ 
	}

#######################################################

char	*tk_xpd_unquote(char *str)

######################################################

void	tk_trim_spaces(t_token *tk)

######################################################

}


void 600_env.c ()
{

######################################################

int	env_var_index_getter(char *var, char **envx)

	if (!envx)
		return (-1); // esperado retorno -1 ou >= 0 na chamada desta funçao em 840, 850, 880 e env_var_setter

#######################################################

int	env_var_setter(char *val, char *var, char ***envx)

	estava:

		*envx = malloc(sizeof(char *) * (1 + 1));


	alterei:

		*envx = malloc(sizeof(char *) * (1 + 1));
		if (!*envx)
		{
			return_error("", errno, 1); // adicionada Filipe 20fev
			return (ERROR);
		}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */


	estava
	
		return (0);

	alterei

		return (SUCCESS);

#######################################################

char	*envp_var_getter(char *var, char **envp)

	if (!envp)
		return (NULL); // apenas verificaçao, chamada na env_var_getter


	if (!ret)
		return (NULL); // apenas verificaçao, chamada na env_var_getter

#######################################################

char	*envt_var_getter(char *var, char **envp)

	if (!envp)
		return (NULL); // apenas verificaçao, chamada na env_var_getter


	if (!ret)
		return (NULL); // apenas verificaçao, chamada na env_var_getter

#######################################################

char	*env_var_getter(char *var, char **envp, char **envt) // chamada na 505, 820, 830 e 840

#######################################################

}


void 700_exec_start.c ()
{

######################################################

static int	get_path_index(char **envp)

#######################################################

char	**split_path(char **envp)

#######################################################

int execute(t_script *s)

estava:

if (s->cmd_count == 1)
	{
		if (exec_one(s, path))
			return (1);
	}

alterei:

if (s->cmd_count == 1)
	{
		if (exec_one(s, path))
			return (TRUE);
	}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

estava:

	else if (exec_many(s, path))
		return (1);

alterei:

	else if (exec_many(s, path))
		return (TRUE);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */


estava:

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &s->termios_p); // ao contrario do 400_termios.c, nao fiz return_error. deveria?
	//show_func(__func__, SUCCESS, NULL);
	return (0);

alterei: 

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &s->termios_p);
	//show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);

#######################################################

}


void 705_exec_type.c ()
{

######################################################

int exec_type(char *cmd)

#######################################################

}


void 710_exec_one.c ()
{

######################################################

int	exec_bi(int id, t_script *s, int i)

estava:

	return (0);

alterei:

	return (SUCCESS);

#######################################################

void	exec_ve(char **path, char **cmd, char **env)



para rever com Antonio:

	if (tmp[0] == '.' || tmp[0] == '/')
	{
		// falta atualizar a variável de ambiente SHLVL (o valor de SHLVL é acrescido em 1.)
		execve(*cmd, cmd, env);
		free(tmp); // se entrar no execve este free já nao acontece
		return ; // se entrar no execve este return já nao acontece
	}

######################################################

int	exec_one_fork(t_script *s, char **path) // funçao chamada no exec_one

estava:

	if (pid == -1)
		return (fork_error(path)); // a funçao fork_error faz sentido?

alterei:

	if (pid == -1)
	{
		// return (fork_error(path));
		//free_array(path); // estava a ser feito no fork error mas o exec_one tb o faz if exec_one_fork
		return (return_error("", errno, 1)); // alterado filipe 20 fev
	}

######################################################

int	exec_one(t_script *s, char **path)

para rever com Antonio:

	if (exec_one_fork(s, path)) 
		
			estava: free_array(path); // o exec_one_forks faz free a path no fork_error se pid == -1, double free???
			alterei: //free_array(path); // dava double free no env e pwd e deixou de dar

######################################################

}


void 720_exec_many.c ()
{

######################################################

int	exec_cmd_1(t_script *s, char **path, int *pipeout)

	estava:

		if (pipe(pipeout) == -1)
			return (pipe_error(path));

	alterei:

		if (pipe(pipeout) == -1)
	{
		free (path);
		return (return_error("", errno, 1)); // deveria escrever "Error: pipe failed\n"?
		//return (pipe_error(path)); // deverei usar esta funçao ou o return_error?
	}


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */


	estava:

		if (pid == -1)
			return (fork_error(path));

	alterei:

		if (pid == -1)
	{
		free (path);
		return (return_error("", errno, 1));
		//return (fork_error(path));
	}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

alterei de return (0); para return (SUCCESS);

#######################################################

int	exec_cmd_i(t_script *s, char **path, int **pipes, int i)

estava:

	if (!pipes)
		return (1);

alterei:

	if (!pipes)
		return (return_error("", errno, 1)); // nao precisa dar free tb a path?

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */


estava:

	if (pid == -1)
		return (fork_error(path));

alterei:

	if (pid == -1)
	{
		free (path); // a funçao fork_error dá free a path
		return (return_error("", errno, 1));
		//return (fork_error(path));
	}

#######################################################

int	exec_cmd_n(t_script *s, char **path, int *pipein)

	estava:

	if (pid == -1)
		return (fork_error(path));

alterei:

	if (pid == -1)
	{
		free (path); // a funçao fork_error dá free a path
		return (return_error("", errno, 1));
		//return (fork_error(path));
	}

#######################################################

int	exec_cmd_loop(t_script *s, char **path, int *pipe1, int *pipe2)

#######################################################

int	exec_many(t_script *s, char **path)

	alterei:
		 return (1); por return (ERROR);
		 return (0); por return (SUCCESS);

#######################################################

}


void 730_exec_childs.c ()
{

######################################################

void	ex_child_1(t_script *s, char **path, int *pipeout)

	exit_forks("pipe_std_setter", 1, s, path); // esta funçao chama já o return_error

	alterei:
	
		exit(SUCCESS);

#######################################################

void	ex_child_i(t_script *s, char **path, int **pipes, int i)

	chamada de exit_forks("pipe_std_setter", 1, s, path); // esta funçao chama já o return_error

	alterei:
	
		exit(SUCCESS);

#######################################################

void	ex_child_n(t_script *s, char **path, int *pipein, int i)

	exit_forks("pipe_std_setter", 1, s, path); // esta funçao chama já o return_error

	alterei:
	
		exit(SUCCESS);

#######################################################

void exec_go(t_script *s, char **path, int id, int i)



#######################################################

}


void 740_exec_redirs.c ()

{

######################################################

void	in_redir(t_script *s, int i, char **path)

	if (fdin == -1)
		exit_forks(s->cmds[i].in.name, 1, s, path); // funçao chama ja o return_error
	
	else if (fdin != STDIN_FILENO && dup2(fdin, STDIN_FILENO) == -1)
		exit_forks("Error: dup2 failed", 1, s, path); // funçao chama ja o return_error

#######################################################

void	out_redir(t_script *s, int i, char **path)

	if (fdout == -1)
		exit_forks(s->cmds[i].out.name, 1, s, path); // funçao chama ja o return_error

	else if (fdout != STDOUT_FILENO && dup2(fdout, STDOUT_FILENO) == -1)
		exit_forks("Error: dup2 failed", 1, s, path); // funçao chama ja o return_error

#######################################################

}


void 750_exec_heredoc.c ()
{

######################################################

void	error_message_heredoc(char *msg)

#######################################################

void	loop_heredoc(t_list *h, int pipe)

#######################################################

void	heredoc(t_script *s, int i, char **path)

	estava:
	
	if (pipe(pipe_tmp) == -1)
	{
		write(2, "Error: pipe failed\n", 19);
		free_cmds_path(s, path);
		exit(1);
	}

	alterei:

	if (pipe(pipe_tmp) == -1)
	{
		//write(2, "Error: pipe failed\n", 19);
		free_cmds_path(s, path);
		exit((return_error("", errno, 1)));
	}


	alterei:

		exit(ERROR); // alterado 20fev (estava exit(1)))

#######################################################

}


void 760_exec_pipes.c ()
{

######################################################

int	**pipe_init(char **path, int *pipe1, int *pipe2)

#######################################################

void	pipe_closer(int *pa, int *pb)

#######################################################

int	pipe_std_setter(int *pipe, int end)

	return (0); para return (SUCCESS);

#######################################################

}


void 799_exec_errors.c ()
{

######################################################

int	fork_error(char **path)

#######################################################

int	pipe_error(char **path)

#######################################################

}


void 810_bi_echo.c ()
{

######################################################

int	bi_echo_flag(char *str)

alterei: 

	return (FALSE); // estava 0
	return (true); // estava 1

######################################################

int	bi_echo(t_script *s, int n)

######################################################

int	bi_env_upd(t_script *s, int n)

#######################################################

}


void 820_bi_cd.c ()
{

######################################################

int	change_dir(char *path, char ***envp)

	ret = chdir(path);
	if (ret == -1)
		return (return_error(path, 1, 1)); // ja tratado

#######################################################

int	bi_cd(t_script *s, int n)

	estava:

		if (home == NULL)
		{
			ft_putendl_fd("Minishell: cd: HOME not set", 2);
			free(home);
			return (1);
		}

	alterei: // ver com o Antonio, nao esta a funcionar como deveria

		printf("HOME:%s\n", home); // este teste é pq se fizermos unset HOME, cd nao está a entrar no caso abaixo e deveria
		if (home == NULL)
		{
			//ft_putendl_fd("Minishell: cd: HOME not set", 2);
			free(home);
			return (return_error("Minishell: cd: HOME not set", 1, 0));
		}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */


	estava: 


		if (s->cmds[n].argc > 2)
		{
			//env_var_setter(s->cmds[n].argv[1],"_", &s->envp);
			ft_putendl_fd("Minishell: cd: too many arguments", 2);
			//show_func(__func__, ERROR, NULL);
			return (1);
		}

	
	alterei:

		if (s->cmds[n].argc > 2)
		{
			//env_var_setter(s->cmds[n].argv[1],"_", &s->envp);
			// ft_putendl_fd("Minishell: cd: too many arguments", 2);
			//show_func(__func__, ERROR, NULL);
			return (return_error("Minishell: cd: too many arguments", 1, 0));
		}


#######################################################

}


void 830_bi_pwd.c ()
{

######################################################

int	bi_pwd(t_script *s, int n)

#######################################################

}


void 840_bi_export.c ()
{

######################################################

int	var_name_check(char *var)

#######################################################

void	bi_export_upd_var(t_script *s, int n, int i)

#######################################################

void	bi_export_new_var(t_script *s, int n, int i)

#######################################################

int	export_status(t_script *s, int n)

	questao:
	
		if (!s->envp)
			return (1); // deveria fazer return(return_error("", 1, 0)) ???? no caso de nao haver envp na *s 

#######################################################

int	bi_export(t_script *s, int n)


#######################################################

}


void 850_bi_unset.c ()
{

######################################################

int	bi_unset(t_script *s, int n)

#######################################################

int	bi_unset_envt(t_script *s, int n)

#######################################################

}


void 860_bi_env.c ()
{

######################################################

int	bi_env(t_script *s, int n)

#######################################################

}


void 870_bi_exit.c ()
{

######################################################


alterei:

if (ft_atoi(s->cmds[n].argv[1]) == 0)
		exit (0);

if (ft_is_str_digit(s->cmds[n].argv[1]) == 1 || !ft_atoi(s->cmds[n].argv[1]))

#######################################################

int	exit_error_args(const char *msg, int system) 

######################################################

int	exit_error_notnum(const char *msg, int system)

######################################################

int	bi_exit(t_script *s, int n)

// falta atualizar a variável de ambiente SHLVL (o valor de SHLVL é decrescido em 1.)

estava:

	if (s->cmds[n].argc > 2)
	{
		return (exit_error_args("too many arguments\n", 2));
	}
	if (ft_is_str_digit(s->cmds[n].argv[1]) == 1)
	{
		//show_func(__func__, ERROR, NULL);
		exit_error_notnum(s->cmds[n].argv[1], 2);
		free_commands(s->cmds, s->cmd_count);
		free_array(s->envp);
		exit (2);
	}

alterei: 
// alterei a ordem pq ao testar 'exit d 4' dizia que tem demasiados argumentos e o bash analisa primeiro o conteudo e nao a quantidade

	if (ft_is_str_digit(s->cmds[n].argv[1]) == 1)
	{
		//show_func(__func__, ERROR, NULL);
		exit_error_notnum(s->cmds[n].argv[1], 2); // podemos usar a return_error, certo???
		free_commands(s->cmds, s->cmd_count);
		free_array(s->envp);
		exit (2);
	}
	if (s->cmds[n].argc > 2)
	{
		return (exit_error_args("too many arguments\n", 2)); // podemos usar a return_error, certo???
	}


######################################################

}


void 880_bi_equal.c ()
{

######################################################

void	bi_equal_upd(t_script *s, int n, int i)

#######################################################

void	bi_equal_new(t_script *s, int n, int i)

#######################################################

int	bi_equal(t_script *s, int n)

#######################################################

}


void 900_free.c ()
{

######################################################

void	free_array(char **array)

#######################################################

int	free_tokens(t_token **head)

#######################################################

/// @return 		SUCCESS or ERROR ?? needs coherence check
int	free_commands(t_command *cmd, int cmd_idx)

	return (1); // esclarecer

#######################################################

void	free_cmds_path(t_script *script, char **path)

#######################################################

void	exit_forks(char *msg, int errms, t_script *s, char **path)

	return_error(msg, errms, 1); // já tem chamada de return_error

#######################################################

}


void 910_errors.c ()
{

######################################################

int	export_error(const char *msg, int errms) 
// exemplo a seguir para utilizar variaveis que precisem de malloc e chamada de return_error

#######################################################

int	return_error(const char *msg, int errms, int errbash)
// definiçao de exit_status no minishell ou perror

#######################################################

char	**ordered_array(char **s, char t) // WTF!!!!!!!!!!!

#######################################################

}


void 999_debug.c ()
{

######################################################


#######################################################

}

