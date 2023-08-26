/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:54:44 by motroian          #+#    #+#             */
/*   Updated: 2023/08/26 21:47:53 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_strcat(char *dst, const char *src, int *n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	*n += j;
}

int	alphanum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
			&& c <= 'Z') || c == '_')
		return (0);
	return (1);
}

int	lenof(int val)
{
	int i = 0;
	while (val > 0)
	{
		val /= 10;
		i++;
	}
	return (i);
}

void	fakeitoa(char str[5], int n)
{
	int				len;
	unsigned int	nb;

	nb = n;
	if (n == 0)
	{
		str[0] = '0';
		str[1] = 0;
		return ;
	}
	len = lenof(n);
	// strcpy(str, "avio");
	printf("{{{%i}}[%i]}\n", len, n);
	str[len] = 0;
	while (--len >= 0)
	{
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
}
char	*expand_ok(char *str, t_data *env, int *clef)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (str[0] && ft_isdigit(str[0]))
		return (*clef += 1, NULL);
	if (str[0] && alphanum(str[0]) && str[0] != '?')
		return ("$");
	if (str[0] == '?')
	{
		*clef += 1;
		fakeitoa(env->fakeitoa, env->status);
		return (env->fakeitoa);
	}
	while (str && str[i] && !alphanum(str[i]))
		i++;
	*clef += i;
	while (env->env_copy[y])
	{
		if (!ft_strncmp(str, env->env_copy[y], i) && env->env_copy[y][i] == '=')
		{
			return (&env->env_copy[y][i + 1]);
		}
		y++;
	}
	return (NULL);
}

int	copy_squote(char *str, char *new, int *i, int *n)
{
	if (str[(*i)] == 39)
	{
		new[(*n)++] = str[(*i)++];
		while (str[(*i)] && str[(*i)] != 39)
			new[(*n)++] = str[(*i)++];
		new[(*n)++] = str[(*i)++];
		return (1);
	}
	return (0);
}

char	*ft_expandd(char *str, t_data *env)
{
	int		i;
	char	*new;
	char	*value;
	int		n;

	new = ft_calloc(count_expand(str, env) + 1, 1);
	i = 0;
	n = 0;
	while (str && str[i])
	{
		if (copy_squote(str, new, &i, &n))
			;
		else if (str[i] == '$' && str[i + 1])
		{
			i++;
			value = expand_ok(&str[i], env, &i);
			if (value)
				ft_strcat(&new[n], value, &n);
		}
		else
			new[n++] = str[i++];
	}
	free(str);
	return (new);
}
