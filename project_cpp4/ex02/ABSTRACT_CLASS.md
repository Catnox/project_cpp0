# Classes Abstraites en C++ - Exercice 02

## 🎯 Objectif de l'exercice

Cet exercice transforme la classe `Animal` en classe **abstraite** `AAnimal`, rendant impossible l'instanciation directe d'un "Animal" générique.

---

## 📚 Qu'est-ce qu'une Classe Abstraite ?

Une **classe abstraite** est une classe qui :
- Contient au moins une **méthode virtuelle pure** (`= 0`)
- **Ne peut pas être instanciée** directement
- Sert de **modèle** pour les classes dérivées

---

## 🔑 La syntaxe : Méthode Virtuelle Pure

### Avant (ex00/ex01) - Classe concrète

```cpp
class Animal
{
    public:
        virtual void makeSound() const;  // Méthode virtuelle (avec implémentation)
};
```

On peut créer un `Animal` :
```cpp
Animal* meta = new Animal();  // ✅ Fonctionne
meta->makeSound();            // Affiche "Animal sound!"
```

### Après (ex02) - Classe abstraite

```cpp
class AAnimal
{
    public:
        virtual void makeSound() const = 0;  // Méthode virtuelle PURE
};
```

Le `= 0` signifie :
- **"Cette méthode n'a pas d'implémentation dans cette classe"**
- **"Les classes dérivées DOIVENT l'implémenter"**

```cpp
AAnimal* meta = new AAnimal();  // ❌ ERREUR DE COMPILATION !
// error: cannot declare variable 'meta' to be of abstract type 'AAnimal'
```

---

## 📝 Convention de nommage

Le préfixe `A` dans `AAnimal` est une **convention 42** :
- **A** = Abstract
- Indique visuellement que la classe est abstraite

Autres conventions courantes :
- `IInterface` (I = Interface)
- `AbstractAnimal`

---

## 🔄 Comparaison : Animal vs AAnimal

| Aspect | Animal (ex00/ex01) | AAnimal (ex02) |
|--------|-------------------|----------------|
| `makeSound()` | `virtual void makeSound() const;` | `virtual void makeSound() const = 0;` |
| Instanciation | ✅ `new Animal()` possible | ❌ Impossible |
| But | Classe de base utilisable | Modèle/contrat uniquement |
| Nom | `Animal` | `AAnimal` (convention 42) |

---

## 🎨 Pourquoi utiliser une classe abstraite ?

### 1. **Logique métier**

Un "Animal" générique n'a pas de sens dans la vraie vie. Quel son fait un "Animal" ?

```cpp
// Avant (problématique) :
Animal* a = new Animal();
a->makeSound();  // "Animal sound!" - Ça ne veut rien dire !

// Après (logique) :
// On ne peut créer que des animaux CONCRETS
Dog* d = new Dog();
d->makeSound();  // "Woof Woof!" ✅
```

### 2. **Forcer l'implémentation**

Les classes dérivées **DOIVENT** implémenter `makeSound()` :

```cpp
class Bird : public AAnimal
{
    // Si on n'implémente pas makeSound()...
};

Bird* b = new Bird();  // ❌ ERREUR !
// error: cannot declare variable 'b' to be of abstract type 'Bird'
// note: because 'Bird' does not implement 'makeSound()'
```

### 3. **Définir un contrat**

La classe abstraite définit ce que les classes dérivées **doivent faire**, sans dire **comment** :

```cpp
class AAnimal
{
    public:
        virtual void makeSound() const = 0;  // Contrat : tout animal fait un son
        virtual void move() const = 0;       // Contrat : tout animal se déplace
        virtual void eat() const = 0;        // Contrat : tout animal mange
};
```

---

## 📊 Hiérarchie de l'ex02

