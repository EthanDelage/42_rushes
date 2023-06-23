/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wordle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:10:00 by ethan             #+#    #+#             */
/*   Updated: 2023/06/23 22:10:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef WORDLE_HPP
# define WORDLE_HPP

# include <string>
# include <unordered_map>

# define DICTIONARY_FILE	"./data/words.txt"
# define MAX_NB_ATTEMPTS	6
# define GREEN				"\e[0;32m"
# define YELLOW				"\e[0;33m"
# define GREY				"\e[0;90m"
# define DEFAULT			"\e[0m"

typedef std::unordered_map<std::string, bool> WordleDictionaryType;

class Wordle {

public:
	Wordle();

	void	play();

private:
	std::string				_mysteryWord;
	std::string				_inputtedWords[MAX_NB_ATTEMPTS];
	WordleDictionaryType	_dictionary;
	unsigned int			_nbAttempts;
	unsigned int const		_maxNbAttempts;

	std::string		getMysteryWord();
	std::string		getInput();
	bool			isValidWord(std::string &word);
	void			display();
	void			displayRow(unsigned int rowIndex);
	std::string		getLetterColor(std::string &word, size_t index);
};

#endif