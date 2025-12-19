# Interfaces et Design Pattern - Exercice 03

## 🎯 Objectif de l'exercice

Cet exercice est le plus complet du module CPP04. Il combine :
- **Interfaces** (`ICharacter`, `IMateriaSource`)
- **Classes abstraites** (`AMateria`)
- **Polymorphisme**
- **Deep copy** avec le pattern **Clone**
- **Gestion mémoire** avancée

---

## 📚 Qu'est-ce qu'une Interface ?

### Définition

Une **interface** en C++ est une classe abstraite **pure** qui :
- Ne contient **QUE** des méthodes virtuelles pures
- N'a **AUCUN** attribut (pas de données membres)
- N'a **AUCUNE** implémentation
- Définit un **contrat** que les classes dérivées doivent respecter

### Convention de nommage

Le préfixe `I` indique une interface :
- `ICharacter` = Interface Character
- `IMateriaSource` = Interface MateriaSource

---

## 🔍 Les Interfaces de l'exercice

### ICharacter

```cpp
class ICharacter
{
public:
    virtual ~ICharacter() {}
    virtual std::string const & getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};
```

**Contrat défini :**
- Tout personnage a un nom (`getName`)
- Tout personnage peut équiper une Materia (`equip`)
- Tout personnage peut déséquiper une Materia (`unequip`)
- Tout personnage peut utiliser une Materia (`use`)

### IMateriaSource

```cpp
class IMateriaSource
{
public:
    virtual ~IMateriaSource() {}
    virtual void learnMateria(AMateria*) = 0;
    virtual AMateria* createMateria(std::string const & type) = 0;
};
```

**Contrat défini :**
- Toute source peut apprendre une Materia (`learnMateria`)
- Toute source peut créer une Materia par son type (`createMateria`)

---

## ⚖️ Interface vs Classe Abstraite

| Aspect | Interface (`ICharacter`) | Classe Abstraite (`AMateria`) |
|--------|--------------------------|-------------------------------|
| Préfixe convention | `I` | `A` |
| Attributs | ❌ Aucun | ✅ Peut en avoir (`_type`) |
| Méthodes implémentées | ❌ Aucune | ✅ Peut en avoir (`getType()`) |
| Méthodes virtuelles pures | ✅ Toutes | ✅ Au moins une (`clone()`) |
| Constructeurs | ❌ Non (ou vide) | ✅ Oui |
| But | Définir un contrat pur | Base commune avec code partagé |

### Exemple concret

```cpp
// INTERFACE - Aucun code, juste des déclarations
class ICharacter
{
public:
    virtual ~ICharacter() {}
    virtual std::string const & getName() const = 0;  // = 0 partout
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};

// CLASSE ABSTRAITE - Du code + au moins une méthode pure
class AMateria
{
protected:
    std::string _type;  // Attribut !

public:
    AMateria(std::string const & type) : _type(type) {}  // Constructeur avec code !
    
    std::string const & getType() const { return _type; }  // Méthode implémentée !
    
    virtual AMateria* clone() const = 0;  // Méthode pure
    virtual void use(ICharacter& target);  // Méthode virtuelle (pas pure)
};
```

---

## 🏗️ Architecture complète

```
┌─────────────────────────────────────────────────────────────────────┐
│                           INTERFACES                                 │
├─────────────────────────────────────────────────────────────────────┤
│                                                                      │
│  ┌─────────────────┐              ┌─────────────────┐               │
│  │   ICharacter    │              │ IMateriaSource  │               │
│  │ (interface)     │              │ (interface)     │               │
│  │                 │              │                 │               │
│  │ + getName()     │              │ + learnMateria()│               │
│  │ + equip()       │              │ + createMateria()│              │
│  │ + unequip()     │              │                 │               │
│  │ + use()         │              │                 │               │
│  └────────┬────────┘              └────────┬────────┘               │
│           │                                │                         │
│           │ implémente                     │ implémente              │
│           ▼                                ▼                         │
│  ┌─────────────────┐              ┌─────────────────┐               │
│  │   Character     │              │  MateriaSource  │               │
│  │ (concrète)      │              │  (concrète)     │               │
│  │                 │              │                 │               │
│  │ - _name         │              │ - _templates[4] │               │
│  │ - _inventory[4] │              │                 │               │
│  └─────────────────┘              └─────────────────┘               │
│                                                                      │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│                      CLASSE ABSTRAITE                                │
├─────────────────────────────────────────────────────────────────────┤
│                                                                      │
│                    ┌─────────────────┐                              │
│                    │    AMateria     │                              │
│                    │ (abstraite)     │                              │
│                    │                 │                              │
│                    │ # _type         │                              │
│                    │ + getType()     │                              │
│                    │ + clone() = 0   │  ← Méthode pure              │
│                    │ + use()         │                              │
│                    └────────┬────────┘                              │
│                             │                                        │
│              ┌──────────────┴──────────────┐                        │
│              │                             │                         │
│              ▼                             ▼                         │
│     ┌─────────────────┐           ┌─────────────────┐               │
│     │      Ice        │           │      Cure       │               │
│     │ (concrète)      │           │ (concrète)      │               │
│     │                 │           │                 │               │
│     │ + clone()       │           │ + clone()       │               │
│     │ + use()         │           │ + use()         │               │
│     │ "ice bolt"      │           │ "heals wounds"  │               │
│     └─────────────────┘           └─────────────────┘               │
│                                                                      │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 🧬 Le Pattern Clone

### Problème

Comment copier un objet quand on a seulement un pointeur vers la classe de base ?

```cpp
AMateria* original = new Ice();
AMateria* copy = new ???(*original);  // On ne sait pas que c'est Ice !
```

### Solution : La méthode `clone()`

```cpp
// Dans AMateria (classe abstraite)
virtual AMateria* clone() const = 0;

