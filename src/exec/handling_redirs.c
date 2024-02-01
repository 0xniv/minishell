/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmoretti <brmoretti@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:26:07 by vde-frei          #+#    #+#             */
/*   Updated: 2024/01/31 21:31:51 by brmoretti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	input_redir(t_ast *node_pipe);
static int	append_trunc(t_ast *node_pipe, t_token *token, int flag);

void	handle_redirs(t_ast *node_pipe)
{
	t_token			*token;
	int				file;
	const int		tmp = dup(STDOUT_FILENO);

	token = node_pipe->right->exec->first->content;
	if (node_pipe->type == L_REDIR)
		input_redir(node_pipe);
	else if (node_pipe->type == R_REDIR)
		file = append_trunc(node_pipe, token, TRUN);
	else if (node_pipe->type == APPEND)
		file = append_trunc(node_pipe, token, APEN);
	if (node_pipe->type == R_REDIR || node_pipe->type == APPEND)
	{
		if (file == -1)
			exit(1); //panic
		if (node_pipe->type_prev == 0)
			dup2(file, STDOUT_FILENO);
		close(file);
		execution(node_pipe->left);
		dup2(tmp, STDOUT_FILENO);
	}
	close (tmp);
}

static void	input_redir(t_ast *node_pipe)
{
	t_token	*token;
	int		file = 0;
	const int		tmp = dup(STDIN_FILENO);

	token = node_pipe->right->exec->first->content;
	file = open(token->str, O_RDONLY);
	if (file == -1)
		exit(1); //panic
	dup2(file, STDIN_FILENO);
	execution(node_pipe->left);
	dup2(tmp, STDIN_FILENO);
	close (tmp);
	close(file);
}

static int	append_trunc(t_ast *node_pipe, t_token *token, int flag)
{
	node_pipe->left->type_prev = node_pipe->type;
	return (open(token->str,  flag, 0644));
}