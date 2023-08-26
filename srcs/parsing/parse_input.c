/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 22:44:42 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/26 18:53:44 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_sep(t_var *tot, char *input)
{
	if ((input[tot->i] != '|' && input[tot->i + 1] && input[tot->i] == '>'
			&& input[tot->i + 1] == '>') || (input[tot->i] != '|'
			&& input[tot->i + 1] && input[tot->i] == '<' && input[tot->i
					+ 1] == '<'))
		tot->d = 2;
	if (tot->i > 0)
		tot->j++;
	tot->n = 1;
}

int	len_total(char *input, int len)
{
	t_var	tot;

	ft_memset(&tot, 0, sizeof(tot));
	tot.d = 1;
	while (input[tot.i])
	{
		if (input[tot.i] == '|' || input[tot.i] == '<' || input[tot.i] == '>')
			count_sep(&tot, input);
		while (tot.d > 0)
		{
			tot.d--;
			tot.j++;
			tot.i++;
		}
		if (tot.n == 1 && tot.i != len)
			tot.j++;
		tot.n = 0;
		tot.d = 1;
	}
	return (tot.j);
}

void	*find_sep(t_var *var, char *input, char *new)
{
	if ((input[var->i] != '|' && input[var->i + 1] && input[var->i] == '>'
			&& input[var->i + 1] == '>') || (input[var->i] != '|'
			&& input[var->i + 1] && input[var->i] == '<' && input[var->i
					+ 1] == '<'))
		var->d = 2;
	if (var->i > 0)
		new[var->j++] = ' ';
	var->n = 1;
	return (new);
}

void	*parse_input(char *input)
{
	t_var	var;
	char	*new;

	ft_memset(&var, 0, sizeof(var));
	var.d = 1;
	var.len = ft_strlen(input);
	var.lentotal = len_total(input, var.len);
	new = ft_calloc(sizeof(char), (var.lentotal + 1));
	if (!new)
		return (NULL);
	while (input[var.i])
	{
		if (input[var.i] == '|' || input[var.i] == '<' || input[var.i] == '>')
			new = find_sep(&var, input, new);
		while (var.d-- > 0)
			new[var.j++] = input[var.i++];
		if (var.n == 1 && var.i != var.len)
			new[var.j++] = ' ';
		var.n = 0;
		var.d = 1;
	}
	free(input);
	return (new);
}
