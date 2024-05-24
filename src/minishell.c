/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/05/24 18:48:19 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t volatile g_signals = 0;

void ft_itos(int entero, char *new_level)
{
	if (entero < 10)
	{
		new_level[0] = entero + '0';
		new_level[1] = '\0';
	}
	else if (entero < 100)
	{
		new_level[0] = (entero / 10) + '0';
		new_level[1] = (entero % 10) + '0';
		new_level[2] = '\0';
	}
	else if (entero < 1000)
	{
		new_level[0] = (entero / 100) + '0';
		entero = entero % 100;
		new_level[1] = (entero / 10) + '0';
		new_level[2] = (entero % 10) + '0';
		new_level[3] = '\0';
	}
}

char	*prompt(int exit_status)
{
	char	entero[5];
	char	*str;
	char	*final_str;

	ft_itos(exit_status, entero);
	if (exit_status == 0)
		final_str = ft_strjoin("\001\033[0;32m✔ \033[0m",
				"🏓  PongShell ↴ \002");
	else
	{
		str = ft_strjoin("\001\033[0;31m", entero);
		final_str = ft_strjoin(str, "\033[0m 🏓  PongShell ↴ \002");
		free(str);
	}
	return (final_str);
}

static void	init_sh(t_shell *sh, char **env)
{
	sh->exit_status = 0;
	sh->env = NULL;
	sh->cmds = NULL;
	sh->pro.w = NULL;
	sh->pro.r = NULL;
	sh->env = create_lst_env(env);
}

int	main(int ac, char **av, char **env)
{
	t_shell	sh;
	char	*prompt_str;

	(void)av;
	(void)ac;
	init_sh(&sh, env);
	while (1)
	{
		prompt_str = prompt(sh.exit_status);
		// ft_dprintf(1, "\001%s\002\n", prompt_str);
		ft_signals(&sh, INTERACTIVE);
		disable_control_chars_echo();
		sh.line = readline(prompt_str);
		if (!sh.line)
			execute_exit(&sh); // <- call the exit builtin with no params
		free(prompt_str);
		add_history(sh.line);
		sh.tokens = generate_tokens(sh.line);
		if (parse_all(&sh) != -1 && ft_strlen(sh.line) > 0)
		{
			// print_tokens(sh.tokens);
			//	print_words(sh.pro.w);
			//	print_redir(sh.pro.r);
			// convert lst_env into char **matriz_env
			if (!sh.matriz_env)
				sh.matriz_env = convert_env_dchar(sh.env, env);
			restore_terminal_settings();
			executor(&sh);
		}
		soft_exit(&sh);
	}
	return (0);
}

/*

	- arreglar exit status
	- echo "hi'bye" ✅
	- '<  te mete en un lugar extraño(que es lo correcto) pero al salir con ctr-d da segfault
	- echo ""hola como '"' estas a ---> da segfault;✅
	- exit con muchos parametros no funciona correctamente (too many arguments) ($? = 1)
	- exit con primer parametro con letras (numeric argument required) ($? = 255)
	- unset PATH -> NO DEBERIA FUNCIONAR, pero funciona :(
	- comillas juntas hace que pete -> echo ""'✅
*/
