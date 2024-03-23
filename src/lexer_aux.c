/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:01:28 by deordone          #+#    #+#             */
/*   Updated: 2024/03/23 15:17:52 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:42:37 by deordone          #+#    #+#             */
/*   Updated: 2024/03/23 15:01:16 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_type(t_token *lst)
{
	if (ft_strncmp(lst->data, "<<", 3) == 0)
		lst->type = DLESS;
	else if (ft_strncmp(lst->data, ">>", 2) == 0)
		lst->type = DGREAT;
	else if (ft_strncmp(lst->data, "<", 1) == 0 || ft_strncmp(lst->data, "<<<",
			3) == 0)
		lst->type = LESS;
	else if (ft_strncmp(lst->data, ">", 1) == 0)
		lst->type = GREAT;
	else if (ft_strncmp(lst->data, "|", 1) == 0)
		lst->type = PIPE;
	else if (ft_strncmp(lst->data, "\'", 1) == 0)
		lst->type = SQUOTE;
	else if (ft_strncmp(lst->data, "\"", 1) == 0)
		lst->type = DQUOTE;
	else if (ft_strncmp(lst->data, "$", 1) == 0)
		lst->type = EXP;
	else
		lst->type = CMD;
}

char	**montage_tokens(char *line)
{
	char	**tokens;
	char 	*words;
	int		len;
	int 	i;

	len = len_matriz(line);
	tokens = malloc(sizeof(char *) * len + 1);
	tokens[len] = NULL;
	while (token[i] != NULL)
	{
		//len of words
		words = malloc(sizeof(char) * len_word + 1);
		//cpy words
		token[i] = words;
		i++;
	}
	dprintf(2, "len ->%d\n", len);
	return (tokens);
}

//#########################################

int	cont_meta(char *s)
{
	int		i;
	int		j;
	int		count;
	char	*meta;

	i = -1;
	count = 0;
	meta = STR_META;
	while (s[++i])
	{
		j = -1;
		while (meta[++j])
		{
			if (s[i] == meta[j] && s[i] != '\'' && s[i] != '\"')
				count++;
		}
	}
	if (count != 0)
		return (++count);
	return (count);
}

static char	*cpy_space(char *final_s, char *s, char btween)
{
	int	i;
	int	j;
	int	h;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (is_charmeta(s[i]) > 0 && s[i] != '\'' && s[i] != '\"')
		{
			h = 0;
			while (++h)
			{
				final_s[j++] = btween;
				if (h >= 2)
					break ;
				final_s[j++] = s[i];
				if (s[i + 1] && s[i] == s[i + 1] && is_charmeta(s[i + 1]) > 0
					&& s[i] != '$' && s[i] != '\'' && s[i] != '\"')
					final_s[j++] = s[++i];
				if (s[i + 1] && s[i] == s[i + 1] && s[i] == '<')
					final_s[j++] = s[++i];
				else if (s[i] == '$')
				{
					while (s[i + 1] != '\0' && s[i + 1] != ' ' && s[i
						+ 1] != '\'' && s[i + 1] != '\"')
					{
						final_s[j++] = s[++i];
					}
				}
			}
		}
		else
			final_s[j++] = s[i];
		i++;
	}
	return (final_s);
}

char	*add_between(char *s, char btween)
{
	int		len_str;
	char	*final_str;

	if (!s)
		return (NULL);
	len_str = ft_strlen(s);
	len_str += cont_meta(s) * 2;
	final_str = ft_calloc(sizeof(char), len_str + 1);
	if (!final_str)
		return (NULL);
	final_str = cpy_space(final_str, s, btween);
	final_str[len_str] = '\0';
	free(s);
	return (final_str);
}
