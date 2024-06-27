/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:05:29 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/15 22:41:38 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_max_index(int index, t_stack *stack_b)
{
	t_stack	*tmp;
	int		i;

	i = 0;
	tmp = stack_b;
	while (tmp)
	{
		if (tmp->index == index)
			break ;
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	index_nodes(t_stack *stack_a)
{
	t_stack	*tmp1;
	t_stack	*tmp2;
	int		i;

	tmp1 = stack_a;
	while (tmp1)
	{
		i = 0;
		tmp2 = stack_a;
		while (tmp2)
		{
			if (tmp1->value > tmp2->value)
				i++ ;
			tmp2 = tmp2->next;
		}
		tmp1->index = i;
		tmp1 = tmp1->next;
	}
}

static void	final_sort(t_stack **stack_a, t_stack **stack_b)
{
	while (*stack_b)
	{
		while ((*stack_b)->index != ft_lstsize(*stack_b) - 1)
		{
			if (find_max_index(ft_lstsize(*stack_b) - 1,
					*stack_b) < ft_lstsize(*stack_b) / 2)
				rb(stack_b);
			else
				rrb(stack_b);
		}
		pa(stack_a, stack_b);
	}
}

void	sort(t_stack **stack_a, t_stack **stack_b)
{
	int	offset;

	index_nodes(*stack_a);
	offset = 16;
	if (ft_lstsize(*stack_a) > 100)
		offset = 32;
	while (*stack_a)
	{
		if (ft_lstsize(*stack_b) > (*stack_a)->index)
			pb(stack_a, stack_b);
		else if (ft_lstsize(*stack_b) + offset >= (*stack_a)->index)
		{
			pb(stack_a, stack_b);
			rb(stack_b);
		}
		else
			ra(stack_a);
	}
	final_sort(stack_a, stack_b);
}

int	find_min(t_stack *stack_a)
{
	int	min;

	min = stack_a->value;
	while (stack_a)
	{
		if (stack_a->value < min)
			min = stack_a->value;
		stack_a = stack_a->next;
	}
	return (min);
}
