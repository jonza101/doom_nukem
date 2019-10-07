/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 17:44:11 by jsteuber          #+#    #+#             */
/*   Updated: 2019/01/12 21:23:51 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*curr;
	t_list	*nlst;

	if (!alst || !del)
		return ;
	curr = *alst;
	while (curr != NULL)
	{
		nlst = curr->next;
		del(curr->content, curr->content_size);
		free(curr);
		curr = nlst;
	}
	*alst = NULL;
}
