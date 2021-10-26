/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:26:41 by lbertran          #+#    #+#             */
/*   Updated: 2021/10/26 09:13:54 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>
char	*ft_strjoin(const char *s1, const char *s2, t_free *to_free)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*ret;

	i = -1;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = ft_malloc(sizeof(char) * (len + 1), &to_free);
	if (!ret)
		ft_malloc_error(to_free);
	if (s1)
	{
		while (s1[++i])
			ret[i] = s1[i];
	}
	if ((int)i == -1)
		i = 0;
	if (s2)
	{
		while (s2[j])
			ret[i++] = s2[j++];
	}
	ret[i] = '\0';
	return (ret);
}
