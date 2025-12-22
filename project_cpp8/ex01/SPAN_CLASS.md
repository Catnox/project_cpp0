# Span - Ex01

## Concept : Classe avec Container STL interne

Cet exercice combine la création d'une classe personnalisée avec l'utilisation d'un container STL (`std::vector`) pour le stockage interne.

## Architecture de la classe Span

```cpp
class Span
{
private:
    unsigned int        _maxSize;    // Capacité maximale
    std::vector<int>    _numbers;    // Stockage des nombres

public:
    void addNumber(int number);      // Ajouter un nombre
    int shortestSpan() const;        // Plus petit écart
    int longestSpan() const;         // Plus grand écart
    
    template<typename InputIterator>
    void addRange(InputIterator begin, InputIterator end);  // Ajout en masse
};
```

## Algorithmes STL utilisés

### std::sort
```cpp
std::vector<int> sorted = _numbers;
std::sort(sorted.begin(), sorted.end());
```
- Trie le vector en place
- Complexité : O(n log n)
- Utilisé pour `shortestSpan()` : après tri, les plus proches sont adjacents

### std::min_element / std::max_element
```cpp
int min = *std::min_element(_numbers.begin(), _numbers.end());
int max = *std::max_element(_numbers.begin(), _numbers.end());
```
- Retourne un itérateur vers le min/max
- Complexité : O(n)
- `longestSpan = max - min`

## Calcul des spans

### Shortest Span (plus petit écart)
```cpp
int Span::shortestSpan() const
{
    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());  // Tri

    int minSpan = INT_MAX;
    for (size_t i = 1; i < sorted.size(); i++)
    {
        int span = sorted[i] - sorted[i - 1];  // Différence entre adjacents
        if (span < minSpan)
            minSpan = span;
    }
    return minSpan;
}
```

**Pourquoi trier ?**
- Après tri, les nombres les plus proches sont côte à côte
- On n'a qu'à comparer les paires adjacentes : O(n) au lieu de O(n²)

### Longest Span (plus grand écart)
```cpp
int Span::longestSpan() const
{
    int min = *std::min_element(_numbers.begin(), _numbers.end());
    int max = *std::max_element(_numbers.begin(), _numbers.end());
    return max - min;
}
```

**Simple et efficace** : Le plus grand écart est toujours `max - min`.

## Méthode template addRange

```cpp
template<typename InputIterator>
void addRange(InputIterator begin, InputIterator end)
{
    size_t distance = std::distance(begin, end);
    if (_numbers.size() + distance > _maxSize)
        throw SpanFullException();
    _numbers.insert(_numbers.end(), begin, end);
}
```

### Pourquoi dans le header ?

C'est un template, donc l'implémentation doit être visible au moment de la compilation.

### std::distance
```cpp
size_t count = std::distance(begin, end);
```
- Calcule le nombre d'éléments entre deux itérateurs
- Fonctionne avec tous les types d'itérateurs

### vector::insert avec range
```cpp
_numbers.insert(_numbers.end(), begin, end);
```
- Insère tous les éléments de `[begin, end)` à la fin du vector
- Plus efficace que des `push_back` répétés

## Utilisation de addRange

```cpp
// Avec un vector
std::vector<int> vec;
vec.push_back(1);
vec.push_back(2);
sp.addRange(vec.begin(), vec.end());

// Avec une list
std::list<int> lst;
lst.push_back(10);
lst.push_back(20);
sp.addRange(lst.begin(), lst.end());

// Avec un tableau C
int arr[] = {1, 2, 3, 4, 5};
sp.addRange(arr, arr + 5);
```

## Gestion des exceptions

| Exception | Condition |
|-----------|-----------|
| `SpanFullException` | Tentative d'ajout quand size >= maxSize |
| `NoSpanException` | shortestSpan/longestSpan avec < 2 éléments |

## Performances

| Opération | Complexité |
|-----------|------------|
| `addNumber` | O(1) amorti |
| `addRange` | O(n) |
| `shortestSpan` | O(n log n) (tri) |
| `longestSpan` | O(n) |

## Pourquoi std::vector ?

| Avantage | Description |
|----------|-------------|
| Accès direct | O(1) pour l'accès par index |
| Tri efficace | `std::sort` optimisé pour les vecteurs |
| insert range | Méthode native pour ajouter plusieurs éléments |
| Copie simple | L'opérateur `=` fait une deep copy automatiquement |

## Points clés

1. **Encapsulation** : Le vector est privé, l'interface publique est simple

2. **Algorithmes STL** : Réutilisation de `sort`, `min_element`, `max_element`, `distance`, `insert`

3. **Template dans classe non-template** : `addRange` est template même si `Span` ne l'est pas

4. **Scalabilité** : Testé avec 10,000+ nombres grâce à des algorithmes efficaces
