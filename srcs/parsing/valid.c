/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:41:40 by motroian          #+#    #+#             */
/*   Updated: 2023/08/28 22:10:58 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_norm2(int *i, char *str)
{
	if (((str[*i] == '<') && (str[*i + 1] == '<')) || ((str[*i] == '>')
			&& (str[*i + 1] == '>')))
	{
		(*i) += 2;
		if (str[*i] == '\0')
			return (1);
		while (str[*i] && (str[*i] == ' ' || str[*i] == '	'))
			(*i)++;
		if (ft_strchr("><|", str[*i]))
			return (1);
	}
	return (0);
}

int	syntax(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i + 1] == '\0')
			if (ft_strchr("><|", str[i]) || ((str[i] == '<') && (str[i
							+ 1] == '<')) || ((str[i] == '>') && (str[i
							+ 1] == '>')))
				return (1);
		if (ft_norm2(&i, str))
			return (1);
		if ((str[i] == '>') || (str[i] == '<'))
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '	'))
				i++;
			if ((str[i] == '<') && (str[i + 1] == '<'))
				return (0);
			else if (ft_strchr("><|", str[i]))
				return (1);
		}
	}
	return (0);
}

int	quotes(char *str)
{
	int		i;
	int		quote;
	char	c;

	i = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] && str[i] != 39 && str[i] != 34)
			i++;
		if (str[i] && (str[i] == 39 || str[i] == 34))
		{
			c = str[i];
			if (str[i++] == c)
				quote++;
			while (str[i] && (str[i] != c))
				i++;
			if (str[i++] == c)
				quote++;
			else
				break ;
		}
	}
	return (quote % 2);
}

int	ft_norme(char *str, int *i, int c, int *quote)
{
	c = str[*i];
	if (str[(*i)++] == c)
		(*quote)++;
	return (c);
}

char	*negatif(char *str)
{
	int		i;
	int		quote;
	char	c;

	i = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] && str[i] != 39 && str[i] != 34)
			i++;
		if (str[i] && (str[i] == 39 || str[i] == 34))
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
			{
				str[i] *= -1;
				i++;
			}
			if (str[i] == c)
				i++;
			// c = str[i];
			// if (str[i++] == c)
			// 	quote++;
			// while (str[i] && (str[i] != c))
			// 	str[i++] *= -1;
			// while (str[i] && (str[i] != c))
			// {
			// 	if (str[i++] == c)
			// 		quote++;
			// 	else
			// 		break ;
			// }
		}
	}
	return (str);
}
