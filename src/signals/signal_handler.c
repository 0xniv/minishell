/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:15:21 by bmoretti          #+#    #+#             */
/*   Updated: 2024/02/19 17:00:40 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int signal)
{
	g_last_signal = signal;
	ast_holder(NULL, 1);
	token_list_holder(NULL, 1, 0);
	if (on_heredoc(-1))
		close(STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	if (!is_after_prompt(-1))
		rl_redisplay();
	last_exit_status(130);
}
