# MutantStack - Ex02

## Concept : Héritage de Container STL

Cet exercice montre comment **étendre un container STL** en héritant de lui pour ajouter des fonctionnalités manquantes.

## Le problème avec std::stack

`std::stack` est un **adaptateur de container** : il encapsule un autre container (par défaut `std::deque`) et n'expose que les opérations LIFO (Last In, First Out).

```cpp
std::stack<int> s;
s.push(1);
s.push(2);
s.top();   // ✅ Accès au sommet
s.pop();   // ✅ Supprimer le sommet

// ❌ Pas d'itérateurs !
// s.begin();  // N'existe pas
// s.end();    // N'existe pas
```

## La solution : MutantStack

```cpp
template<typename T>
class MutantStack : public std::stack<T>
{
public:
    // Exposer les itérateurs du container sous-jacent
    typedef typename std::stack<T>::container_type::iterator iterator;
    
    iterator begin() { return this->c.begin(); }
    iterator end()   { return this->c.end(); }
};
```

## Le secret : le membre protégé `c`

`std::stack` a un membre **protégé** appelé `c` qui est le container sous-jacent :

```cpp
// Dans la définition de std::stack (simplifié)
template<typename T, typename Container = std::deque<T>>
class stack
{
protected:
    Container c;  // Le container sous-jacent (accessible aux classes dérivées)
    
public:
    void push(const T& val) { c.push_back(val); }
    void pop()              { c.pop_back(); }
    T& top()                { return c.back(); }
    // ...
};
```

En héritant de `std::stack`, on peut accéder à `c` et exposer ses itérateurs !

## Types définis

```cpp
// container_type = le type du container sous-jacent (std::deque<T> par défaut)
typedef typename std::stack<T>::container_type::iterator iterator;
typedef typename std::stack<T>::container_type::const_iterator const_iterator;
typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;
```

### Pourquoi `typename` ?

`std::stack<T>::container_type::iterator` est un **type dépendant** du paramètre template `T`. Le compilateur a besoin de `typename` pour savoir que c'est un type et non une variable.

## Implémentation des itérateurs

```cpp
template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin()
{
    return this->c.begin();
}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::end()
{
    return this->c.end();
}
```

- `this->c` accède au container protégé hérité de `std::stack`
- On délègue simplement à `c.begin()` et `c.end()`

## Héritage complet

Grâce à l'héritage public, MutantStack hérite automatiquement de toutes les méthodes de std::stack :

| Méthode | Description |
|---------|-------------|
| `push(val)` | Ajouter un élément au sommet |
| `pop()` | Supprimer le sommet |
| `top()` | Accéder au sommet |
| `size()` | Nombre d'éléments |
| `empty()` | Vérifier si vide |

**+ Les nouvelles méthodes** :
| Méthode | Description |
|---------|-------------|
| `begin()` | Itérateur vers le premier élément |
| `end()` | Itérateur après le dernier |
| `rbegin()` | Itérateur inverse (fin → début) |
| `rend()` | Fin de l'itérateur inverse |

## Comparaison avec std::list

Le sujet demande de comparer avec `std::list`. Les deux doivent produire la même sortie :

```cpp
// MutantStack
mstack.push(5);
std::cout << mstack.top();  // Accès au dernier
mstack.pop();               // Supprimer le dernier

// std::list (équivalent)
lst.push_back(5);
std::cout << lst.back();    // Accès au dernier
lst.pop_back();             // Supprimer le dernier
```

## Convertibilité avec std::stack

```cpp
MutantStack<int> mstack;
mstack.push(1);
mstack.push(2);

std::stack<int> s(mstack);  // ✅ Conversion possible grâce à l'héritage
```

## Pattern d'extension STL

Ce pattern est utile pour :
1. Ajouter des fonctionnalités à un container existant
2. Personnaliser le comportement
3. Exposer des membres normalement cachés

⚠️ **Attention** : Les containers STL n'ont pas de destructeur virtuel. L'héritage est donc risqué pour le polymorphisme. Ici c'est acceptable car on n'utilise pas de pointeurs vers la classe de base.

## Points clés

1. **Héritage public** : Hérite de toutes les méthodes de std::stack

2. **Membre protégé `c`** : Accessible car protégé, pas privé

3. **`typename`** : Obligatoire pour les types dépendants

4. **4 types d'itérateurs** : iterator, const_iterator, reverse_iterator, const_reverse_iterator

5. **Compatibilité** : Peut être converti en std::stack classique
