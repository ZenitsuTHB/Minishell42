/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:22:28 by deordone          #+#    #+#             */
/*   Updated: 2024/02/17 13:55:04 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../library/libft/libft.h"
# include "../library/dprintf/ft_dprintf.h"
# define BUG {\
		dprintf(2, "Ha entrado en -> %s\n", __FILE__);\
		dprintf(2, "En la funcion -> %s\n", __func__);\
		dprintf(2, "En la linea -> %d\n", __LINE__);\
	      }
#endif