// Dans Ice
AMateria* Ice::clone() const
{
    return new Ice(*this);  // Crée une copie de soi-même
}

// Dans Cure
AMateria* Cure::clone() const
{
    return new Cure(*this);  // Crée une copie de soi-même
}
```

### Utilisation

```cpp
AMateria* original = new Ice();        // Type réel : Ice
AMateria* copy = original->clone();    // Crée un nouvel Ice !

// Le polymorphisme appelle Ice::clone() même avec un pointeur AMateria*
```

### Visualisation

```
original (AMateria*)           copy (AMateria*)
        │                              │
        ▼                              ▼
   ┌─────────┐    clone()        ┌─────────┐
   │   Ice   │ ──────────────►   │   Ice   │
   │ "ice"   │                   │ "ice"   │
   └─────────┘                   └─────────┘
                                 Nouvel objet !
```

---

## 📦 Gestion de l'inventaire (Character)

### Structure

```cpp
class Character : public ICharacter
{
private:
    std::string _name;
    AMateria* _inventory[4];  // 4 slots max
};
```

### equip() - Équiper une Materia

```cpp
void Character::equip(AMateria* m)
{
    if (!m)
        return;
    for (int i = 0; i < 4; i++)
    {
        if (!_inventory[i])  // Trouve le premier slot vide
        {
            _inventory[i] = m;
            return;
        }
    }
    // Si inventaire plein, ne fait rien
}
```

### unequip() - Déséquiper une Materia

```cpp
void Character::unequip(int idx)
{
    if (idx >= 0 && idx < 4)
        _inventory[idx] = NULL;  // NE PAS DELETE !
}
```

⚠️ **ATTENTION** : `unequip` ne doit **PAS** delete la Materia ! Elle est juste "posée par terre".

### use() - Utiliser une Materia

```cpp
void Character::use(int idx, ICharacter& target)
{
    if (idx >= 0 && idx < 4 && _inventory[idx])
        _inventory[idx]->use(target);  // Polymorphisme !
}
```

---

## 🏭 MateriaSource - La fabrique de Materias

### Concept

`MateriaSource` est une **fabrique** qui :
1. **Apprend** des Materias (stocke des templates)
2. **Crée** des copies de ces templates à la demande

### learnMateria() - Apprendre

```cpp
void MateriaSource::learnMateria(AMateria* m)
{
    if (!m)
        return;
    for (int i = 0; i < 4; i++)
    {
        if (!_templates[i])
        {
            _templates[i] = m;  // Stocke le template
            return;
        }
    }
    delete m;  // Si plein, on delete pour éviter la fuite
}
```

### createMateria() - Créer

```cpp
AMateria* MateriaSource::createMateria(std::string const & type)
{
    for (int i = 0; i < 4; i++)
    {
        if (_templates[i] && _templates[i]->getType() == type)
            return _templates[i]->clone();  // Clone le template !
    }
    return NULL;  // Type inconnu
}
```

### Visualisation du flux

```
1. APPRENDRE
   ┌──────────────┐
   │ MateriaSource │
   │              │
   │ templates[0] │◄─── new Ice()
   │ templates[1] │◄─── new Cure()
   │ templates[2] │
   │ templates[3] │
   └──────────────┘

2. CRÉER
   createMateria("ice")
           │
           ▼
   templates[0]->clone()
           │
           ▼
   ┌─────────┐
   │ NEW Ice │ ◄── Nouvelle instance
   └─────────┘
