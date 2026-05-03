/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:13:20 by aboutale          #+#    #+#             */
/*   Updated: 2026/01/02 21:13:21 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <deque>
#include <climits>
#include <cctype>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sys/time.h>
#include <algorithm>


class PmergeMe {

	private :

		std::vector<int> _myVector;
		std::deque<int> _myDeque;
		

		void _sortVector(std::vector<int> &vec);
		std::vector<int> _jakobStahlInsertion(size_t max_size);
		std::deque<int> _jakobStahlDequeInsertion(size_t max_size);
		void _sortDeque(std::deque<int> &deq);

	public : 

		PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator=(const PmergeMe& copy);
		~PmergeMe();

		void sort(int argc, char **argv);


};

#endif