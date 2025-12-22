# Classe Template Array - Ex02

## Concept : Classe Template

Une **classe template** permet de créer des classes génériques réutilisables avec n'importe quel type. C'est le même principe que les templates de fonctions, mais appliqué aux classes.

## Structure de la classe Array

```cpp
template<typename T>
class Array
{
private:
    T           *_elements;  // Tableau dynamique
    unsigned int _size;      // Taille du tableau

public:
    Array();                              // Constructeur par défaut
    Array(unsigned int n);                // Constructeur avec taille
    Array(Array const &src);              // Constructeur de copie
    Array &operator=(Array const &rhs);   // Opérateur d'assignation
    ~Array();                             // Destructeur
    
    T &operator[](unsigned int index);              // Accès []
    T const &operator[](unsigned int index) const;  // Accès [] const
    unsigned int size() const;                      // Getter taille
};
```

## Fichiers séparés : .hpp et .tpp

### Pourquoi un fichier .tpp ?

Les templates doivent être entièrement visibles par le compilateur lors de l'instanciation. On ne peut pas séparer déclaration (.hpp) et définition (.cpp) comme d'habitude.

**Solution** : Fichier `.tpp` inclus à la fin du `.hpp`

```cpp
// Array.hpp
#ifndef ARRAY_HPP
#define ARRAY_HPP

template<typename T>
class Array { /* déclarations */ };

#include "Array.tpp"  // Inclusion de l'implémentation

#endif
```

## Implémentations clés

### Constructeur avec taille (initialisation par défaut)

```cpp
template<typename T>
Array<T>::Array(unsigned int n) : _elements(new T[n]()), _size(n)
{
}
```

**Le `()` dans `new T[n]()`** est crucial :
- `new int[5]` → valeurs non initialisées (garbage)
- `new int[5]()` → valeurs initialisées à 0

### Deep Copy (Copie profonde)

```cpp
template<typename T>
Array<T> &Array<T>::operator=(Array const &rhs)
{
    if (this != &rhs)
    {
        delete[] _elements;           // Libérer l'ancienne mémoire
        _size = rhs._size;
        _elements = new T[_size]();   // Allouer nouvelle mémoire
        for (unsigned int i = 0; i < _size; i++)
            _elements[i] = rhs._elements[i];  // Copier les éléments
    }
    return *this;
}
```

**Pourquoi deep copy ?**
- Shallow copy : copie le pointeur → deux objets pointent sur la même mémoire
- Deep copy : copie les données → deux tableaux indépendants

### Opérateur [] avec vérification

```cpp
template<typename T>
T &Array<T>::operator[](unsigned int index)
{
    if (index >= _size)
        throw OutOfBoundsException();
    return _elements[index];
}
```

Contrairement aux tableaux C natifs, notre `Array` vérifie les bornes et lance une exception si l'index est invalide.

## La forme canonique complète

Cette classe respecte la **Orthodox Canonical Form** de C++98 :

| Élément | Rôle |
|---------|------|
| Constructeur par défaut | Créer un objet vide |
| Constructeur de copie | Créer une copie indépendante |
| Opérateur d'assignation | Copier un objet dans un autre |
| Destructeur | Libérer les ressources |

## Exception personnalisée

```cpp
class OutOfBoundsException : public std::exception
{
public:
    virtual const char *what() const throw()
    {
        return "Index out of bounds";
    }
};
```

- Hérite de `std::exception`
- Override de `what()` pour le message d'erreur
- `throw()` : spécification d'exception (n'en lance aucune)

## Avantages vs tableau C natif

| Tableau C | Array<T> |
|-----------|----------|
| Pas de vérification des bornes | Exception si hors limites |
| Taille inconnue | `size()` disponible |
| Gestion mémoire manuelle | RAII automatique |
| Copie = partage de pointeur | Deep copy |

## Utilisation

```cpp
Array<int> arr(5);       // 5 entiers initialisés à 0
arr[0] = 42;             // Accès et modification
std::cout << arr.size(); // Affiche 5

Array<int> copy = arr;   // Copie profonde
copy[0] = 100;           // Ne modifie pas arr

arr[10] = 0;             // Exception: Index out of bounds
```

## Points importants

1. **RAII** (Resource Acquisition Is Initialization) : La mémoire est automatiquement libérée à la destruction de l'objet.

2. **Généricité** : Fonctionne avec int, double, string, ou n'importe quelle classe.

3. **Sécurité** : Vérification des bornes contrairement aux tableaux C.

4. **Pas d'allocation préventive** : On alloue exactement la taille demandée.
