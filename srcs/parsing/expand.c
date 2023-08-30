/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:54:44 by motroian          #+#    #+#             */
/*   Updated: 2023/08/30 18:30:05 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_ok(char *str, t_data *env, int *clef)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (str[0] && ft_isdigit(str[0]))
		return (*clef += 1, NULL);
	if (str[0] && alphanum(str[0]) && str[0] != '?')
		return (ft_strdup("$"));
	if (str[0] == '?')
		return (*clef += 1, ft_itoa(env->status));
	while (str && str[i] && !alphanum(str[i]))
		i++;
	*clef += i;
	while (env->env_copy[y])
	{
		if (!ft_strncmp(str, env->env_copy[y], i) && env->env_copy[y][i] == '=')
			return (ft_strdup(&env->env_copy[y][i + 1]));
		y++;
	}
	return (NULL);
}

int	is_heredoc(char *str, char *new, int *i, int *n)
{
	int	x;

	x = *i;
	if (str[x] && str[x + 1] && str[x] == '<' && str[x + 1] == '<')
	{
		new[(*n)++] = str[(*i)++];
		new[(*n)++] = str[(*i)++];
		while (str[(*i)] && str[(*i)] == ' ')
			new[(*n)++] = str[(*i)++];
		while (str[(*i)] && str[(*i)] != ' ')
			new[(*n)++] = str[(*i)++];
		return (1);
	}
	return (0);
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

char	*nouvelle_str_un_espace(char *str);

char	*ft_expandd(char *str, t_data *env)
{
	int		i;
	char	*new;
	char	*value;
	int		n;

	new = ft_calloc(count_expand(str, env) + 1, 1);
	if (!new)
		return (NULL);
	i = 0;
	n = 0;
	while (str && str[i])
	{
		if (copy_squote(str, new, &i, &n) || is_heredoc(str, new, &i, &n))
			;
		else if (str[i] == '$' && str[i + 1])
		{
			i++;
			value = expand_ok(&str[i], env, &i);
			// if (i - 3 >= 0 && str[i - 3] != '\"')
			// {
			// 	printf("str %s\n", str);
			// 	printf("\n\n\n\n%c\n",str[i - 3]);
			// 	printf("oueee\n");
			// 	value = nouvelle_str_un_espace(value);
			// }
			if (value)
			{
				ft_strcat(&new[n], mgamiloueee(value), &n);
				printf("la value ==== %s\n", new);
				free(value);
			}
		}
		else
			new[n++] = str[i++];
	}
	free(str);
	return (new);
}


/*
Si j'ai ca if (i - 1 >= 0 && str[i - 1] == '\"') alors je laisse comme c'est 
sinon j'enleve les spaces
fontion qui enleve les spaces
*/

int	taille_avec_un_espaces(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t') && i != 0)
		{
			len++;
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if ((str[i] == ' ' || str[i] == '\t'))
				i++;
		}
		else if ((str[i] == ' ' || str[i] == '\t'))
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if ((str[i] == ' ' || str[i] == '\t'))
				i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*nouvelle_str_un_espace(char *str)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	len = taille_avec_un_espaces(str);
	printf("len %d\n", len);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t') && i != 0)
		{
			res[j] = str[i];
			i++;
			j++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if ((str[i] == ' ' || str[i] == '\t'))
				i++;
		}
		else if ((str[i] == ' ' || str[i] == '\t'))
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if ((str[i] == ' ' || str[i] == '\t'))
				i++;
		}
		else
		{
			res[j] = str[i];
			i++;
			j++;
		}
	}
	return (free(str), res);
}