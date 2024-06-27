/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:07:54 by aait-lha          #+#    #+#             */
/*   Updated: 2024/02/11 20:22:59 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

# define HEX_LO "0123456789abcdef"
# define HEX_UP "0123456789ABCDEF"

int		ft_printf(const char *fr, ...);

int		pr_char(int c);
int		pr_str(char *str);
int		pr_adr(uintptr_t adr);
int		pr_dec(int nbr);
int		pr_uns_nbr(unsigned int nbr);
int		pr_hex(unsigned int nbr, int c);

#endif