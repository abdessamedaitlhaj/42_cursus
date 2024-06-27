/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:18:27 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/15 22:28:37 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;

	if (argc < 2)
		return (0);
	stack_a = parse_args(argc, argv);
	if (!stack_a)
	{
		ft_lstclear(&stack_a);
		error();
	}
	if (is_sorted(stack_a))
		return (ft_lstclear(&stack_a), 0);
	sort_list(&stack_a);
	ft_lstclear(&stack_a);
}
