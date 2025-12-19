# Exercice 00 : Conversion de Types Scalaires

## Concepts clés : Static Class, Type Detection, Type Casting

---

## 1. Classe non-instanciable (Static Class)

### Pourquoi ?
La classe `ScalarConverter` n'a **pas besoin de stocker de données**. Elle ne fait que convertir.

### Comment empêcher l'instanciation ?
```cpp
class ScalarConverter
{
    private:
        // Tous les constructeurs en privé !
        ScalarConverter();
        ScalarConverter(const ScalarConverter& other);
        ScalarConverter& operator=(const ScalarConverter& other);
        ~ScalarConverter();

    public:
        // Seule méthode publique : statique
        static void convert(const std::string& literal);
};
```

### Tentative d'instanciation :
```cpp
ScalarConverter sc;                    // ❌ Erreur : constructeur privé
ScalarConverter* sc = new ScalarConverter(); // ❌ Erreur : constructeur privé
ScalarConverter::convert("42");        // ✅ OK : méthode statique
```

---

## 2. Méthode Statique

```cpp
static void convert(const std::string& literal);
```

### Caractéristiques :
- Pas besoin d'instance pour l'appeler
- N'a pas accès à `this`
- Peut seulement accéder aux membres statiques
- Appelée avec `ClassName::method()`

---

## 3. Les Types Scalaires en C++

| Type | Taille | Plage |
|------|--------|-------|
| `char` | 1 byte | -128 à 127 (ou 0 à 255) |
| `int` | 4 bytes | -2,147,483,648 à 2,147,483,647 |
| `float` | 4 bytes | ±3.4E38 (7 chiffres significatifs) |
| `double` | 8 bytes | ±1.7E308 (15 chiffres significatifs) |

---

## 4. Détection du Type du Littéral

### Algorithme :
```
Entrée: "42.0f"
    │
    ├─ Est-ce un pseudo-littéral (nan, inf) ? → Non
    ├─ Est-ce un char ('a' ou caractère seul) ? → Non
    ├─ Est-ce un int (chiffres seulement) ? → Non
    ├─ Est-ce un float (chiffres.chiffresf) ? → Oui !
    └─ Est-ce un double (chiffres.chiffres) ? → -
    
    Résultat: FLOAT
```

### Patterns reconnus :
| Type | Exemples |
|------|----------|
| Char | `'a'`, `c`, `*` (caractère unique non-chiffre) |
| Int | `0`, `-42`, `2147483647` |
| Float | `0.0f`, `-4.2f`, `42.0f` |
| Double | `0.0`, `-4.2`, `42.0` |
| Pseudo | `nan`, `nanf`, `+inf`, `-inf`, `+inff`, `-inff` |

---

## 5. Conversions Explicites (Casts)

### static_cast<> (C++ style) :
```cpp
double d = 42.5;
int i = static_cast<int>(d);      // i = 42 (troncature)
char c = static_cast<char>(i);    // c = '*' (ASCII 42)
float f = static_cast<float>(d);  // f = 42.5f
```

### Équivalent C-style (à éviter) :
```cpp
int i = (int)d;  // Fonctionne mais moins sûr
```

### Pourquoi static_cast ?
- Vérifié à la compilation
- Plus explicite et lisible
- Erreur si conversion impossible

---

## 6. Gestion des Limites et Erreurs

### Vérification des bornes :
```cpp
#include <limits>

// Vérifier si un double peut être converti en int
if (value < static_cast<double>(std::numeric_limits<int>::min()) ||
    value > static_cast<double>(std::numeric_limits<int>::max()))
{
    std::cout << "impossible" << std::endl;
}
```

### Valeurs spéciales :
```cpp
#include <cmath>

std::isnan(value)  // true si NaN (Not a Number)
std::isinf(value)  // true si infini (+inf ou -inf)
```

---

## 7. Pseudo-littéraux

### Float :
- `nanf` : Not a Number (float)
- `+inff` / `-inff` : Infini positif/négatif (float)

