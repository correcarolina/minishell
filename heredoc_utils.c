/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:22:54 by rd-agost          #+#    #+#             */
/*   Updated: 2025/06/09 13:10:23 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signo;

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
	if ((WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		return (-1);
	}
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
