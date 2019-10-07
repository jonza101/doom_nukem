/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 17:46:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/01/22 19:26:28 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*rem(t_list *ret)
{
	t_list	*curr;

	curr = ret;
	while (curr != NULL)
	{
		ret = curr->next;
		free(curr->content);
		free(curr);
		curr = ret;
	}
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*curr;
	t_list	*ret;

	if (!lst || !f)
		return (NULL);
	if ((curr = f(lst)) == NULL)
		return (NULL);
	ret = curr;
	while (lst->next)
	{
		lst = lst->next;
		if ((curr->next = f(lst)) == NULL)
			return (rem(ret));
		curr = curr->next;
	}
	return (ret);
}
