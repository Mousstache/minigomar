/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:05:12 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/30 19:39:44 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_syntax(char *input, t_data *data)
{
	if (quotes(input))
		return (ft_printf("quote fail\n"), free(input), 1);
	if (syntax(input))
		return (ft_printf("syntax error\n"), free(input), 1);
	data->var_name = NULL;
	data->var_value = NULL;
	return (0);
}

int	posquote_two(char *input, int nb, int nb1, int i)
{
	i++;
	while (input[i] && input[i] != nb)
	{
		if (input[i] == nb1)
			input[i] *= -1;
		else if (input[i] == -nb1)
			input[i] *= -1;
		i++;
	}
	return (i);
}

char	*posquote(char *input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == 34)
			i = posquote_two(input, 34, 39, i);
		else if (input[i] == 39)
			i = posquote_two(input, 39, 34, i);
		i++;
	}
	return (input);
}
