/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:32:53 by cacorrea          #+#    #+#             */
/*   Updated: 2025/04/26 18:52:39 by rd-agost         ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
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

//questo e il nodo che deve arrivare al executor:
typedef	struct s_cmdblock
{
	char				**cmd;//un array di str: 0 = cmd, 1 = arg 1, 2 = arg 2...
	t_list				*redir;//ogni nodo contiene il nome del file e il type (filein, fileout, append, heredoc)
	struct s_cmdblock	*next;
}			t_cmdblock;
//forse la lista per il parsing deve diventare questo una volta che elimino
//o includo qui negli fd le pipes e le redirections

//qui devo fare un elenco delle cose? enum REDIRECT 1 PIPE 2...???
/*definire una struct ms che ha le cose principali che non so quali sono
sicuramente una copia delle env variables (envcpy.c)che copio appena inizia
il programma, questa ms struct me la porto dietro tutto il tempo*/
typedef struct s_ms_
{
	t_envlst	*myenv;
	char		*cwd;
	int			stdinout_copy[2];
	int			exit_status;//of the most recently executed foreground pipeline. or put it in a global var
}			t_ms;

/****************list_utils**** list for parsing ******************************/

t_list	*ft_lstnew(char *content);
t_list	*ft_redir_lstnew(char *content, int type);
void	ft_append_node(t_list **lst, t_list *new_node);
void	ft_clear_lst(t_list **head);
t_list	*ft_lstlast(t_list *lst);

/******************* cmd_lst ****list utils for command block******************/

t_cmdblock	*ft_new_cmdblock(char **cmd, t_list *redir);
void		ft_append_cmdblock(t_cmdblock **lst, t_cmdblock *new_node);
void		ft_clear_cmdblock(t_cmdblock **head);

/***********************************lexer**************************************/

/*tokenize(4ft)*/
void	tokenize(t_ms *mini, char *str, t_list **input);
char	*ft_operator(char **str);
/*singlequote(4ft)*/
char	*singlequote(char **str);
char	*doublequote(t_ms mini, char **str);
char	*ft_dollar_expansion(t_ms mini, char **str);
/*ft_get_token*/
char	*ft_get_plain_word(char **str, char *word);
char	*ft_get_token(t_ms mini, char **str);
char	*ft_get_expansion(t_ms mini, char **str, char *word);

/*(3ft)******************************parsing***********************************/

int		ft_check_pipes(t_list *line);
void	ft_parse(t_list *line);
void	debug_printer(t_list *line);

/*(5ft)parse_utils*/
void	ft_assign_operator(t_list *line);
void	ft_assign_delimiter(t_list *line);
void	ft_assign_file(t_list *line);
void	ft_assign_cmd(t_list *line);

/******************************* final parse **********************************/

char	**ft_cmd_matrix(t_list *line);//queste 2 possono essere static
t_list	*redir_lst(t_list *line);//queste 2 possono essere static
t_cmdblock	*ft_create_cmdblock(t_list *line);

/*(5ft)*******************************utils************************************/

int		ft_isempty_str(const char *str);
int		ft_ismetachar(int c);
int		is_str_operator(char *str);
int		ft_isvalid_name(char *str);
char	*ft_strjoin_free(char *s1, char *s2);

/*(2ft)*********************** check_input ************************************/

int	ft_isvalid_input(const char *input);

/**(6ft da levarne una)**********environment***********************************/

t_envlst	*ft_env_cpy(t_envlst *myenv, char **matrix);
t_envlst	*env_new_node(char *var);
void		env_append_node(t_envlst **lst, t_envlst *new);
void		env_clear_node(t_envlst *node);
void		env_rm_node(t_envlst **head, char *str);
void		env_clear_lst(t_envlst **head);
/*ft_pwc*/
char		*ft_getenv_var(t_ms *mini, char *env);

/******************************** builtins*************************************/

void	ft_pwd(t_ms *mini);
void	ft_env(t_ms	*mini);
void	ft_export(t_ms	*mini);
void	ft_unset(t_ms	*mini, char *key);
void	builtin_echo(t_cmdblock *data);

/************************** exec_utils ****************************************/

int	only_one_cmd(t_cmdblock *cmdblocks);
int	is_built_in(char *cmd);
void	close_fds(int fd1, int fd2);

/************************** execute_cmdblocks *********************************/

void	child_process(t_cmdblock *cmd, int prev_fd, int next_fd, t_ms *ms);
void	create_pipes(t_cmdblock *cmdblock, t_ms *ms);
int 	execute_cmdblocks(t_cmdblock *cmdblocks, t_ms *ms);

/*5f********************* handle_redirection **********************************/

int		handle_redirection(t_list *redir);
int		redirection_out(t_list *redir);
int		handle_heredoc(char *delimiter);//da mettere in un file a parte

/*2f******************************* executor **********************************/

void	execute_command(t_cmdblock *data, t_envlst **env, t_ms *mini);

/********************************** others ************************************/

/*nel main per ora*/
void	ms_cleanup(t_ms *ms);

#endif
