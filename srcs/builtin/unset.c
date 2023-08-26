/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:51:23 by motroian          #+#    #+#             */
/*   Updated: 2023/08/26 18:47:34 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_unset(char **var, char ***env)
// {
// 	char	**new;
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		z;

// 	z = -1;
// 	new = ft_calloc((count_string(*env) + 1), sizeof(char *));
// 	if (!new)
// 		return (-1);
// 	while (var[++z])
// 	{
// 		// printf("Value: %s\n", (*env)[++i]);make
// 		i = -1;
// 		while ((*env)[++i])
// 		{
// 			k = -1;
// 			if (!strncmp((*env)[i], var[z], ft_strlen(var[z])))
// 				i++;
// 			if ((*env)[i])
// 			{
// 				j = 0;
// 				new[j] = ft_calloc((ft_strlen((*env)[i]) + 1), sizeof(char));
// 				if (!new[j])
// 					return (free_all(new), -1);
// 				while ((*env)[i][++k])
// 					new[j][k] = (*env)[i][k];
// 			}
// 			// printf("[%s]\n", (*env)[i]);
// 			j++;
// 		}
// 	}
// 	free_all(*env);
// 	*env = new;
// 	return (0);
// }

int	ft_isinenv(char *cle, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cle);
	while (env && env[i])
	{
		if (!ft_strncmp(cle, env[i], len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_mallocunset(char **var, char ***env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (var[i])
	{
		if (ft_isinenv(var[i], *env))
		{
			i++;
			len++;
		}
		else
			i++;
	}
	return (len);
}

int	lenofenv(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

char	**regenerate_ev(int len, int index, char **ev)
{
	int		i;
	int		trgr;
	char	**my_ev;

	if (!ev)
		return (NULL);
	my_ev = ft_calloc(sizeof(*my_ev), (len + 1));
	trgr = 0;
	i = -1;
	while (++i < len)
	{
		trgr += (i == index);
		if (ev[i + trgr])
		{
			my_ev[i] = ft_strdup(ev[i + trgr]);
		}
		else
			my_ev[i] = ft_strdup("");
	}
	return (ft_free_tab(ev), my_ev);
}

int	ft_unset(char **var, char ***env)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (var[i])
	{
		n = ft_isinenv(var[i], *env);
		if (n >= 0 && *env)
			*env = regenerate_ev(lenofenv(*env) - 1, n, *env);
		i++;
	}
	return (0);
}
