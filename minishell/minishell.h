/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:32:53 by cacorrea          #+#    #+#             */
/*   Updated: 2025/01/30 12:32:55 by cacorrea         ###   ########.fr       */
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
# define RD_HEREDOC	5	// << limiter
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
typedef	struct s_executor
{
	char				**cmd;//un array di str: 0 = cmd, 1 = arg 1, 2 = arg 2...
	int					fd[2];//in and out
	struct s_executor	*next;
}			t_executor;
//forse la lista per il parsing deve diventare questo una volta che elimino
//o includo qui negli fd le pipes e le redirections

//qui devo fare un elenco delle cose? enum REDIRECT 1 PIPE 2...???
/*definire una struct ms che ha le cose principali che non so quali sono
sicuramente una copia delle env variables (envcpy.c)che copio appena inizia
il programma, questa ms struct me la porto dietro tutto il tempo*/
typedef struct s_ms
{
	t_envlst	*myenv;
	char		*cwd;
	int			exit_status;
}			t_ms;

/****************list_utils**** list for parsing ******************************/

t_list	*ft_lstnew(char *content);
void	ft_append_node(t_list **lst, t_list *new_node);
void	ft_clear_lst(t_list **head);
void 	print_list(t_list *lista);/***************da levare***********/
void 	print_input(t_list *lista);/**************da levare********* */
int		paired_quotes(const char *str);


/***********************************lexer**************************************/

void	tokenize(t_ms *mini, char *str, t_list **input);
char	*handle_token(t_ms mini, char **str);
char	*singlequote(char **str);
char	*doublequote(t_ms mini, char **str);
char	*ft_operator(char **str);
char	*ft_get_plain_word(char **str, char *word);
char	*ft_get_token(t_ms mini, char **str);
char	*ft_get_expansion(t_ms mini,char **str, char *word);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_dollar_expansion(t_ms mini, char **str);


/*******************************parsing****************************************/

void	ft_parse(t_list *line);
void	ft_assign_operator(t_list *line);
//void	ft_assign_file(t_list *line);
void	ft_assign_delimiter(t_list *line);

void	debug_printer(t_list *line);

/*************************************utils************************************/

int	ft_isempty_str(const char *str);
int	ft_ismetachar(int c);
int	ft_isvalid_name(char *str);


/*******************************input_check************************************/

int	ft_isvalid_input(const char *input);


/**********************************environment*********************************/

t_envlst	*ft_env_cpy(t_envlst *myenv, char **matrix);
t_envlst	*env_new_node(char *var);
void	env_append_node(t_envlst **lst, t_envlst *new);
void	env_clear_node(t_envlst *node);
void	env_rm_node(t_envlst **head, char *str);
void	env_clear_lst(t_envlst **head);

char	*ft_getenv_var(t_ms *mini, char *env);


/******************************** builtins*************************************/

void	ft_pwd(t_ms *mini);
void	ft_env(t_ms	*mini);
void	ft_export(t_ms	*mini);
void	ft_unset(t_ms	*mini, char *key);

/********************************** others ************************************/

#endif

