# Templates de Fonctions - Ex00

## Concept : Les Templates de Fonctions

Les **templates** (modèles) en C++ permettent d'écrire du code générique qui fonctionne avec n'importe quel type de données. Au lieu d'écrire plusieurs fonctions pour différents types (int, double, string...), on écrit une seule fonction template.

## Syntaxe de base

```cpp
template<typename T>
T maFonction(T param) {
    // code utilisant T comme type
}
```

- `template<typename T>` : déclare un paramètre de type générique `T`
- `T` peut être remplacé par n'importe quel type lors de l'appel

## Fonctions implémentées

### 1. swap
```cpp
template<typename T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}
```
- **But** : Échanger les valeurs de deux variables
- **Passage par référence** : Obligatoire pour modifier les originaux
- **Pas de retour** : La modification se fait in-place

### 2. min
```cpp
template<typename T>
T const &min(T const &a, T const &b)
{
    return (a < b) ? a : b;
}
```
- **But** : Retourner le plus petit des deux
- **Si égaux** : Retourne le second (b)
- **Retour par référence const** : Évite une copie inutile

### 3. max
```cpp
template<typename T>
T const &max(T const &a, T const &b)
{
    return (a > b) ? a : b;
}
```
- **But** : Retourner le plus grand des deux
- **Si égaux** : Retourne le second (b)

## Points clés

1. **Définition dans le header** : Les templates doivent être définis dans les fichiers `.hpp`, pas dans les `.cpp`, car le compilateur doit voir l'implémentation pour générer le code spécifique à chaque type.

2. **Opérateur `::` global** : L'utilisation de `::swap()` appelle notre fonction dans l'espace de noms global, évitant tout conflit avec `std::swap`.

3. **Instanciation automatique** : Le compilateur génère automatiquement une version de la fonction pour chaque type utilisé :
   - `::min(a, b)` avec des `int` → génère `min<int>`
   - `::min(c, d)` avec des `string` → génère `min<std::string>`

4. **Contraintes implicites** : Le type `T` doit supporter les opérateurs `<` et `>` pour que `min` et `max` fonctionnent.

## Avantages des templates

- ✅ Code réutilisable
- ✅ Type-safe (vérification à la compilation)
- ✅ Pas de duplication de code
- ✅ Performance optimale (pas d'overhead runtime)
