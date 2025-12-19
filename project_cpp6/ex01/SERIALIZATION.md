# Exercice 01 : Sérialisation avec reinterpret_cast

## Concept clé : reinterpret_cast et manipulation de pointeurs

---

## 1. Qu'est-ce que la sérialisation ?

La **sérialisation** est le processus de conversion d'une structure de données en un format 
qui peut être stocké ou transmis, puis reconstruit plus tard.

Dans cet exercice, on "sérialise" un pointeur en le convertissant en entier.

```
┌─────────────┐    serialize()    ┌─────────────────┐
│  Data*      │ ─────────────────>│   uintptr_t     │
│ 0x7fff5fbff│                    │  140734799804000│
└─────────────┘                   └─────────────────┘
                                          │
                  deserialize()           │
┌─────────────┐ <─────────────────────────┘
│  Data*      │
│ 0x7fff5fbff│
└─────────────┘
```

---

## 2. uintptr_t

### Définition :
```cpp
#include <stdint.h>  // ou <cstdint> en C++11

uintptr_t raw;  // Entier non-signé capable de stocker un pointeur
```

### Caractéristiques :
- Type entier **garanti** de pouvoir stocker une adresse mémoire
- Taille dépend de l'architecture (32 bits → 4 bytes, 64 bits → 8 bytes)
- Défini dans `<stdint.h>` (C) ou `<cstdint>` (C++)

### Pourquoi pas `unsigned long` ?
- `unsigned long` n'est **pas garanti** d'avoir la même taille qu'un pointeur
- Sur Windows 64 bits : `long` = 4 bytes, pointeur = 8 bytes !
- `uintptr_t` est **portable**

---

## 3. reinterpret_cast

### Syntaxe :
```cpp
uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);
Data* ptr = reinterpret_cast<Data*>(raw);
```

### Définition :
`reinterpret_cast` réinterprète le **pattern de bits** d'une valeur comme un autre type.

### Ce que ça fait :
```
Pointeur:     0x7fff5fbff8a0
              ↓ (même bits, interprétation différente)
uintptr_t:    140734799804576
```

### Différence avec les autres casts :

| Cast | Usage | Sécurité |
|------|-------|----------|
| `static_cast` | Conversions numériques, up/downcasting | Vérifié à la compilation |
| `dynamic_cast` | Downcasting polymorphique | Vérifié à l'exécution |
| `const_cast` | Ajouter/retirer const | Dangereux si mal utilisé |
| `reinterpret_cast` | Réinterpréter les bits | Le plus dangereux ! |

---

## 4. Classe Serializer

### Structure :
```cpp
class Serializer
{
    private:
        // Non instanciable
        Serializer();
        Serializer(const Serializer& other);
        Serializer& operator=(const Serializer& other);
        ~Serializer();

    public:
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);
};
```

### Implémentation :
```cpp
uintptr_t Serializer::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data*>(raw);
}
```

---

## 5. Structure Data

Le sujet demande une structure **non-vide** :

```cpp
struct Data
{
    int         id;
    std::string name;
    double      value;
};
```

### Pourquoi non-vide ?
Pour prouver que les données sont bien accessibles après désérialisation.

---

## 6. Test de validité

```cpp
Data original;
original.id = 42;
original.name = "Test";

// Sérialiser
uintptr_t raw = Serializer::serialize(&original);

// Désérialiser
Data* result = Serializer::deserialize(raw);

// Vérifier
if (result == &original)
    std::cout << "SUCCESS!" << std::endl;

// Accéder aux données
std::cout << result->id << std::endl;  // 42
std::cout << result->name << std::endl;  // Test
```

---

## 7. Pourquoi ça fonctionne ?

### Mémoire :
```
Adresse 0x7fff5fbff8a0:
┌──────────────────────────────────┐
│ Data object                      │
│  ├─ id: 42                       │
│  ├─ name: "Test"                 │
│  └─ value: 3.14                  │
└──────────────────────────────────┘
```

### Processus :
1. `serialize()` prend l'adresse `0x7fff5fbff8a0`
2. Convertit en entier `140734799804576`
3. `deserialize()` prend l'entier `140734799804576`
4. Convertit en pointeur `0x7fff5fbff8a0`
5. **L'objet n'a pas bougé** → on peut y accéder !

---

## 8. Dangers de reinterpret_cast

### ⚠️ Comportement indéfini si :
```cpp
// Utiliser une adresse invalide
uintptr_t fake = 12345;
Data* bad = Serializer::deserialize(fake);
bad->id = 42;  // 💥 CRASH ou corruption mémoire !
```

### ⚠️ Problèmes potentiels :
- Pointeur vers objet détruit
- Alignement mémoire incorrect
- Type incorrect (cast vers mauvais type)

---

## 9. Cas d'utilisation réels

| Usage | Exemple |
|-------|---------|
| Stockage d'adresses | Sauvegarder des pointeurs dans un fichier |
| Communication | Transmettre des adresses via réseau |
| Interfaçage C | Passer des pointeurs via `void*` |
| Callbacks | Stocker des contextes utilisateur |

---

## 10. Questions d'évaluation possibles

1. **Qu'est-ce que reinterpret_cast ?**
   > Un cast qui réinterprète le pattern de bits d'une valeur comme un autre type, sans modification.

2. **Pourquoi utiliser uintptr_t plutôt que unsigned long ?**
   > `uintptr_t` est garanti d'avoir la même taille qu'un pointeur, ce qui n'est pas le cas de `unsigned long` sur toutes les plateformes.

3. **La sérialisation modifie-t-elle les données ?**
   > Non, on ne fait que convertir l'adresse en entier et vice-versa. L'objet reste intact en mémoire.

4. **Que se passe-t-il si on désérialise une valeur invalide ?**
   > Comportement indéfini. On obtient un pointeur invalide qui causera un crash ou une corruption si on l'utilise.

5. **Pourquoi le Serializer n'est-il pas instanciable ?**
   > Parce qu'il ne stocke aucune donnée. Les méthodes sont statiques et n'ont pas besoin d'instance.

6. **Quelle est la différence entre static_cast et reinterpret_cast ?**
   > `static_cast` effectue des conversions avec vérification à la compilation. `reinterpret_cast` réinterprète les bits sans vérification.

---

## 11. Les 4 casts C++

```cpp
// 1. static_cast - Conversions "normales"
double d = 3.14;
int i = static_cast<int>(d);  // 3

// 2. dynamic_cast - Downcasting sûr (polymorphisme)
Base* b = new Derived();
Derived* d = dynamic_cast<Derived*>(b);  // OK ou nullptr

// 3. const_cast - Retirer/ajouter const
const int* pc = &i;
int* p = const_cast<int*>(pc);  // Retirer const

// 4. reinterpret_cast - Réinterpréter les bits
Data* ptr = new Data;
uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);
```

---

## Résumé

| Concept | Description |
|---------|-------------|
| `uintptr_t` | Entier capable de stocker un pointeur |
| `reinterpret_cast` | Réinterprète les bits comme un autre type |
| Sérialisation | Convertir une structure en format stockable |
| Désérialisation | Reconstruire la structure depuis le format stocké |
| Pointeur → int → Pointeur | Le pointeur original est retrouvé |
