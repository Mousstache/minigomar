/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:51:52 by motroian          #+#    #+#             */
/*   Updated: 2023/08/08 22:19:54 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**add_variable(t_data *env)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = -1;
	j = 0;
	k = check_var_exist(env->env_copy, env->var_name);
	printf("heeeere->%s|%i\n", env->var_name, k);
	if (!env->var_name)
		return (env->env_copy);
	if (k > -1)
		tab = malloc(sizeof(char *) * (count_string(env->env_copy) + 1));
	else
		tab = malloc(sizeof(char *) * (count_string(env->env_copy) + 2));
	while (env->env_copy[++i])
	{
		if (k == i)
		{
			tab[j++] = ft_strjoin(env->var_name, env->var_value);
		}
		else
		{
			tab[j++] = ft_strdup(env->env_copy[i]);
			// printf("-------------------------------------->%s\n", tab[j++]);

		}
	}
	if (k == -1)
		tab[j++] = ft_strjoin(env->var_name, env->var_value);
	tab[j] = NULL;

	free_all(env->env_copy);
	env->env_copy = tab;
	printf("DERNIERE LIGNE = %s\n", tab[j - 1]);
	return (env->env_copy);
}

char	*get_name_var(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (str[i] != '=' && str[i])
	{
		if (count_between_quotes(str + i, '=') > count_between_quotes(str + i,
																		' '))
			i += count_between_quotes(str + i, ' ') + 1;
		else
			break ;
	}
	new = malloc(sizeof(char) * (count_between_quotes(str + i, '=') + 1));
	if (!new)
		return (NULL);
	while (str[i] != 0 && str[i] != '=')
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = 0;
	return (new);
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

int    ft_export(char **str, char ***env)
{
    int    i;
    int    j;
    int k;
    int res;
	t_data	envv;

    i = 0;
    j = 0;
    k = -1;
    res = 0;
	memset(&envv, 0, sizeof(t_data));
	envv.env_copy = create_env(*env);
    while (str[++k])
    {
        envv.var_name = get_name_var(str[k]);
        if (!char_var_correct(envv.var_name))
        {
            export_error(*str, "not a valid identifier");
            free(envv.var_name);
            res = 1;
        }
        else
        {
            i += count_between_quotes(str[k], '=');
			// printf("%s\n", *str);
            envv.var_value = malloc(sizeof(char) * (ft_strlen(*str + i) + 1));
            while (str[k][i])
                envv.var_value[j++] = str[k][i++];
            envv.var_value[j] = 0;
			// free_all(*env);
			// printf("\n\n\n\nNew env adress: %p\n\n\n\n", *env);
			*env = add_variable(&envv);
			// printf("\n\n\n\nNew env adress: %p\n\n\n\n", *env);
		}
    }
    return (res);
}