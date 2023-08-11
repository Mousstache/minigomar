/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:51:23 by motroian          #+#    #+#             */
/*   Updated: 2023/08/11 21:45:08 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



int	ft_unset(char **var, char ***env)
{
	char	**new;
	int		i;
	int		j;
	int		k;
	int		z;

	i = -1;
	j = 0;
	z = -1;
	new = ft_calloc((count_string(*env) + 1), sizeof(char *));
	if (!new)
		return (-1);
	while (var[++z])
	{
		// printf("Value: %s\n", (*env)[++i]);make
		while ((*env)[++i])
		{
			k = -1;
			if (!strncmp((*env)[i], var[z], ft_strlen(var[z])))
				i++;
			if ((*env)[i])
			{
				new[j] = ft_calloc((ft_strlen((*env)[i]) + 1), sizeof(char));
				if (!new[j])
					return (free_all(new), -1);
				while ((*env)[i][++k])
					new[j][k] = (*env)[i][k];
			}
			j++;
		}
	}
	free_all(*env);
	*env = new;
	return (0);
}
