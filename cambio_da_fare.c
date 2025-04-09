//cambio da fare in tokenize

static char	*handle_token(t_ms mini, char **str)
{
	char	*word;

	word = NULL;
	if (ft_ismetachar(**str))
		word = ft_operator(str);
	else
		word = ft_get_token(mini, str);
	return (word);
}

//splits the input, and put the tokens into a linked list
void	tokenize(t_ms *mini, char *str, t_list **input)
{
	char	*word;

	if (str == NULL || ft_isempty_str(str))
		return ;
	while (*str)
	{
		while (*str && isspace(*str))
			str++;
		if (*str == '\0')
			break ;
		if (ft_ismetachar(*str))
		{
			word = ft_operator(str);
			ft_append_node(input, ft_lstnew(word));
		}
		else
		{
			word = ft_get_token(*mini, str);
		//word = handle_token(*mini, &str);
			if (word != NULL && *word != '\0')
			{
				if ((ft_strncmp(word, "|", 2) == 0) || (ft_strncmp(word, ">>", 3) == 0) || (ft_strncmp(word, "<<", 3) == 0) || \
				(ft_strncmp(word, ">", 2) == 0) || (ft_strncmp(word, "<", 2) == 0))
				{
					ft_append_node(input, ft_lstnew(word));
					//set type to arg
				}
				else
					ft_append_node(input, ft_lstnew(word));
			}
		}
//non posso liberare word perche deve rimanere dentro il nodo
	}
}