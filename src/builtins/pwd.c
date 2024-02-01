/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmoretti <brmoretti@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:51:33 by brmoretti         #+#    #+#             */
/*   Updated: 2024/01/29 23:39:04 by brmoretti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(const char **args)
{
	char	*buffer;
	char	*wd;
	size_t	chars;

	chars = 1024;
	buffer = ft_calloc(chars, sizeof(char));
	while (buffer && args[0])
	{
		wd = getcwd(buffer, chars);
		if (wd)
		{
			ft_putendl_fd(wd, 1);
			free(buffer);
			return (EXIT_SUCCESS);
		}
		else
		{
			free(buffer);
			chars *= 2;
			if (chars > 102400)
				break ;
			buffer = ft_calloc(chars, sizeof(char));
		}
	}
	return (errno);
}