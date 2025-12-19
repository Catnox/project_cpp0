# Le Polymorphisme en C++ - Exercice 00

## 🎯 Objectif de l'exercice

Cet exercice illustre le concept fondamental du **polymorphisme** en C++, en particulier la différence entre une implémentation correcte (avec `virtual`) et une implémentation incorrecte (sans `virtual`).

---

## 📚 Qu'est-ce que le Polymorphisme ?

Le **polymorphisme** (du grec "plusieurs formes") permet à un objet d'être traité comme une instance de sa classe parente tout en conservant son comportement spécifique.

En C++, cela signifie qu'un pointeur de type `Animal*` peut pointer vers un objet `Dog` ou `Cat`, et appeler la bonne méthode selon le **type réel** de l'objet.

---

## 🔑 Le mot-clé `virtual`

### Dans la classe Animal (CORRECT ✅)

```cpp
class Animal
{
    protected:
        std::string _type;
    public:
        virtual ~Animal();           // Destructeur virtuel
        virtual void makeSound() const;  // Méthode virtuelle
};
```

Le mot-clé `virtual` indique au compilateur :
- **"Ne décide pas à la compilation quelle méthode appeler"**
- **"Attends l'exécution pour déterminer le type réel de l'objet"**

### Dans la classe WrongAnimal (INCORRECT ❌)

```cpp
class WrongAnimal
{
    protected:
        std::string _type;
    public:
        ~WrongAnimal();              // PAS de virtual
        void makeSound() const;       // PAS de virtual
};
```

Sans `virtual`, le compilateur choisit la méthode à appeler **selon le type du pointeur**, pas selon le type réel de l'objet.

---

## 🧪 Démonstration dans le main

### Cas CORRECT (avec virtual)

```cpp
const Animal* j = new Dog();  // Pointeur Animal vers objet Dog
const Animal* i = new Cat();  // Pointeur Animal vers objet Cat

j->makeSound();  // Affiche: "Woof Woof!" ✅
i->makeSound();  // Affiche: "Meow!" ✅
```

**Pourquoi ça marche ?**
- `makeSound()` est `virtual` dans `Animal`
- À l'exécution, le programme vérifie le **type réel** de l'objet
- Il appelle la méthode de `Dog` ou `Cat` selon le cas

### Cas INCORRECT (sans virtual)

```cpp
const WrongAnimal* wrongCat = new WrongCat();

wrongCat->makeSound();  // Affiche: "WrongAnimal sound!" ❌
```

**Pourquoi ça ne marche pas ?**
- `makeSound()` n'est PAS `virtual` dans `WrongAnimal`
- Le compilateur voit un pointeur de type `WrongAnimal*`
- Il appelle directement `WrongAnimal::makeSound()` sans vérifier le type réel

---

## 🔄 La Table des Fonctions Virtuelles (vtable)

Quand une classe a des méthodes `virtual`, le compilateur crée une **vtable** (virtual table) :

```
┌─────────────────────────────────────────────────────────┐
│                    VTABLE Animal                         │
├─────────────────────────────────────────────────────────┤
│  makeSound() → Animal::makeSound()                       │
│  ~Animal()   → Animal::~Animal()                         │
└─────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────┐
│                    VTABLE Dog                            │
├─────────────────────────────────────────────────────────┤
│  makeSound() → Dog::makeSound()     ← REMPLACÉ          │
│  ~Animal()   → Dog::~Dog()          ← REMPLACÉ          │
└─────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────┐
│                    VTABLE Cat                            │
├─────────────────────────────────────────────────────────┤
│  makeSound() → Cat::makeSound()     ← REMPLACÉ          │
│  ~Animal()   → Cat::~Cat()          ← REMPLACÉ          │
└─────────────────────────────────────────────────────────┘
```

Chaque objet contient un pointeur caché vers sa vtable, permettant de résoudre les appels de méthodes virtuelles à l'exécution.

---

## ⚠️ Importance du Destructeur Virtuel

```cpp
virtual ~Animal();  // ESSENTIEL !
```

### Pourquoi le destructeur doit être virtual ?

```cpp
Animal* ptr = new Dog();
delete ptr;  // Appelle quel destructeur ?
```

| Avec `virtual ~Animal()` | Sans `virtual ~Animal()` |
|--------------------------|--------------------------|
| ✅ Appelle `~Dog()` puis `~Animal()` | ❌ Appelle seulement `~Animal()` |
| ✅ Mémoire correctement libérée | ❌ Fuite mémoire possible |

---

## 📊 Résumé : Comparaison Animal vs WrongAnimal

| Aspect | Animal (Correct) | WrongAnimal (Incorrect) |
|--------|------------------|-------------------------|
| Destructeur | `virtual ~Animal()` | `~WrongAnimal()` |
| makeSound() | `virtual void makeSound()` | `void makeSound()` |
| Polymorphisme | ✅ Fonctionne | ❌ Ne fonctionne pas |
| Résolution | À l'exécution (dynamique) | À la compilation (statique) |

---

## 🎓 Règles à retenir

1. **Toujours déclarer le destructeur `virtual`** dans une classe de base polymorphe
2. **Déclarer `virtual`** les méthodes qui doivent être redéfinies dans les classes dérivées
3. **Le mot-clé `virtual` dans la classe dérivée est optionnel** (mais recommandé pour la clarté)
4. **Un pointeur de type base** peut appeler les méthodes de la classe dérivée grâce au polymorphisme

---

## 📝 Output attendu

```
=== Test Animal / Dog / Cat ===
Animal Default constructed.
Animal Default constructed.
Dog Default constructed.
Animal Default constructed.
Cat Default constructed.
Dog 
Cat 
Meow!
Woof Woof!
Animal sound!
Cat destructed.
Animal destructed.
Dog destructed.
Animal destructed.
Animal destructed.

=== Test WrongAnimal / WrongCat ===
WrongAnimal Default constructed.
WrongAnimal Default constructed.
WrongCat Default constructed.
WrongCat 
WrongAnimal sound!    ← Le polymorphisme ne fonctionne pas !
WrongAnimal sound!
WrongCat destructed.
WrongAnimal destructed.
WrongAnimal destructed.
```

---

## 🔗 Pour aller plus loin

- **ex01** : Ajout de la classe `Brain` pour comprendre la copie profonde
- **ex02** : Classes abstraites avec `virtual void makeSound() const = 0;`
- **ex03** : Interfaces et classes abstraites multiples
