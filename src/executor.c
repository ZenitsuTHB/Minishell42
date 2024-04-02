/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:40:25 by deordone          #+#    #+#             */
/*   Updated: 2024/04/02 17:27:37 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	executor(t_shell *sh, char **env)
{
	(void)env;
	t_redir *redir;
	t_words *word;
	int *fds;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		exit(-1);
	redir = sh->redir;
	word = sh->words;
//	while (redir || word)
//	{
		if (redir)
		{
			fds = process_redir(redir, fds);
			redir = redir->next;
		}
		else
		{
			fds[0] = STD_IN;
			fds[1] = STD_OUT;	
		}
		//ahora mismo o se ha acabado la ejecucion o hay una pipe
		if (word)
		{
			process_word(word, fds, env);
			word = word->next;
		}
		free(fds);
}
