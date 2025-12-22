#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

// Version pour les tableaux non-const avec fonction prenant une référence non-const
template<typename T, typename F>
void iter(T *array, size_t const length, F func)
{
	for (size_t i = 0; i < length; i++)
		func(array[i]);
}

// Version pour les tableaux const avec fonction prenant une référence const
template<typename T, typename F>
void iter(T const *array, size_t const length, F func)
{
	for (size_t i = 0; i < length; i++)
		func(array[i]);
}

#endif
