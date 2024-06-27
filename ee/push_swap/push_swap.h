/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:17:26 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/15 22:02:51 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

t_stack	*parse_args(int argc, char **argv);

size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str, char *flag);
void	ft_lstadd_back(t_stack **stack, t_stack *new);
void	ft_lstclear(t_stack **stack);
t_stack	*ft_lstlast(t_stack *stack);
t_stack	*ft_lstnew(int value);
int		ft_lstsize(t_stack *stack);
int		ft_isdigit(int c);
int		ft_isspace(int c);

int		is_sorted(t_stack *stack);
int		is_duplicate(t_stack *stack);
void	error(void);
void	free_args(char **args);

void	sort_list(t_stack **stack_a);
void	sort(t_stack **stack_a, t_stack **stack_b);
int		find_min(t_stack *stack_a);

void	sa(t_stack **stack_a);
void	sb(t_stack **stack_b);
void	ss(t_stack **stack_a, t_stack **stack_b);
void	pa(t_stack **stack_a, t_stack **stack_b);
void	pb(t_stack **stack_a, t_stack **stack_b);
void	ra(t_stack **stack_a);
void	rb(t_stack **stack_b);
void	rr(t_stack **stack_a, t_stack **stack_b);
void	rra(t_stack **stack_a);
void	rrb(t_stack **stack_b);
void	rrr(t_stack **stack_a, t_stack **stack_b);

#endif