/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:22:54 by rd-agost          #+#    #+#             */
/*   Updated: 2025/05/31 21:32:28 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signo;

char	*ft_append_text_before_dollar(char **start)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*start)[i] && (*start)[i] != '$')
		i++;
	tmp = ft_substr(*start, 0, i);
	*start += i;
	return (tmp);
}

char	*ft_expand_heredoc(t_ms *mini, char **line)
{
	char	*start;
	char	*expanded;
	char	*part;

	start = *line;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (*start)
	{
		part = ft_append_text_before_dollar(&start);
		expanded = ft_strjoin_free_both(expanded, part);
		if (*start == '$')
		{
			start++;
			expanded = ft_get_expansion(*mini, &start, expanded);
			if (!expanded)
				return (NULL);
		}
	}
	return (expanded);
}

int	ft_wait_heredoc(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (-130);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (-130);
	return (0);
}

int	ft_check_delimiter_quote(char **delimiter)
{
	if (*delimiter && (*delimiter)[0] == S_QUOTE && (*delimiter)[1] != '\0')
	{
		(*delimiter)++;
		return (1);
	}
	return (0);
}

/* char	*ft_append_text_before_dollar(char **start)
{
	char	*tmp;
	char	*expanded_part;
	int		i;

	i = 0;
	while ((*start)[i] && (*start)[i] != '$')
		i++;
	tmp = ft_substr(*start, 0, i);
	expanded_part = tmp;
	*start += i;
	return (expanded_part);
}

void	ft_append_expansion(t_ms *mini, char **start, char **expanded)
{
	char	*tmp;

	if (**start == '$')
	{
		(*start)++;
		tmp = ft_get_expansion(*mini, start, *expanded);
		free(*expanded);
		*expanded = tmp;
	}
}

char	*ft_expand_heredoc(t_ms *mini, char **line)
{
	char	*start;
	char	*expanded;
	char	*part;

	start = *line;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (*start)
	{
		part = ft_append_text_before_dollar(&start);
		expanded = ft_strjoin_free_both(expanded, part);
		free(part);
		ft_append_expansion(mini, &start, &expanded);
	}
	return (expanded);
} */