/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:18:27 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/15 22:32:46 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	apply(t_stack **stack_a, t_stack **stack_b, char *line)
{
	if (!ft_strncmp(line, "sa\n", 3))
		sa(stack_a);
	else if (!ft_strncmp(line, "sb\n", 3))
		sb(stack_b);
	else if (!ft_strncmp(line, "ss\n", 3))
		ss(stack_a, stack_b);
	else if (!ft_strncmp(line, "pa\n", 3))
		pa(stack_a, stack_b);
	else if (!ft_strncmp(line, "pb\n", 3))
		pb(stack_a, stack_b);
	else if (!ft_strncmp(line, "ra\n", 3))
		ra(stack_a);
	else if (!ft_strncmp(line, "rb\n", 3))
		rb(stack_b);
	else if (!ft_strncmp(line, "rr\n", 3))
		rr(stack_a, stack_b);
	else if (!ft_strncmp(line, "rra\n", 4))
		rra(stack_a);
	else if (!ft_strncmp(line, "rrb\n", 4))
		rrb(stack_b);
	else if (!ft_strncmp(line, "rrr\n", 4))
		rrr(stack_a, stack_b);
	else
		error();
}

static void	apply_instructions(t_stack **stack_a)
{
	t_stack	*stack_b;
	char	*line;

	stack_b = NULL;
	line = get_next_line(0);
	while (line)
	{
		apply(stack_a, &stack_b, line);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	if (is_sorted(*stack_a) && !stack_b)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	ft_lstclear(&stack_b);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;

	if (argc < 2)
		return (0);
	stack_a = parse_args(argc, argv);
	apply_instructions(&stack_a);
	ft_lstclear(&stack_a);
}
