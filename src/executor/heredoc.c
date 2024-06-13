/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:38:35 by deordone          #+#    #+#             */
/*   Updated: 2024/06/13 15:32:42 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipes(int p[2], int fd, char *doc)
{
	close(fd);
	close(p[1]);
	if (doc)
		free(doc);
}

static void	write_in_pipe(t_shell *sh, char **doc, int p[2])
{
	char	*expanded_doc;

	expanded_doc = expand_string(sh, *doc);
	ft_putstr_fd(expanded_doc, p[1]);
	ft_putstr_fd("\n", p[1]);
	free(expanded_doc);
	free(*doc);
}

static void	init_doc_fd(int *fd, int last_in, int p[2])
{
	if (pipe(p) < 0)
		exit(1);
	if (last_in != 0)
		close(last_in);
	*fd = dup(0);
}

int	heredoc_case(t_shell *sh, t_redir *redir, int last_in, int len)
{
	int		fd;
	char	*doc;
	int		p[2];

	init_doc_fd(&fd, last_in, p);
	ft_signals(HEREDOC);
	while (42)
	{
		doc = readline("> ");
		if (doc == NULL || g_signals != 0)
		{
			dup2(fd, 0);
			close_pipes(p, fd, doc);
			return (close(*p), -2);
		}
		last_in = p[0];
		if (ft_strlen(doc) > ft_strlen(redir->file))
			len = ft_strlen(doc);
		else
			len = ft_strlen(redir->file);
		if (!doc || !redir->file || ft_strncmp(doc, redir->file, len) == 0)
			break ;
		write_in_pipe(sh, &doc, p);
	}
	return (close_pipes(p, fd, doc), last_in);
}

// int	heredoc_case(t_shell *sh, t_redir *redir, int last_in)
// {
// 	char	*doc;

// 	int		len;
// 	int		p[2];
// 	int		fd;

// 	(void)sh;
// 	if (last_in != 0)
// 		close(last_in);
// 	fd = dup(0);
// 	ft_signals(HEREDOC);
// 	if (pipe(p) < 0)
// 		exit(1);
// 	while (42)
// 	{
// 		doc = readline("> ");
// 		if (doc == NULL || g_signals != 0)
// 		{
// 			dup2(fd, 0);
// 			return (-2);
// 		}
// 		last_in = p[0];
// 		if (ft_strlen(doc) > ft_strlen(redir->file))
// 			len = ft_strlen(doc);
// 		else
// 			len = ft_strlen(redir->file);
// 		if (!doc || !redir->file || ft_strncmp(doc, redir->file, len) == 0)
// 			break ;
// 		doc = expand_string(sh, doc);
// 		ft_putstr_fd(doc, p[1]);
// 		ft_putstr_fd("\n", p[1]);
// 		free(doc);
// 	}
// 	close(p[1]);
// 	close(fd);
// 	ft_putstr_fd("\n\0", p[1]);
// 	free(doc);
// 	return (last_in);
// }