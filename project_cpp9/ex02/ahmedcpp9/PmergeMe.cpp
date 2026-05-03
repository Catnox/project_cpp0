/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:13:25 by aboutale          #+#    #+#             */
/*   Updated: 2026/01/02 21:13:26 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

 int _compteur = 0;

bool compareAndCount(int a, int b) {
   _compteur++;
    return a < b;
} 



PmergeMe::PmergeMe() {


}



PmergeMe::PmergeMe(const PmergeMe& copy) {

	_myVector = copy._myVector;
	_myDeque = copy._myDeque;
}



PmergeMe& PmergeMe::operator=(const PmergeMe& copy) {

	if (this != &copy) {

		_myVector = copy._myVector;
		_myDeque = copy._myDeque;
	}
	return *this;
}



PmergeMe::~PmergeMe() {


}



std::vector<int> PmergeMe::_jakobStahlInsertion(size_t max_size) {

	std::vector<int> jakobSeq;
	if(max_size < 2)
		return jakobSeq;

	size_t next = 0;
	size_t prev = 0;
	size_t last = 1;
	while (next < max_size) {

		next = last + 2 * prev;
		if (next >= max_size)
			break;
		jakobSeq.push_back(next);
		prev = last;
		last = next;

	}
	return (jakobSeq);

}


std::deque<int> PmergeMe::_jakobStahlDequeInsertion(size_t max_size) {

	std::deque<int> jakobSeq;
	if(max_size < 2)
		return jakobSeq;

	size_t next = 0;
	size_t prev = 0;
	size_t last = 1;
	while (next < max_size) {

		next = last + 2 * prev;
		if (next >= max_size)
			break;
		jakobSeq.push_back(next);
		prev = last;
		last = next;
	}
	return (jakobSeq);

}



void PmergeMe::_sortVector(std::vector<int> &mainContainer) {

	if (mainContainer.size() < 2)
		return;
	int alone = -1;

	if (mainContainer.size() % 2 != 0)
	{
		alone = mainContainer.back();
		mainContainer.pop_back();
	}
	std::vector< std::pair<int,int> > pairs;
	for (size_t i = 0; i < mainContainer.size(); i +=2) {

		if (mainContainer[i] > mainContainer[i + 1]) {

			pairs.push_back(std::make_pair(mainContainer[i], mainContainer[i + 1]));
		}
		else 
			pairs.push_back(std::make_pair(mainContainer[i + 1], mainContainer[i]));
	}
	mainContainer.clear();
	for (size_t i = 0; i < pairs.size(); i++) {

		 mainContainer.push_back(pairs[i].first);
	}
	_sortVector(mainContainer);
	
	std::vector<std::pair<int, int> > sortedPairs;
	for (size_t i= 0; i < mainContainer.size(); i++) {

		for (size_t j = 0 ; j < pairs.size(); j++) {

			if (pairs[j].first == mainContainer[i]){

				sortedPairs.push_back(pairs[j]);
				break;
			}	
		}
	}
	pairs = sortedPairs;
	mainContainer.insert(mainContainer.begin(), pairs[0].second);
	size_t prevJakobIndex = 0;
	std::vector<int> jakobSeq = _jakobStahlInsertion(pairs.size());
	for (size_t i = 0; i < jakobSeq.size() ; i++) {

		size_t currentJakobIndex = jakobSeq[i];
		if (currentJakobIndex >= pairs.size() )
			currentJakobIndex = pairs.size() - 1;
		for (size_t j = currentJakobIndex; j > prevJakobIndex; j--) {
	
			std::vector<int>::iterator max = std::lower_bound(mainContainer.begin(), mainContainer.end(),pairs[j].first);
			std::vector<int>::iterator pos = std::lower_bound(mainContainer.begin(), max, pairs[j].second);
			mainContainer.insert(pos, pairs[j].second);
		}
		prevJakobIndex = currentJakobIndex;
	}
	if (prevJakobIndex <= pairs.size() - 1){

		for (size_t k = pairs.size() - 1; k > prevJakobIndex; k--) {

			std::vector<int>::iterator max = std::lower_bound(mainContainer.begin(), mainContainer.end(),pairs[k].first);
			std::vector<int>::iterator pos = std::lower_bound(mainContainer.begin(), max, pairs[k].second,  compareAndCount);
			mainContainer.insert(pos, pairs[k].second);
		}	
	}
	if ( alone != -1) {
		
		std::vector<int>::iterator pos = std::lower_bound(mainContainer.begin(), mainContainer.end(), alone);
		mainContainer.insert(pos, alone);
	}
}



void PmergeMe::_sortDeque(std::deque<int> &mainContainer) {

	if (mainContainer.size() < 2)
		return;

	int alone = -1;
	if (mainContainer.size() % 2 != 0)
	{
		alone = mainContainer.back();
		mainContainer.pop_back();
	}

	std::deque< std::pair <int, int > > pairs;
	for (size_t i = 0 ; i < mainContainer.size(); i+=2) {
		
		if (mainContainer[i] > mainContainer[i + 1])
			pairs.push_back(std::make_pair(mainContainer[i], mainContainer[i + 1]));
		else
			pairs.push_back(std::make_pair(mainContainer[i + 1], mainContainer[i]));
	}
	mainContainer.clear();
	for(size_t i = 0; i < pairs.size(); i++) {
		
		mainContainer.push_back(pairs[i].first);
	}
	_sortDeque(mainContainer);
	std::deque< std::pair <int, int> > sortedPairs;
	for (size_t i = 0 ; i < mainContainer.size(); i++) {

		for (size_t j = 0; j < pairs.size(); j++) {

			if (pairs[j].first == mainContainer[i]) {

				sortedPairs.push_back(pairs[j]);
				break;
			}
		}	
	}
	pairs = sortedPairs;
	mainContainer.push_front(pairs[0].second);
	size_t prevJakobIndex = 0;
	std::deque<int> jakobSeq = _jakobStahlDequeInsertion(pairs.size());
	 for (size_t i = 0; i < jakobSeq.size(); i++) {

		size_t currentJakobIndex = jakobSeq[i];
		if (currentJakobIndex >= pairs.size())
			currentJakobIndex = pairs.size() - 1;
		for (size_t j = currentJakobIndex ; j > prevJakobIndex ; j--) {


			std::deque<int>::iterator max = std::lower_bound(mainContainer.begin(), mainContainer.end(), pairs[j].first );
			std::deque<int>::iterator pos = std::lower_bound(mainContainer.begin(), max, pairs[j].second, compareAndCount );
			mainContainer.insert(pos, pairs[j].second);
		}
		prevJakobIndex = currentJakobIndex;
	}
	if(prevJakobIndex <= pairs.size() - 1) {
			
		for (size_t k = pairs.size() - 1 ; k > prevJakobIndex; k--) {
		
			std::deque<int>::iterator max = std::lower_bound(mainContainer.begin(), mainContainer.end(), pairs[k].first );
			std::deque<int>::iterator pos = std::lower_bound(mainContainer.begin(), max, pairs[k].second );
			mainContainer.insert(pos, pairs[k].second);
		}
	}
	if (alone != -1) {
		
		std::deque<int>::iterator pos = std::lower_bound(mainContainer.begin(), mainContainer.end(), alone);
		mainContainer.insert(pos, alone);
	}
}



void PmergeMe::sort(int argc, char **argv) {

	_myVector.clear();
    _myDeque.clear();
	for(int i = 1; i < argc; i++ ) {

		std::string str = argv[i];
		for (size_t j = 0 ; j < str.size() ; j++) {
			
			if (!isdigit(str[j])) {

			std::cerr << "Error" << std::endl;
			return;
			}
		}
		long number = atol(str.c_str());
		if (number < INT_MIN || number > INT_MAX || number < 0) {

			std::cerr << "Error" << std::endl;
			return;
		}
		for (size_t k = 0; k < _myVector.size(); k++) {

			if (_myVector[k] == (int)number) {

				std::cerr << "Error" << std::endl;
				return;
			}

		}
		_myVector.push_back(number);
	}
	std::cout << "Before: " ;
		for (size_t i = 0 ; i < _myVector.size() ; i++) {
		std::cout <<  _myVector[i] << " ";
	}
	std::cout << std::endl;

	_myVector.clear();
	struct timeval startVector;
	gettimeofday(&startVector, NULL);

	for (int i = 1; i < argc; i++) {

		long number = atol(argv[i]);
		_myVector.push_back(number);
	}
	_sortVector(_myVector);
	struct timeval endVector;
	gettimeofday(&endVector, NULL);
	long double res_start = (startVector.tv_sec * 1000000) + startVector.tv_usec ;
	long double res_end = (endVector.tv_sec* 1000000) + endVector.tv_usec;
	long double res = (res_end - res_start);
	
	std::cout << "After: " ;
	for (size_t i = 0 ; i < _myVector.size() ; i++) {
		std::cout <<  _myVector[i] << " ";
	}
	std::cout << std::endl;
	std::cout << std::fixed << std::setprecision(3) << "Time to process a range of " << _myVector.size() << " elements with std::vector : " <<  res << " us" << std::endl;
	
	
	struct timeval startDeque;
	gettimeofday(&startDeque, NULL);

	for (int i = 1; i < argc ; i++){

		long number = atol(argv[i]);
		_myDeque.push_back(number);
	}
	
	_sortDeque(_myDeque);
	struct timeval endDeque;
	gettimeofday(&endDeque, NULL);
	res_start = (startDeque.tv_sec * 1000000) + startDeque.tv_usec ;
	res_end = (endDeque.tv_sec* 1000000) + endDeque.tv_usec;
	res = (res_end - res_start);
	std::cout << std::fixed << std::setprecision(3) << "Time to process a range of " << _myDeque.size() << " elements with std::deque : " <<  res << " us" << std::endl;
	std::cout << _compteur << std::endl;
}
