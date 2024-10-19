/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-asli <hel-asli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:20:44 by hel-asli          #+#    #+#             */
/*   Updated: 2024/10/19 03:47:48 by hel-asli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int rl_signal = 0;

// void	built_env(t_env **env, char **ev)
// {
// 	char	**sp;
// 	int		i;

// 	i = 0;
// 	(void)env;
// 	sp = NULL;
// 	while (ev[i])
// 	{
// 		sp = ft_env_split(ev[i]);
// 		if (ft_strcmp(sp[0], "OLDPWD"))
// 			ft_lstadd_back(env, ft_lstnew(ft_strdup(sp[0]), ft_strdup(sp[1])));
// 		ft_free(sp);
// 		i++;
// 	}
// }


// void	set_env(t_env **env)
// {
// 	char	*pwd;

// 	pwd = getcwd(NULL, 0);
// 	ft_lstadd_back(env, ft_lstnew(ft_strdup("PATH"),
// 			ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
// 	ft_lstadd_back(env, ft_lstnew(ft_strdup("PWD"), pwd));
// 	ft_lstadd_back(env, ft_lstnew(ft_strdup("SHLVL"), ft_strdup("1")));
// 	ft_lstadd_back(env, ft_lstnew(ft_strdup("_"), ft_strdup("/usr/bin/env")));
// 	ft_lstadd_back(env, ft_lstnew(ft_strdup("OLDPWD"), NULL));
// }




void set_terminal_new_attr(struct termios *old_attr)
{
	struct termios new_attr;

	tcgetattr(STDIN_FILENO, &new_attr);
	new_attr = *old_attr;
}

void restore_terminal_old_attr(struct termios *old_attr)
{
	tcsetattr(STDIN_FILENO, TCSANOW, old_attr);
}
void setup_signals(void)
{
    struct sigaction sa_int, sa_quit;
    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESETHAND | SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);
    
    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;
    sigaction(SIGQUIT, &sa_quit, NULL);
}


int	main(int ac, char **av, char **ev)
{
	t_shell		shell;
	(void)av;
	if (!isatty(STDIN_FILENO) || ac != 1)
		exit(EXIT_FAILURE);
	tcgetattr(STDIN_FILENO, &shell.old_attr);
	tcgetattr(STDIN_FILENO, &shell.copy);
	shell.copy.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &shell.copy);
	setup_signals();
	shell.env = NULL;
	shell.commands = NULL;
	shell.exit_status = 0;
	shell.escape = 1;
	if (!ev || !*ev)
		set_env(&shell.env);
	else
		built_env(&shell.env, ev);
	read_input(&shell, "minishell$ ");
	env_clear(&shell.env);
	restore_terminal_old_attr(&shell.old_attr);
}
