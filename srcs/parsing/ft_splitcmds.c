#include "minishell.h"

int	quote_open(t_split *split, const char *str, int i)
{
	if (str[i])
	{
		if (!str[i + 1])
			return (FALSE);
		return (split->quote1 || split->quote2);
	}
	else
		return (FALSE);
}

t_split	init_split(void)
{
	t_split		ret;

	ret.quote1 = 0;
	ret.quote2 = 0;
	return (ret);
}

void	update_quote_status(t_split *split, char c)
{
	if (c == '\'')
		split->quote1 = !split->quote1;
	else if (c == '"')
		split->quote2 = !split->quote2;
}

int	get_cmd_start(const char *str, char c, int i)
{
	t_split	split;

	split = init_split();
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			update_quote_status(&split, str[i]);
		if (str[i] == c && !quote_open(&split, str, i))
		{
			i += 1;
			break ;
		}
		if (i == 0)
		{
			i = -1;
			break ;
		}
		i--;
	}
	i += 1;
	return (i);
}

int	count_cmds(const char *str, char c)
{
	int		i;
	int		count;
	t_split	split;

	i = 0;
	count = 0;
	split = init_split();
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			update_quote_status(&split, str[i]);
		if (!quote_open(&split, str, i) && str[i] != c
			&& (str[i + 1] == c || !str[i + 1]))
			count++;
		i++;
	}
	return (count);
}

char	**ft_splitcmds(const char *str, char c)
{
	char	**ret;
	int		i;
	int		wc;
	t_split	split;

	i = -1;
	wc = 0;
	split = init_split();
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char *) * (count_cmds(str, c) + 1));
	if (!ret)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			update_quote_status(&split, str[i]);
		if (!quote_open(&split, str, i) && str[i] != c
			&& (str[i + 1] == c || !str[i + 1]))
		{
			ret[wc] = ft_strrdup(str, get_cmd_start(str, c, i), i);
			if (!ret[wc++])
			{
				free_split(ret);
				return (NULL);
			}
		}
	}
	ret[wc] = 0;
	return (ret);
}
