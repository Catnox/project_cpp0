# RPN (Reverse Polish Notation) - Ex01

## Concept : Notation Polonaise Inverse et std::stack

La **Notation Polonaise Inverse** (RPN) est une notation mathématique où les opérateurs suivent leurs opérandes.

## Exemples de conversion

| Notation infixe | Notation RPN |
|-----------------|--------------|
| `3 + 4` | `3 4 +` |
| `(1 + 2) * 3` | `1 2 + 3 *` |
| `8 * 9 - 9 - 9 - 9 - 4 + 1` | `8 9 * 9 - 9 - 9 - 4 - 1 +` |

## Pourquoi std::stack ?

```cpp
std::stack<int> _stack;
```

La pile (stack) est **parfaite** pour RPN car :
1. On empile les opérandes
2. Quand on rencontre un opérateur, on dépile 2 opérandes
3. On effectue l'opération
4. On empile le résultat

## Algorithme

```cpp
int RPN::calculate(std::string const &expression)
{
    for (chaque caractère c dans expression)
    {
        if (c est un espace)
            continuer;
            
        if (c est un chiffre 0-9)
            _stack.push(c - '0');
            
        else if (c est un opérateur + - * /)
        {
            if (_stack.size() < 2)
                throw exception;  // Pas assez d'opérandes
                
            int b = _stack.top(); _stack.pop();
            int a = _stack.top(); _stack.pop();
            
            int result = appliquer_operation(a, b, c);
            _stack.push(result);
        }
        else
            throw exception;  // Caractère invalide
    }
    
    if (_stack.size() != 1)
        throw exception;  // Expression mal formée
        
    return _stack.top();
}
```

## Exemple pas à pas

Expression : `8 9 * 9 - 9 - 9 - 4 - 1 +`

| Étape | Caractère | Action | Pile |
|-------|-----------|--------|------|
| 1 | `8` | push(8) | [8] |
| 2 | `9` | push(9) | [8, 9] |
| 3 | `*` | 8 * 9 = 72 | [72] |
| 4 | `9` | push(9) | [72, 9] |
| 5 | `-` | 72 - 9 = 63 | [63] |
| 6 | `9` | push(9) | [63, 9] |
| 7 | `-` | 63 - 9 = 54 | [54] |
| 8 | `9` | push(9) | [54, 9] |
| 9 | `-` | 54 - 9 = 45 | [45] |
| 10 | `4` | push(4) | [45, 4] |
| 11 | `-` | 45 - 4 = 41 | [41] |
| 12 | `1` | push(1) | [41, 1] |
| 13 | `+` | 41 + 1 = 42 | [42] |

**Résultat : 42**

## Contraintes du sujet

1. **Chiffres < 10** : Chaque opérande est un seul chiffre (0-9)
2. **Opérateurs supportés** : `+`, `-`, `*`, `/`
3. **Pas de parenthèses** : Elles sont inutiles en RPN
4. **Pas de décimaux** : Calculs sur entiers

## Gestion des erreurs

```cpp
// Pas assez d'opérandes
if (_stack.size() < 2)
    throw InvalidExpressionException();

// Division par zéro
if (op == '/' && b == 0)
    throw DivisionByZeroException();

// Caractère invalide (parenthèses, lettres, etc.)
if (!isdigit(c) && !isOperator(c))
    throw InvalidExpressionException();

// Expression incomplète
if (_stack.size() != 1)
    throw InvalidExpressionException();
```

## Avantages de RPN

| Avantage | Description |
|----------|-------------|
| Pas de parenthèses | L'ordre des opérations est explicite |
| Pas de priorité | Chaque opération est effectuée immédiatement |
| Simple à parser | Un seul passage de gauche à droite |
| Efficace | Utilisé dans les calculatrices HP |

## Container utilisé

✅ **std::stack** - Ne peut plus être utilisé dans les exercices suivants

(Note : std::map déjà utilisé en ex00)
