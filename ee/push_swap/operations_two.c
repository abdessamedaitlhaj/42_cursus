/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:46:15 by aait-lha          #+#    #+#             */
/*   Updated: 2024/04/20 14:30:21 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rb(t_stack **stack_b)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	tmp = *stack_b;
	last = *stack_b;
	while (last->next)
		last = last->next;
	*stack_b = tmp->next;
	tmp->next = NULL;
	last->next = tmp;
	write(1, "rb\n", 3);
}

void	rr(t_stack **stack_a, t_stack **stack_b)
{
	ra(stack_a);
	rb(stack_b);
	write(1, "rr\n", 3);
}

void	rra(t_stack **stack_a)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	tmp = *stack_a;
	while (tmp->next->next)
		tmp = tmp->next;
	last = tmp->next;
	tmp->next = NULL;
	last->next = *stack_a;
	*stack_a = last;
	write(1, "rra\n", 4);
}

void	rrb(t_stack **stack_b)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	tmp = *stack_b;
	while (tmp->next->next)
		tmp = tmp->next;
	last = tmp->next;
	tmp->next = NULL;
	last->next = *stack_b;
	*stack_b = last;
	write(1, "rrb\n", 4);
}

void	ra(t_stack **stack_a)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	tmp = *stack_a;
	last = *stack_a;
	while (last->next)
		last = last->next;
	*stack_a = tmp->next;
	tmp->next = NULL;
	last->next = tmp;
	write(1, "ra\n", 3);
}
