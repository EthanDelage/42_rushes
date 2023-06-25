/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wordle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:10:00 by ethan             #+#    #+#             */
/*   Updated: 2023/06/23 22:10:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "Wordle.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

Wordle::Wordle():
	_nbAttempts(0),
	_maxNbAttempts(MAX_NB_ATTEMPTS) {

	for (auto &_inputtedWord : _inputtedWords) {
		_inputtedWord = "";
	}

	this->_dictionary = parseDictionary();
	this->_mysteryWord = this->getMysteryWord();
}

WordleDictionaryType	Wordle::parseDictionary() {
	WordleDictionaryType	result;
	std::ifstream			inputFile(DICTIONARY_FILE);

	if (!inputFile.is_open())
		throw std::runtime_error("Failed to open file " DICTIONARY_FILE);

	std::string	line;
	for (size_t i = 1; std::getline(inputFile, line); i++) {
		if (line.length() != 5)
			throw std::runtime_error("Word at line number "
				+ std::to_string(i) + " is not 5 characters long");
		for (int j = 0; j < 5; ++j) {
			if (!isalpha(line[j]))
				throw std::runtime_error("A word contains an invalid character");
		}
		std::transform(line.begin(), line.end(), line.begin(), ::toupper);
		result[line] = false;
	}
	inputFile.close();
	if (result.size() == 0)
		throw std::runtime_error("The dictionary is empty");
	return (result);
}

void	Wordle::play() {
	std::cout << "Number of words: "<< _dictionary.size() << std::endl;
	display();
	while (_nbAttempts < _maxNbAttempts && !std::cin.eof()) {
		_inputtedWords[_nbAttempts] = getInput();
		display();
		if (_inputtedWords[_nbAttempts] == _mysteryWord) {
			std::cout << "Congratulations you found the word "
				<< _mysteryWord << " in " << _nbAttempts + 1
				<< (_nbAttempts == 0 ? " guess ": " guesses") << std::endl;
			return ;
		}
		++_nbAttempts;
	}
	std::cout << "Too bad the word to guess was " << _mysteryWord << std::endl;
}

std::string		Wordle::getMysteryWord() {
	int		randomNumber = rand() % this->_dictionary.size();
	auto	iterator = this->_dictionary.begin();

	std::advance(iterator, randomNumber);
	return (iterator->first);
}

std::string Wordle::getInput() {
	std::string	input;

	std::cout << "Enter a word: ";
	if (!std::getline(std::cin, input))
		throw std::runtime_error("Failed to read input");
	std::transform(input.begin(), input.end(), input.begin(), ::toupper);
	while (!isValidWord(input)) {
		if (input.length() != 5)
			std::cerr << "The word must contain exactly 5 letters" << std::endl;
		else
			std::cerr << "Not in word list" << std::endl;
		std::cout << "Enter a word: ";
		std::getline(std::cin, input);
		std::transform(input.begin(), input.end(), input.begin(), ::toupper);
	}
	return (input);
}

bool Wordle::isValidWord(std::string &word) {
	return (_dictionary.count(word));
}

void Wordle::display() {
	for (int i = 0; i < MAX_NB_ATTEMPTS; ++i) {
		displayRow(i);
	}
}

void Wordle::displayRow(unsigned int rowIndex) {
	std::string	currentWord = _inputtedWords[rowIndex];

	if (currentWord.empty())
		std::cout << "_ _ _ _ _" << std::endl;
	else {
		for (int i = 0; i < 5; ++i) {
			std::cout << getLetterColor(currentWord, i) << currentWord[i] << DEFAULT << " ";
		}
		std::cout << std::endl;
	}
}

std::string Wordle::getLetterColor(std::string &word, size_t index) {
	std::string	copyMysteryWord(_mysteryWord);

	for (int i = 0; copyMysteryWord[i]; ++i) {
		if (word[i] == copyMysteryWord[i])
			copyMysteryWord[i] = ' ';
	}
	if (word[index] == _mysteryWord[index])
		return (GREEN);
	else if (copyMysteryWord.find(word[index]) != std::string::npos
		&& word.find(word[index]) == index)
		return (YELLOW);
	return (GREY);
}
