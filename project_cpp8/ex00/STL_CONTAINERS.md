# EasyFind - Ex00

## Concept : Templates et Containers STL

Cet exercice introduit l'utilisation combinée des **templates** avec les **containers de la STL** (Standard Template Library).

## La STL en bref

La STL fournit des containers génériques :

| Container | Description | Accès |
|-----------|-------------|-------|
| `std::vector` | Tableau dynamique | Accès direct O(1) |
| `std::list` | Liste doublement chaînée | Accès séquentiel O(n) |
| `std::deque` | Double-ended queue | Accès direct O(1) |

## La fonction easyfind

```cpp
template<typename T>
typename T::iterator easyfind(T &container, int value)
{
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw NotFoundException();
    return it;
}
```

### Décryptage

1. **`template<typename T>`** : T sera un container (vector, list, deque...)

2. **`typename T::iterator`** : 
   - Chaque container STL définit un type `iterator`
   - `typename` est obligatoire car `T::iterator` est un type dépendant
   - Sans `typename`, le compilateur ne sait pas si c'est un type ou une variable

3. **`std::find`** : Algorithme STL qui cherche un élément
   - Prend deux itérateurs (début et fin)
   - Retourne un itérateur vers l'élément trouvé, ou `end()` si non trouvé

4. **Gestion d'erreur** : Exception si non trouvé (comme demandé dans le sujet)

## Le mot-clé typename

```cpp
// ERREUR sans typename
T::iterator it;  // Le compilateur ne sait pas si c'est un type

// CORRECT avec typename
typename T::iterator it;  // Explicitement un type
```

**Règle** : Utiliser `typename` devant tout type dépendant d'un paramètre template.

## Itérateurs

Les itérateurs sont des "pointeurs généralisés" pour parcourir les containers.

```cpp
std::vector<int> vec;
vec.push_back(1);
vec.push_back(2);

// Parcours avec itérateur
for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    std::cout << *it << " ";
```

### Méthodes clés

| Méthode | Description |
|---------|-------------|
| `begin()` | Itérateur vers le premier élément |
| `end()` | Itérateur après le dernier élément |
| `*it` | Déréférencement (accès à la valeur) |
| `++it` | Avancer à l'élément suivant |

## std::find (algorithme STL)

```cpp
#include <algorithm>

std::vector<int>::iterator it = std::find(vec.begin(), vec.end(), 42);
if (it != vec.end())
    std::cout << "Trouvé!";
```

- Parcourt de `begin()` à `end()`
- Retourne `end()` si non trouvé
- Complexité : O(n) pour les containers séquentiels

## Pourquoi pas les containers associatifs ?

Le sujet interdit les containers associatifs (`map`, `set`) car :

1. Ils ne stockent pas directement des `int` simples
   - `std::map<K, V>` stocke des paires clé-valeur
   - `std::set<T>` a sa propre méthode `find()` optimisée

2. Ils ont leurs propres méthodes de recherche O(log n)
   - Utiliser `std::find` serait inefficace

## Version const

```cpp
template<typename T>
typename T::const_iterator easyfind(T const &container, int value)
```

Permet d'utiliser `easyfind` sur des containers const, retournant un `const_iterator` (lecture seule).

## Points clés

1. **Généricité** : Fonctionne avec vector, list, deque et tout container séquentiel d'entiers

2. **typename obligatoire** : Pour les types dépendants

3. **std::find** : Réutilisation d'un algorithme STL existant

4. **Exception** : Comportement cohérent avec la philosophie C++ (similaire à `std::out_of_range`)

5. **Itérateurs** : Interface uniforme pour tous les containers
