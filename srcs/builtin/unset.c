/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:51:23 by motroian          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:49 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int		ft_unset(char **var, char ***env)
{
	char	**new;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	int z = -1;
	new = ft_calloc((count_string(*env) + 1), sizeof(char *));
	// printf("%d\n", count_string(*env));
	if (!new)
		return (-1);
	while (var[++z])
	{
		printf("Value: %s\n" ,(*env)[++i]);
		while ((*env)[++i])
		{
			k = -1;
			if (!strncmp((*env)[i], var[z], ft_strlen(var[z])))
				i++;
			// printf("Env[%d]: %s, var : %s \n",i,  (*env)[i], var[z]);
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
	// printf("Count string: %d\n", count_string(new));
	// printf("Print the current env \n");
	// ft_env(&new, NULL);
	free_all(*env);
	*env = new;
	return (0);
}
