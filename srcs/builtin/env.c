/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 03:12:53 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/11 21:40:39 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_env(char **arg, char ***env)
{
	int		i;
	char	**tab;

	(void)arg;
	i = 0;
	tab = *env;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	ft_env(ac, av, env);
// }
