#include "minishell.h"

int	count_quotes(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			count++;
		i++;
	}
	return (count);
}

char	*var_value_noquotes(char *var)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char) * (ft_strlen(var) + count_quotes(var) + 1));
	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '\'' || var[i] == '"')
			ret[j++] = '\\';
		if (var[i] == ' ' && j && ret[j - 1] != ' ')
			ret[j++] = var[i];
		else if (var[i] != ' ')
			ret[j++] = var[i];
		i++;
	}
	if (ret[j - 1] == ' ')
		ret[j - 1] = 0;
	ret[j] = 0;
	printf("var value = %s\n", ret);
	return (ret);
}

char	*get_env_var(t_shell *shell, char *name, int quotes)
{
	t_envlst	*lst;
	char		*ret;

	lst = shell->env_var;
	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(shell->last_exit_return));
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			if (quotes)
				return (ft_strdup(lst->value, shell->to_free));
			else
				return (var_value_noquotes(lst->value));
		}
		lst = lst->next;
	}
	ret = ft_malloc(1, &shell->to_free);
	*ret = 0;
	return (ret);
}

int	has_env_var(char *input, t_shell *shell)
{
	t_parser	*parser;
	int			i;

	parser = init_parser(shell);
	i = 0;
	while (input[i])
	{
		if (input[i] == '"' && !parser->s_quote)
			parser->d_quote = !parser->d_quote;
		else if (input[i] == '\'' && !parser->d_quote)
			parser->s_quote = !parser->s_quote;
		else if (input[i] == '$' && !parser->s_quote)
		{
			free(parser);
			return (i);
		}
		i++;
	}
	free(parser);
	return (-1);
}
