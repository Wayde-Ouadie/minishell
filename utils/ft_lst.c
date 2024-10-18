/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-asli <hel-asli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 03:10:56 by hel-asli          #+#    #+#             */
/*   Updated: 2024/10/18 00:52:19 by hel-asli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstlast(t_env *env)
{
	if (!env)
		return (NULL);
	while (env && env->next != NULL)
		env = env->next;
	return (env);
}

// void	env_clear(t_env *env)
// {
// 	t_env *curr;
// 	t_env *tmp;

// 	curr = env;
// 	tmp = NULL;
// 	while (curr)
// 	{
// 		tmp = curr;
// 		curr = curr->next;
// 		free(tmp->key);
// 		free(tmp->value);
// 	}
// }

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
			ft_lstlast(*lst)->next = new;
	}
}

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	ft_back_addlst(t_commands **lst, t_commands *new)
{
	t_commands	*last;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
		}
		else
		{
			last = ft_last(*lst);
			last->next = new;
		}
	}
}

t_commands	*ft_last(t_commands *node)
{
	if (!node)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

void	cmds_clear(t_commands **cmds)
{
	t_commands *curr;
	t_commands *tmp;

	if (!cmds)
		return ;
	curr = *cmds;
	tmp = NULL;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		if (tmp)
		{
			if (tmp->args)
				ft_free(tmp->args);
			if (tmp->redirect)
				clear_redirect(&tmp->redirect);
			free(tmp);
			tmp = NULL;
		}
	}
	*cmds = NULL;
}
