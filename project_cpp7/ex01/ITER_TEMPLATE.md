# Template iter - Ex01

## Concept : Fonction Template avec Callback

L'exercice `iter` introduit un concept plus avancé : une fonction template qui prend une autre fonction en paramètre pour l'appliquer sur chaque élément d'un tableau.

## La fonction iter

```cpp
template<typename T, typename F>
void iter(T *array, size_t const length, F func)
{
    for (size_t i = 0; i < length; i++)
        func(array[i]);
}
```

### Paramètres

1. **`T *array`** : Pointeur vers le premier élément du tableau
2. **`size_t const length`** : Taille du tableau (const car non modifiée)
3. **`F func`** : Fonction callback à appliquer sur chaque élément

### Double paramètre de type

- `T` : Le type des éléments du tableau
- `F` : Le type de la fonction (peut être un pointeur de fonction, un foncteur, etc.)

## Gestion const / non-const

Le sujet demande de supporter les tableaux const ET non-const. Solution : deux surcharges.

```cpp
// Version non-const : permet de modifier les éléments
template<typename T, typename F>
void iter(T *array, size_t const length, F func);

// Version const : lecture seule
template<typename T, typename F>
void iter(T const *array, size_t const length, F func);
```

## Exemples de fonctions callback

### Fonction template (lecture)
```cpp
template<typename T>
void print(T const &elem)
{
    std::cout << elem << " ";
}
```

### Fonction template (modification)
```cpp
template<typename T>
void increment(T &elem)
{
    elem++;
}
```

### Fonction classique
```cpp
void toUpper(char &c)
{
    if (c >= 'a' && c <= 'z')
        c = c - 32;
}
```

## Utilisation

```cpp
int arr[] = {1, 2, 3, 4, 5};

// Avec template instancié explicitement
::iter(arr, 5, print<int>);

// Le compilateur déduit les types T et F automatiquement
::iter(arr, 5, increment<int>);
```

## Points clés

1. **Fonction template instanciée** : Quand on passe `print<int>`, on instancie explicitement le template pour le type `int`.

2. **Flexibilité du paramètre F** : Le type `F` accepte :
   - Pointeurs de fonction classiques
   - Templates de fonctions instanciés
   - Foncteurs (objets avec `operator()`)

3. **Passage par valeur de F** : La fonction est passée par valeur car les pointeurs de fonction sont légers.

4. **Références dans les callbacks** :
   - `T const &` pour lecture seule
   - `T &` pour modification

## Pattern couramment utilisé

Ce pattern est similaire à `std::for_each` de la STL :
```cpp
std::for_each(begin, end, function);
```

C'est un exemple de **programmation fonctionnelle** en C++, où les fonctions sont des "citoyens de première classe" (peuvent être passées en paramètres).
