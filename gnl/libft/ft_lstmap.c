/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 14:22:15 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/12/01 18:52:09 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *temp;
	t_list *list;

	if (lst && f)
	{
		temp = (*f)(lst);
		list = temp;
		while (lst->next)
		{
			if (!(temp->next = (*f)(lst->next)))
				return (NULL);
			temp = temp->next;
			lst = lst->next;
		}
		return (list);
	}
	return (NULL);
}