```
           ┌─────────────────────┐
           │      AAnimal        │  ← Classe ABSTRAITE
           │  (ne peut pas être  │
           │    instanciée)      │
           │                     │
           │ + makeSound() = 0   │  ← Méthode virtuelle pure
           └──────────┬──────────┘
                      │
         ┌────────────┴────────────┐
         │                         │
         ▼                         ▼
┌─────────────────┐       ┌─────────────────┐
│       Dog       │       │       Cat       │
│   (concrète)    │       │   (concrète)    │
│                 │       │                 │
│ + makeSound()   │       │ + makeSound()   │
│   "Woof Woof!"  │       │   "Meow!"       │
│                 │       │                 │
│ + Brain* _brain │       │ + Brain* _brain │
└─────────────────┘       └─────────────────┘

✅ new Dog()  → OK
✅ new Cat()  → OK
❌ new AAnimal() → ERREUR
```

---

## 🧪 Démonstration dans le main

```cpp
int main()
{
    // AAnimal* meta = new AAnimal();  // ❌ DÉCOMMENTÉ = ERREUR
    // error: cannot declare variable 'meta' to be of abstract type 'AAnimal'

    // Mais le polymorphisme fonctionne toujours !
    const AAnimal* j = new Dog();  // ✅ Pointeur AAnimal vers Dog
    const AAnimal* i = new Cat();  // ✅ Pointeur AAnimal vers Cat

    j->makeSound();  // "Woof Woof!"
    i->makeSound();  // "Meow!"

    delete j;
    delete i;
}
```

---

## ⚠️ Règles importantes

### 1. Une méthode virtuelle pure PEUT avoir une implémentation

```cpp
// Dans AAnimal.hpp
virtual void makeSound() const = 0;

// Dans AAnimal.cpp (optionnel)
void AAnimal::makeSound() const
{
    std::cout << "Default animal sound" << std::endl;
}
```

Les classes dérivées peuvent alors appeler cette implémentation :
```cpp
void Dog::makeSound() const
{
    AAnimal::makeSound();  // Appel de l'implémentation de base
    std::cout << "Woof!" << std::endl;
}
```

### 2. Si UNE méthode est pure → la classe est abstraite

```cpp
class Example
{
    public:
        void normalMethod();           // Méthode normale
        virtual void virtualMethod();  // Méthode virtuelle
        virtual void pureMethod() = 0; // UNE seule méthode pure
};

Example* e = new Example();  // ❌ ERREUR - Example est abstraite
```

### 3. Une classe dérivée reste abstraite si elle n'implémente pas tout

```cpp
class AAnimal
{
    virtual void makeSound() const = 0;
    virtual void move() const = 0;
};

class Dog : public AAnimal
{
    void makeSound() const override { /* ... */ }
    // move() pas implémenté !
};

Dog* d = new Dog();  // ❌ ERREUR - Dog est encore abstraite
```

---

## 🔗 Évolution à travers les exercices

| Exercice | Classe | Type | Instanciable |
|----------|--------|------|--------------|
| ex00 | `Animal` | Concrète | ✅ Oui |
| ex01 | `Animal` | Concrète | ✅ Oui |
| ex02 | `AAnimal` | **Abstraite** | ❌ Non |
| ex03 | `ICharacter`, `IMateriaSource` | **Interfaces** | ❌ Non |

---

## 🎓 Résumé

| Concept | Description |
|---------|-------------|
| Classe abstraite | Classe avec au moins une méthode virtuelle pure |
| Méthode virtuelle pure | `virtual void method() = 0;` |
| Instanciation | Impossible sur une classe abstraite |
| But | Définir un contrat/modèle pour les classes dérivées |
| Convention 42 | Préfixe `A` (ex: `AAnimal`, `AMateria`) |

---

## 📝 Erreur de compilation typique

```
error: cannot declare variable 'meta' to be of abstract type 'AAnimal'
note: because the following virtual functions are pure within 'AAnimal':
note: virtual void AAnimal::makeSound() const
```

Cette erreur confirme que ta classe abstraite fonctionne correctement !
