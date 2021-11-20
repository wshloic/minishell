/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:46:55 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/20 16:15:33 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*redirect_last(t_redirect *redirect)
{
	t_redirect	*tmp;

	tmp = redirect;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	redirect_addback(t_redirect *redirect, int type, t_shell *shell)
{
	t_redirect	*tmp;

	tmp = redirect_last(redirect);
	tmp->next = (t_redirect *)ft_malloc(sizeof(t_redirect), &shell->to_free);
	if (!tmp->next)
		ft_malloc_error(shell->to_free);
	tmp->next->next = NULL;
	return (1);
}

int	is_redirect(char *str, int *i)
{
	if (str[*i] == '>')
	{
		(*i)++;
		if (str[*i] == '>')
		{
			(*i)++;
			return (2);
		}
		return (1);
	}
	else if (str[*i] == '<')
	{
		(*i)++;
		if (str[*i] == '<')
		{
			(*i)++;
			return (4);
		}
		return (3);
	}
	return (0);
}