```

---

## 🔄 Deep Copy dans Character

### Constructeur par copie

```cpp
Character::Character(Character const & other) : _name(other._name)
{
    for (int i = 0; i < 4; i++)
    {
        if (other._inventory[i])
            _inventory[i] = other._inventory[i]->clone();  // Clone !
        else
            _inventory[i] = NULL;
    }
}
```

### Opérateur d'assignation

```cpp
Character & Character::operator=(Character const & other)
{
    if (this != &other)
    {
        _name = other._name;
        for (int i = 0; i < 4; i++)
        {
            if (_inventory[i])
                delete _inventory[i];  // Libère l'ancien
            if (other._inventory[i])
                _inventory[i] = other._inventory[i]->clone();  // Clone le nouveau
            else
                _inventory[i] = NULL;
        }
    }
    return *this;
}
```

---

## 🧪 Démonstration dans le main

```cpp
// Création de la source de Materias
IMateriaSource* src = new MateriaSource();
src->learnMateria(new Ice());   // Apprend Ice
src->learnMateria(new Cure());  // Apprend Cure

// Création d'un personnage
ICharacter* me = new Character("me");

// Création et équipement de Materias
AMateria* tmp;
tmp = src->createMateria("ice");  // Clone de Ice
me->equip(tmp);
tmp = src->createMateria("cure"); // Clone de Cure
me->equip(tmp);

// Utilisation
ICharacter* bob = new Character("bob");
me->use(0, *bob);  // "* shoots an ice bolt at bob *"
me->use(1, *bob);  // "* heals bob's wounds *"

// Nettoyage
delete bob;
delete me;
delete src;
```

---

## ⚠️ Pièges à éviter

### 1. unequip() ne doit PAS delete

```cpp
// MAUVAIS ❌
void Character::unequip(int idx)
{
    if (idx >= 0 && idx < 4 && _inventory[idx])
    {
        delete _inventory[idx];  // NON ! Fuite ou double-free possible
        _inventory[idx] = NULL;
    }
}

// BON ✅
void Character::unequip(int idx)
{
    if (idx >= 0 && idx < 4)
        _inventory[idx] = NULL;  // Juste mettre à NULL
}
```

La Materia est "par terre" - le code appelant doit gérer sa mémoire.

### 2. Inventaire plein

```cpp
AMateria* extra = new Ice();
fullCharacter->equip(extra);  // N'équipe pas si plein
delete extra;  // DOIT être fait manuellement !
```

### 3. Forward declarations

```cpp
// Dans AMateria.hpp
class ICharacter;  // Forward declaration car on utilise ICharacter&

// Dans ICharacter.hpp
class AMateria;    // Forward declaration car on utilise AMateria*
```

---

## 📊 Résumé des classes

| Classe | Type | Rôle |
|--------|------|------|
| `ICharacter` | Interface | Contrat pour les personnages |
| `IMateriaSource` | Interface | Contrat pour les sources de Materia |
| `AMateria` | Abstraite | Base des Materias avec `clone()` |
| `Character` | Concrète | Implémente `ICharacter` |
| `MateriaSource` | Concrète | Implémente `IMateriaSource` |
| `Ice` | Concrète | Materia de glace |
| `Cure` | Concrète | Materia de soin |

---

## 🎓 Concepts clés à retenir

1. **Interface** = Contrat pur (que des méthodes virtuelles pures, pas d'attributs)
2. **Classe abstraite** = Base commune avec du code partagé + au moins une méthode pure
3. **Pattern Clone** = Permet de copier un objet polymorphique
4. **Deep copy** = Chaque copie a ses propres objets (pas de pointeurs partagés)
5. **Forward declaration** = Évite les dépendances circulaires
6. **Gestion mémoire** = Qui crée, qui delete ?

---

## 📝 Output attendu

```
=== Test du sujet ===
* shoots an ice bolt at bob *
* heals bob's wounds *

=== Tests supplementaires ===

--- Test copie profonde Character ---
Original: original
Copy: copy
Original use:
* shoots an ice bolt at target *
* heals target's wounds *
Copy use:
* shoots an ice bolt at target *
* heals target's wounds *

--- Test unequip ---
unequip OK (pas de double free)

--- Test inventaire plein ---
Inventaire plein gere correctement
```

---

## 🔗 Évolution du module CPP04

| Ex | Concept principal | Classes |
|----|-------------------|---------|
| 00 | Polymorphisme de base | `Animal`, `Dog`, `Cat`, `virtual` |
| 01 | Deep copy avec pointeurs | `Brain*`, copie profonde |
| 02 | Classe abstraite | `AAnimal`, `= 0` |
| 03 | Interfaces + Design patterns | `ICharacter`, `IMateriaSource`, Clone |
