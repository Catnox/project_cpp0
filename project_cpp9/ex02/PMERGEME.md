# PmergeMe (Ford-Johnson) - Ex02

## Concept : Merge-Insert Sort avec deux containers

Cet exercice implémente l'algorithme **Ford-Johnson** (merge-insert sort) avec deux containers différents pour comparer les performances.

## Pourquoi std::vector et std::deque ?

Les containers déjà utilisés sont interdits :
- ❌ std::map (ex00)
- ❌ std::stack (ex01)

Containers choisis :
- ✅ **std::vector** : Tableau dynamique, cache-friendly
- ✅ **std::deque** : Double-ended queue, segments de mémoire

## L'algorithme Ford-Johnson (Merge-Insert Sort)

C'est un algorithme hybride qui combine :
1. **Merge Sort** : Pour diviser le problème
2. **Binary Insertion Sort** : Pour les petits sous-tableaux

### Pourquoi cet hybride ?

| Taille du tableau | Algorithme optimal |
|-------------------|-------------------|
| Grand (> 16 éléments) | Merge Sort O(n log n) |
| Petit (≤ 16 éléments) | Insertion Sort (moins d'overhead) |

## Implémentation

### Merge Sort récursif

```cpp
void mergeSortVector(std::vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        // Pour les petits tableaux, utiliser insertion sort
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
```

### Binary Insertion Sort

```cpp
void insertSortVector(std::vector<int> &arr, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int key = arr[i];
        
        // Trouver la position avec recherche binaire
        int pos = binarySearchVector(arr, key, left, i - 1);
        
        // Décaler les éléments
        for (int j = i - 1; j >= pos; j--)
            arr[j + 1] = arr[j];
            
        arr[pos] = key;
    }
}
```

### Recherche binaire

```cpp
int binarySearchVector(std::vector<int> &arr, int item, int low, int high)
{
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] < item)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}
```

## Mesure du temps

```cpp
#include <sys/time.h>

double getTimeInMicroseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000.0 + tv.tv_usec;
}

double start = getTimeInMicroseconds();
// ... tri ...
double end = getTimeInMicroseconds();
double duration = end - start;  // En microsecondes
```

## Comparaison vector vs deque

| Caractéristique | std::vector | std::deque |
|-----------------|-------------|------------|
| Mémoire | Contiguë | Segments |
| Cache | Très efficace | Moins efficace |
| Insertion milieu | O(n) | O(n) |
| Accès aléatoire | O(1) | O(1) |
| Performance tri | Généralement meilleur | Un peu plus lent |

### Pourquoi vector est souvent plus rapide ?

1. **Localité de cache** : Données contiguës en mémoire
2. **Préchargement** : Le CPU anticipe les accès
3. **Moins d'indirections** : Un seul pointeur vs plusieurs segments

## Format de sortie

```
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector : 2 us
Time to process a range of 5 elements with std::deque  : 3 us
```

## Validation des entrées

```cpp
void PmergeMe::parseInput(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        // Vérifier que c'est un nombre positif
        for (chaque caractère)
            if (!isdigit(c))
                throw InvalidInputException();
        
        long num = strtol(argv[i], NULL, 10);
        if (num < 0 || num > INT_MAX)
            throw InvalidInputException();
        
        _vec.push_back(num);
        _deq.push_back(num);
    }
}
```

## Complexité

| Opération | Complexité |
|-----------|------------|
| Ford-Johnson global | O(n log n) |
| Merge | O(n) |
| Binary Insertion (petits groupes) | O(n²) mais n ≤ 16 |

## Containers utilisés

✅ **std::vector** + **std::deque** (2 containers requis)

### Récapitulatif Module 09

| Exercice | Container(s) |
|----------|--------------|
| ex00 | std::map |
| ex01 | std::stack |
| ex02 | std::vector + std::deque |

Chaque container n'est utilisé qu'une seule fois dans le module, conformément aux règles.
