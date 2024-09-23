/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-asli <hel-asli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:20:44 by hel-asli          #+#    #+#             */
/*   Updated: 2024/08/31 11:09:29 by hel-asli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_env(t_env **env, char **ev)
{
	char	**sp;
	int		i;

	i = 0;
	(void)env;
	while (ev[i])
	{
		sp = ft_env_split(ev[i]);
		ft_lstadd_back(env, ft_lstnew(ft_strdup(sp[0]), ft_strdup(sp[1]), true));
		ft_free(sp);
		i++;
	}
}


void	set_env(t_env **env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_lstadd_back(env, ft_lstnew(ft_strdup("PATH"),
			ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."), true));
	ft_lstadd_back(env, ft_lstnew(ft_strdup("PWD"), pwd, true));
	ft_lstadd_back(env, ft_lstnew(ft_strdup("SHLVL"), ft_strdup("1"), true));
	ft_lstadd_back(env, ft_lstnew(ft_strdup("_"), ft_strdup("/usr/bin/env"), true));
}

int	main(int ac, char **av, char **ev)
{
	t_shell		shell;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	shell.env = NULL;
	shell.commands = NULL;
	if (ev == NULL || *ev == NULL)
	{
		set_env(&shell.env);
		set_env(&shell.export);
	}
	else
	{
		built_env(&shell.env, ev);
		build_export(&shell.export, ev);
	}
	read_input(&shell, "minishell: ", ev);
}
