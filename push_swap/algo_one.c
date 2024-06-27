/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:26:10 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/15 21:31:07 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_two(t_stack **stack_a)
{
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a);
}

void	sort_three(t_stack **stack_a)
{
	if ((*stack_a)->value > (*stack_a)->next->value)
	{
		ra(stack_a);
		sort_two(stack_a);
	}
	else
		rra(stack_a);
	if ((*stack_a)->next->value > (*stack_a)->next->next->value)
	{
		rra(stack_a);
		sort_two(stack_a);
	}
	sort_two(stack_a);
}

static void	sort_four(t_stack **stack_a, t_stack **stack_b)
{
	if ((*stack_a)->value == find_min(*stack_a))
		pb(stack_a, stack_b);
	else
	{
		if ((*stack_a)->next->value == find_min(*stack_a))
			ra(stack_a);
		else if ((*stack_a)->next->next->value == find_min(*stack_a))
		{
			rra(stack_a);
			rra(stack_a);
		}
		else
			rra(stack_a);
		pb(stack_a, stack_b);
	}
	if (!is_sorted(*stack_a))
		sort_three(stack_a);
	pa(stack_a, stack_b);
}

static void	sort_five(t_stack **stack_a, t_stack **stack_b)
{
	if ((*stack_a)->value == find_min(*stack_a))
		pb(stack_a, stack_b);
	else
	{
		if ((*stack_a)->next->value == find_min(*stack_a))
			ra(stack_a);
		else if ((*stack_a)->next->next->value == find_min(*stack_a))
		{
			ra(stack_a);
			ra(stack_a);
		}
		else if ((*stack_a)->next->next->next->value == find_min(*stack_a))
		{
			rra(stack_a);
			rra(stack_a);
		}
		else
			rra(stack_a);
		pb(stack_a, stack_b);
	}
	if (!is_sorted(*stack_a))
		sort_four(stack_a, stack_b);
	pa(stack_a, stack_b);
}

void	sort_list(t_stack **stack_a)
{
	int		size;
	t_stack	*stack_b;

	stack_b = NULL;
	size = ft_lstsize(*stack_a);
	if (size == 2)
		sort_two(stack_a);
	else if (size == 3)
		sort_three(stack_a);
	else if (size == 4)
		sort_four(stack_a, &stack_b);
	else if (size == 5)
		sort_five(stack_a, &stack_b);
	else
		sort(stack_a, &stack_b);
	return ;
}
