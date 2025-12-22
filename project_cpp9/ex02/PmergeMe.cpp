#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <climits>

// Constructeur par défaut
PmergeMe::PmergeMe()
{
}

// Constructeur de copie
PmergeMe::PmergeMe(PmergeMe const &src) : _vec(src._vec), _deq(src._deq)
{
}

// Opérateur d'assignation
PmergeMe &PmergeMe::operator=(PmergeMe const &rhs)
{
	if (this != &rhs)
	{
		_vec = rhs._vec;
		_deq = rhs._deq;
	}
	return *this;
}

// Destructeur
PmergeMe::~PmergeMe()
{
}

// Parser les arguments
void PmergeMe::parseInput(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		std::string arg(argv[i]);
		
		// Vérifier que ce sont uniquement des chiffres
		for (size_t j = 0; j < arg.length(); j++)
		{
			if (!std::isdigit(arg[j]))
				throw InvalidInputException();
		}

		// Convertir en nombre
		char *endPtr;
		long num = std::strtol(argv[i], &endPtr, 10);

		if (*endPtr != '\0' || num < 0 || num > INT_MAX)
			throw InvalidInputException();

		_vec.push_back(static_cast<int>(num));
		_deq.push_back(static_cast<int>(num));
	}

	if (_vec.empty())
		throw InvalidInputException();
}

// Recherche binaire pour vector
int PmergeMe::binarySearchVector(std::vector<int> &arr, int item, int low, int high)
{
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (arr[mid] == item)
			return mid + 1;
		else if (arr[mid] < item)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return low;
}

// Insertion sort pour vector (utilisé pour petits groupes)
void PmergeMe::insertSortVector(std::vector<int> &arr, int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int key = arr[i];
		int j = i - 1;

		// Utiliser la recherche binaire pour trouver la position
		int pos = binarySearchVector(arr, key, left, j);

		// Décaler les éléments
		while (j >= pos)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[pos] = key;
	}
}

// Merge pour vector
void PmergeMe::mergeVector(std::vector<int> &arr, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::vector<int> L(n1), R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}

	while (i < n1)
		arr[k++] = L[i++];
	while (j < n2)
		arr[k++] = R[j++];
}

// Merge sort récursif pour vector
void PmergeMe::mergeSortVector(std::vector<int> &arr, int left, int right)
{
	if (left < right)
	{
		// Pour petits groupes, utiliser insertion sort
		if (right - left + 1 <= 16)
		{
			insertSortVector(arr, left, right);
			return;
		}

		int mid = left + (right - left) / 2;
		mergeSortVector(arr, left, mid);
		mergeSortVector(arr, mid + 1, right);
		mergeVector(arr, left, mid, right);
	}
}

// Ford-Johnson pour vector
void PmergeMe::mergeInsertSortVector(std::vector<int> &arr)
{
	if (arr.size() <= 1)
		return;
	mergeSortVector(arr, 0, arr.size() - 1);
}

// Recherche binaire pour deque
int PmergeMe::binarySearchDeque(std::deque<int> &arr, int item, int low, int high)
{
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (arr[mid] == item)
			return mid + 1;
		else if (arr[mid] < item)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return low;
}

// Insertion sort pour deque
void PmergeMe::insertSortDeque(std::deque<int> &arr, int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int key = arr[i];
		int j = i - 1;

		int pos = binarySearchDeque(arr, key, left, j);

		while (j >= pos)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[pos] = key;
	}
}

// Merge pour deque
void PmergeMe::mergeDeque(std::deque<int> &arr, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::deque<int> L(n1), R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}

	while (i < n1)
		arr[k++] = L[i++];
	while (j < n2)
		arr[k++] = R[j++];
}

// Merge sort récursif pour deque
void PmergeMe::mergeSortDeque(std::deque<int> &arr, int left, int right)
{
	if (left < right)
	{
		if (right - left + 1 <= 16)
		{
			insertSortDeque(arr, left, right);
			return;
		}

		int mid = left + (right - left) / 2;
		mergeSortDeque(arr, left, mid);
		mergeSortDeque(arr, mid + 1, right);
		mergeDeque(arr, left, mid, right);
	}
}

// Ford-Johnson pour deque
void PmergeMe::mergeInsertSortDeque(std::deque<int> &arr)
{
	if (arr.size() <= 1)
		return;
	mergeSortDeque(arr, 0, arr.size() - 1);
}

// Trier les deux containers
void PmergeMe::sort()
{
	mergeInsertSortVector(_vec);
	mergeInsertSortDeque(_deq);
}

// Afficher les résultats
void PmergeMe::displayResults(double vecTime, double deqTime) const
{
	// Afficher Before (on utilise deq car il contient les mêmes valeurs non triées si on l'appelle avant sort)
	std::cout << "Before:";
	for (size_t i = 0; i < _vec.size() && i < 10; i++)
		std::cout << " " << _vec[i];
	if (_vec.size() > 10)
		std::cout << " [...]";
	std::cout << std::endl;

	// Afficher After
	std::cout << "After:";
	for (size_t i = 0; i < _vec.size() && i < 10; i++)
		std::cout << " " << _vec[i];
	if (_vec.size() > 10)
		std::cout << " [...]";
	std::cout << std::endl;

	// Afficher les temps
	std::cout << "Time to process a range of " << _vec.size() 
			  << " elements with std::vector : " << vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size() 
			  << " elements with std::deque  : " << deqTime << " us" << std::endl;
}

// Getters
std::vector<int> const &PmergeMe::getVector() const
{
	return _vec;
}

std::deque<int> const &PmergeMe::getDeque() const
{
	return _deq;
}

// Exception
const char *PmergeMe::InvalidInputException::what() const throw()
{
	return "Error";
}
