/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:32:53 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/05 13:13:20 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/signal.h> 
# include <termios.h>  
# include <errno.h>
# include <limits.h>
# include "libft/libft.h"

# define S_QUOTE	39
# define D_QUOTE	34
# define PIPE		1
# define RD_IN		2	// < filename
# define RD_OUT_T	3	// > filename
# define RD_OUT_A	4	// >> filename
# define RD_HEREDOC	5	// << delimiter
# define CMD		6
# define ARG		7
# define DELIMITER	8
# define INFILE		9
# define OUTFILE_T	10
# define OUTFILE_A	11

extern volatile sig_atomic_t g_signo;

#define GREEN "\001\033[1;92m\002"
#define AQUA "\001\033[1;36m\002"
#define DEFAULT "\001\033[0m\002"

//una lista per fare il parsing
typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
}			t_list;

//una lista per gestire le variabili di ambiente, in una metto la KEY e in un'altra
// il value, il '=' non lo metto, se poi devo stampare l'elenco di variabili lo
//aggiungo dopo
typedef struct s_envlst
{
	char			*key;
	char			*value;
	struct s_envlst	*next;
}			t_envlst;

//una lista per gestire le redirections, in un campo metto il nome del file o il
//delimitatore nel caso di heredoc, in un'altroil type (filein, fileout, append, heredoc)
//e un terzo per il fd nel caso di heredoc
typedef struct s_redirlst
{
	char				*content;
	int					type;
	int					heredoc_fd;
	struct s_redirlst	*next;
}		t_redirlst;

//questo e il nodo che deve arrivare al executor:
typedef struct s_cmdblock
{
	char				**cmd;//un array di str: 0 = cmd, 1 = arg 1, 2 = arg 2...
	t_redirlst			*redir;//ogni nodo contiene il nome del file e il type (filein, fileout, append, heredoc)
	struct s_cmdblock	*next;
}			t_cmdblock;

//minishell's main struct
typedef struct s_ms_
{
	t_envlst	*myenv;
	char		*cwd;
	t_cmdblock 	*cmdblocks;
	int			stdinout_copy[2];
	int			exit_status;
}			t_ms;

/************************ ft_init *********************************************/

t_ms		*ft_init(char **env);
void		ms_cleanup(t_ms *ms);

/****************list_utils**** list for parsing ******************************/

t_list		*ft_lstnew(char *content);
void		ft_append_node(t_list **lst, t_list *new_node);
t_list		*ft_lstlast(t_list *lst);
void		ft_clear_lst(t_list **head);

/******************* cmd_lst ****list utils for command block******************/

t_cmdblock	*ft_new_cmdblock(char **cmd, t_redirlst *redir);
void		ft_append_cmdblock(t_cmdblock **lst, t_cmdblock *new_node);
void		ft_clear_cmdblock(t_cmdblock **head);

/******************************* redir_lst ************************************/

t_redirlst	*ft_redir_lstnew(char *content, int type);
void		ft_redir_append_node(t_redirlst **lst, t_redirlst *new_node);
void		ft_redir_clear_lst(t_redirlst **head);

/***********************************lexer**************************************/

/*tokenize(4ft)*/
void		tokenize(t_ms *mini, char *str, t_list **input);
char		*ft_operator(char **str);
/*singlequote(4ft)*/
char		*singlequote(char **str);
char		*doublequote(t_ms mini, char **str);
char		*ft_dollar_expansion(t_ms mini, char **str);
/*ft_get_token*/
char		*ft_get_plain_word(char **str, char *word);
char		*ft_get_token(t_ms mini, char **str, int hd);
char		*ft_get_expansion(t_ms mini, char **str, char *word);

/*(3ft)******************************parsing***********************************/

int			ft_check_pipes(t_list *line);
int			ft_parse(t_list *line);

/*(5ft)parse_utils*/
void		ft_assign_operator(t_list *line);
void		ft_assign_delimiter(t_list *line);
void		ft_assign_file(t_list *line);
void		ft_assign_cmd(t_list *line);

