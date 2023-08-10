/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 02:56:31 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/08 20:11:53 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_cd(char **arg, char ***env)
{
	(void)env;
	printf("arg 1 {%s} arg 2 [%s]\n", arg[1], arg[2]);
	if (arg[1] && arg[2])
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	else if (arg[1] && chdir(arg[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

	// int	main(int ac, char **av, char **env)
	// {
	// 	printf("AVANT ");
	// 	ft_pwd(av, env);
	// 	printf("\n");
	// 	ft_cd(av, env);
	// 	printf("\n");
	// 	printf("APRES ");
	// 	ft_pwd(av, env);
	// 	printf("\n");
	// }
