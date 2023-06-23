/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 21:14:00 by ethan             #+#    #+#             */
/*   Updated: 2023/06/23 21:14:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Wordle.hpp"
#include <iostream>

int	main() {
	srand(time(NULL));
	try {
		Wordle	wordle;
		wordle.play();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}