### Double :
- `nan` : Not a Number (double)
- `+inf` / `-inf` : Infini positif/négatif (double)

### Génération :
```cpp
#include <limits>

double nan_val = std::numeric_limits<double>::quiet_NaN();
double inf_val = std::numeric_limits<double>::infinity();
double neg_inf = -std::numeric_limits<double>::infinity();
```

---

## 8. Affichage Formaté

```cpp
#include <iomanip>

// Toujours afficher au moins une décimale
std::cout << std::fixed << std::setprecision(1);

std::cout << 42.0f << "f" << std::endl;  // "42.0f"
std::cout << 42.0 << std::endl;          // "42.0"
```

---

## 9. Flux de Conversion

```
┌──────────────┐
│ Input: "42"  │
└──────┬───────┘
       │
       ▼
┌──────────────────┐
│ detectType()     │ → INT
└──────┬───────────┘
       │
       ▼
┌──────────────────┐
│ convertFromInt() │
│ value = 42       │
└──────┬───────────┘
       │
       ├────────────────────────────────────┐
       │                                    │
       ▼                                    ▼
┌──────────────┐                    ┌──────────────┐
│ displayChar()│                    │ displayInt() │
│ 42 → '*'     │                    │ 42           │
└──────────────┘                    └──────────────┘
       │                                    │
       ▼                                    ▼
┌──────────────┐                    ┌──────────────┐
│displayFloat()│                    │displayDouble│
│ 42.0f        │                    │ 42.0         │
└──────────────┘                    └──────────────┘
```

---

## 10. Cas Particuliers

### Caractères non-affichables :
```cpp
// ASCII 0-31 et 127 sont non-affichables
if (!std::isprint(static_cast<int>(value)))
    std::cout << "Non displayable" << std::endl;
```

### Overflow sur int :
```cpp
// "999999999999" dépasse INT_MAX
// → char: impossible, int: impossible, float/double: OK
```

### Caractère avec guillemets :
```cpp
// './convert '\''a'\''' ou ./convert "'a'"
// → Reconnu comme char 'a'
```

---

## 11. Questions d'évaluation possibles

1. **Pourquoi la classe n'est-elle pas instanciable ?**
   > Elle ne stocke aucune donnée. La méthode convert est statique et n'a pas besoin d'instance.

2. **Qu'est-ce qu'une méthode statique ?**
   > Une méthode qui appartient à la classe et non à une instance. Appelée avec `Class::method()`.

3. **Qu'est-ce que static_cast ?**
   > Un opérateur de conversion C++ vérifié à la compilation, plus sûr que le cast C-style.

4. **Comment gérer NaN et Infinity ?**
   > Avec `std::isnan()` et `std::isinf()` de `<cmath>`, et `std::numeric_limits` pour les générer.

5. **Pourquoi char 42 affiche '\*' ?**
   > 42 est le code ASCII du caractère '*'.

6. **Que se passe-t-il si la conversion n'est pas possible ?**
   > On affiche "impossible" (overflow, NaN vers int, etc.).

---

## 12. Fonctions Autorisées

| Fonction | Header | Usage |
|----------|--------|-------|
| `std::atoi()` | `<cstdlib>` | String → int |
| `std::atof()` | `<cstdlib>` | String → double |
| `std::strtof()` | `<cstdlib>` | String → float |
| `std::strtod()` | `<cstdlib>` | String → double |
| `std::isnan()` | `<cmath>` | Teste si NaN |
| `std::isinf()` | `<cmath>` | Teste si infini |
| `std::isprint()` | `<cctype>` | Teste si affichable |

---

## Résumé

| Concept | Description |
|---------|-------------|
| Static class | Constructeurs privés + méthodes statiques |
| static_cast | Conversion de type C++ sûre |
| Type detection | Analyser le format du littéral |
| numeric_limits | Bornes min/max des types |
| Pseudo-literals | nan, inf (valeurs spéciales IEEE 754) |
