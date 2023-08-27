/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:51:52 by motroian          #+#    #+#             */
/*   Updated: 2023/08/27 20:50:55 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add2(t_data *env, char **tab, int *k)
{
	if ((*k) > -1)
		tab = malloc(sizeof(char *) * (count_string(env->env_copy) + 1));
	else
		tab = malloc(sizeof(char *) * (count_string(env->env_copy) + 2));
	return (tab);
}

char	**add_variable(t_data *env)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = -1;
	j = 0;
	tab = NULL;
	k = check_var_exist(env->env_copy, env->var_name);
	if (!env->var_name)
		return (env->env_copy);
	tab = add2(env, tab, &k);
	while (env->env_copy[++i])
	{
		if (k == i)
			tab[j++] = ft_strjoin(env->var_name, env->var_value);
		else
			tab[j++] = ft_strdup(env->env_copy[i]);
	}
	if (k == -1)
		tab[j++] = ft_strjoin(env->var_name, env->var_value);
	tab[j] = NULL;
	free_all(env->env_copy);
	env->env_copy = tab;
	return (env->env_copy);
}

int	export_error(char *str, char *msg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_putchar_fd('"', 2);
	while (str && str[i])
		ft_putchar_fd(str[i++], 2);
	ft_putchar_fd('"', 2);
	ft_putchar_fd(' ', 2);
	while (msg[j])
		ft_putchar_fd(msg[j++], 2);
	ft_putchar_fd('\n', 2);
	return (i);
}

int	norme_export(char **str, t_data *envv, char ***env, int res)
{
	int		i;
	int		j;
	int		k;

	k = -1;
	while (str[++k])
	{
		j = 0;
		i = 0;
		envv->var_name = get_name_var(str[k]);
		if (!char_var_correct(envv->var_name))
		{
			export_error(str[k], "not a valid identifier");
			res = 1;
		}
		else
		{
			i = count_between_quotes(str[k], '=');
			envv->var_value = ft_strchr(str[k], '=');
			*env = add_variable(envv);
		}
		free(envv->var_name);
	}
	return (res);
}

int	ft_export(char **str, char ***env)
{
	int		res;
	t_data	envv;

	if (!str[0])
		return (0);
	res = 0;
	ft_memset(&envv, 0, sizeof(t_data));
	envv.env_copy = create_env(*env, 1);
	res = norme_export(str, &envv, env, res);
	return (res);
}
