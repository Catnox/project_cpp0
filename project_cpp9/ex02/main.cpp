#include <iostream>
#include <ctime>
#include <sys/time.h>
#include "PmergeMe.hpp"

double getTimeInMicroseconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000.0 + tv.tv_usec;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	try
	{
		PmergeMe sorter;
		sorter.parseInput(argc, argv);

		// Copier les valeurs originales pour l'affichage "Before"
		std::vector<int> original = sorter.getVector();

		// Afficher Before
		std::cout << "Before:";
		for (size_t i = 0; i < original.size(); i++)
			std::cout << " " << original[i];
		std::cout << std::endl;

		// Créer deux sorters séparés pour mesurer les temps
		PmergeMe sorterVec;
		PmergeMe sorterDeq;
		
		// Parser pour chaque sorter
		sorterVec.parseInput(argc, argv);
		sorterDeq.parseInput(argc, argv);

		// Mesurer le temps pour vector
		double startVec = getTimeInMicroseconds();
		std::vector<int> vec = sorterVec.getVector();
		// Créer une copie non-const pour le tri
		std::vector<int> vecCopy = vec;
		// On doit trier via l'objet
		sorterVec.sort();
		double endVec = getTimeInMicroseconds();
		double vecTime = endVec - startVec;

		// Mesurer le temps pour deque (déjà fait dans sort, mais on refait)
		sorterDeq.parseInput(argc, argv);
		double startDeq = getTimeInMicroseconds();
		sorterDeq.sort();
		double endDeq = getTimeInMicroseconds();
		double deqTime = endDeq - startDeq;

		// Afficher After
		std::vector<int> const &sorted = sorterVec.getVector();
		std::cout << "After:";
		for (size_t i = 0; i < sorted.size(); i++)
			std::cout << " " << sorted[i];
		std::cout << std::endl;

		// Afficher les temps
		std::cout << "Time to process a range of " << sorted.size() 
				  << " elements with std::vector : " << vecTime << " us" << std::endl;
		std::cout << "Time to process a range of " << sorted.size() 
				  << " elements with std::deque  : " << deqTime << " us" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