/******************************* final parse **********************************/

char		**ft_cmd_matrix(t_list *line);//queste 2 possono essere static
t_redirlst	*redir_lst(t_list *line);//queste 2 possono essere static
t_cmdblock	*ft_create_cmdblock(t_list *line);
void		free_matrix(char **matrix, int i);

/*(5ft)*******************************utils************************************/

int			ft_ismetachar(int c);
int			is_str_operator(char *str);
int			ft_isvalid_name(char *str);

/*(2ft)*********************** check_input ************************************/

int			ft_isvalid_input(const char *input);
int			ft_isempty_str(const char *str);

/**(5ft)*************************environment***********************************/

t_envlst	*env_new_node(char *var);
void		env_append_node(t_envlst **lst, t_envlst *new);
void		env_rm_node(t_envlst **head, char *str);
t_envlst	*env_get_node(t_envlst **head, char *key);
char		*ft_getenv_var(t_ms *mini, char *env);

/*(4ft)******************** environment_utils *********************************/

void		env_clear_node(t_envlst *node);
void		env_clear_lst(t_envlst **head);
t_envlst	*ft_env_cpy(t_envlst *myenv, char **matrix);
int			ft_lstsize(t_envlst *lst);

/******************************** builtins*************************************/

int			execute_builtin(char **cmd, t_ms *mini);
int			is_built_in(char *cmd);
void		print_builtin_error(char *builtin, char *arg, t_ms *mini);

/************************* builtins files *************************************/

int			ft_pwd(t_ms *mini);
int			ft_env(char **cmd, t_ms *mini);
void		env_export_print(t_envlst *env);
int			ft_export(char **cmd, t_ms *mini);
int			ft_unset(char **cmd, t_ms *mini);
int			builtin_echo(char **cmd);
int			ft_cd(char **cmd, t_ms *mini);
int 		ft_exit(char **cmd, t_ms *ms);

/************************** exec_utils ****************************************/

int			cmd_not_found(char *cmd, char **env, t_ms *mini, char *cmd_path);
int			only_one_cmd(t_cmdblock *cmdblocks);
char		**envlst_to_matrix(t_envlst *env);

/**************************** esec_utils2 *************************************/

void		create_single_pipe(t_cmdblock *cmd, int pipe_fd[2]);
void		close_fd(int fd);
void		close_2_fds(int fd1, int fd2);

/************************** execute_cmdblocks *********************************/

void		child_process(t_cmdblock *cmd, int prev_fd, int next_fd[2], t_ms *ms);
void		create_pipes(t_cmdblock *cmdblock, t_ms *ms);
int			execute_cmdblocks(t_cmdblock *cmdblocks, t_ms *ms);
int			wait_for_childs(void);

/*5f********************* handle_redirection **********************************/

int			handle_redirection(t_redirlst *redir, t_ms *mini);
int			redirection_out(t_redirlst *redir, t_ms *mini);

/*4f***************************** heredoc *************************************/

int			handle_heredocs(t_cmdblock *cmdblocks, t_ms *mini);

/************************** heredoc_utils *************************************/

char		*ft_append_text_before_dollar(char **start);
void		ft_append_expansion(t_ms *mini, char **start, char **expanded);
char		*ft_expand_heredoc(t_ms *mini, char **line);
int			ft_wait_heredoc(pid_t pid);
int			ft_check_delimiter_quote(char **delimiter);

/*2f******************************* executor **********************************/

int			execute_single_command(char **cmd, t_ms *mini);

/**************************** ft_print_error **********************************/

void		ft_print_error(char *str, t_ms *mini, int err);
void		ft_print_error2(char *str, t_ms *mini, int err);

/* ******************************SIGNALS************************************* */

void		signal_handler(int signo);
void		setup_signals(void);
void		setup_child_signals(void);
void		setup_heredoc_signals(void);
void		ft_hd_ctrlc(volatile sig_atomic_t g_signo, int ex_SI, int w_fd);

#endif
