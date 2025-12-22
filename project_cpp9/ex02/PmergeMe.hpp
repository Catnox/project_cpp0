#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe
{
private:
	std::vector<int>	_vec;
	std::deque<int>		_deq;

	// Ford-Johnson (merge-insert) pour vector
	void mergeInsertSortVector(std::vector<int> &arr);
	void insertSortVector(std::vector<int> &arr, int left, int right);
	void mergeVector(std::vector<int> &arr, int left, int mid, int right);
	void mergeSortVector(std::vector<int> &arr, int left, int right);

	// Ford-Johnson (merge-insert) pour deque
	void mergeInsertSortDeque(std::deque<int> &arr);
	void insertSortDeque(std::deque<int> &arr, int left, int right);
	void mergeDeque(std::deque<int> &arr, int left, int mid, int right);
	void mergeSortDeque(std::deque<int> &arr, int left, int right);

	// Recherche binaire pour insertion
	int binarySearchVector(std::vector<int> &arr, int item, int low, int high);
	int binarySearchDeque(std::deque<int> &arr, int item, int low, int high);

public:
	// Constructeurs et destructeur
	PmergeMe();
	PmergeMe(PmergeMe const &src);
	PmergeMe &operator=(PmergeMe const &rhs);
	~PmergeMe();

	// Méthodes principales
	void parseInput(int argc, char **argv);
	void sort();
	void displayResults(double vecTime, double deqTime) const;

	// Getters
	std::vector<int> const &getVector() const;
	std::deque<int> const &getDeque() const;

	// Exceptions
	class InvalidInputException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

#endif
