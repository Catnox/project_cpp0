# Deep Copy vs Shallow Copy - Exercice 01

## 🎯 Objectif de l'exercice

Cet exercice introduit la gestion de la **mémoire dynamique** dans les classes avec héritage. Chaque `Dog` et `Cat` possède un pointeur vers un objet `Brain` alloué dynamiquement.

---

## 🧠 Structure de l'exercice

```cpp
class Dog : public Animal
{
    private:
        Brain* _brain;  // Pointeur vers un objet alloué avec new
    // ...
};

class Brain
{
    private:
        std::string ideas[100];  // Tableau de 100 idées
    // ...
};
```

---

## ❌ Le problème : Shallow Copy (Copie superficielle)

### Si on ne fait PAS de deep copy :

```cpp
// MAUVAISE IMPLÉMENTATION ❌
Dog::Dog(const Dog &other) : Animal(other)
{
    _brain = other._brain;  // On copie juste le POINTEUR !
}
```

### Ce qui se passe en mémoire :

```
AVANT LA COPIE:
┌─────────────┐         ┌─────────────┐
│    dog1     │         │    Brain    │
│ _brain: ────┼────────►│ ideas[100]  │
│             │         │             │
└─────────────┘         └─────────────┘

APRÈS SHALLOW COPY (dog2 = copie de dog1):
┌─────────────┐         
│    dog1     │         ┌─────────────┐
│ _brain: ────┼────────►│    Brain    │
│             │         │ ideas[100]  │
└─────────────┘    ┌───►│             │
                   │    └─────────────┘
┌─────────────┐    │
│    dog2     │    │
│ _brain: ────┼────┘
│             │
└─────────────┘

⚠️ Les deux objets pointent vers le MÊME Brain !
```

### Problèmes causés :

1. **Modification partagée** : Si `dog2` modifie une idée, `dog1` est aussi affecté
2. **Double free** : À la destruction, les deux destructeurs vont essayer de `delete` le même `Brain` → **CRASH** ou comportement indéfini
3. **Dangling pointer** : Si `dog1` est détruit en premier, `dog2._brain` pointe vers de la mémoire libérée

---

## ✅ La solution : Deep Copy (Copie profonde)

### Constructeur par copie

```cpp
Dog::Dog(const Dog &other) : Animal(other)
{
    _brain = new Brain(*other._brain);  // On crée un NOUVEAU Brain
}
```

### Ce qui se passe en mémoire :

```
APRÈS DEEP COPY:
┌─────────────┐         ┌─────────────┐
│    dog1     │         │   Brain 1   │
│ _brain: ────┼────────►│ ideas[100]  │
│             │         │ "I love..."  │
└─────────────┘         └─────────────┘

┌─────────────┐         ┌─────────────┐
│    dog2     │         │   Brain 2   │
│ _brain: ────┼────────►│ ideas[100]  │  ← COPIE des données
│             │         │ "I love..."  │
└─────────────┘         └─────────────┘

✅ Chaque objet a son propre Brain !
```

---

## 🔄 Opérateur d'assignation : Pourquoi delete puis new ?

### Le code :

```cpp
Dog &Dog::operator=(const Dog &other)
{
    if (this != &other) {
        Animal::operator=(other);
        delete _brain;                    // 1. Libérer l'ancien Brain
        _brain = new Brain(*other._brain); // 2. Créer un nouveau Brain
    }
    return *this;
}
```

### Pourquoi ces étapes ?

#### Étape 1 : `delete _brain`

L'objet `this` a **déjà** un `Brain` alloué (lors de sa construction). Si on ne le supprime pas :
- **Fuite mémoire** : L'ancien `Brain` reste en mémoire, inaccessible
- Chaque assignation créerait une nouvelle fuite

#### Étape 2 : `_brain = new Brain(*other._brain)`

On crée un **nouveau** `Brain` qui est une copie de celui de `other`.

### Visualisation :

```
AVANT ASSIGNATION (dog3 = dog1):
┌─────────────┐         ┌─────────────┐
│    dog3     │         │  Brain 3    │  ← Ancien Brain
│ _brain: ────┼────────►│ ideas vides │
└─────────────┘         └─────────────┘

┌─────────────┐         ┌─────────────┐
│    dog1     │         │  Brain 1    │
│ _brain: ────┼────────►│ "I love..." │
└─────────────┘         └─────────────┘

APRÈS delete _brain:
┌─────────────┐         
│    dog3     │         ❌ Brain 3 libéré
│ _brain: ?   │         
└─────────────┘         

APRÈS new Brain(*other._brain):
┌─────────────┐         ┌─────────────┐
│    dog3     │         │ Brain 3 NEW │
│ _brain: ────┼────────►│ "I love..." │  ← Copie de Brain 1
└─────────────┘         └─────────────┘
```

---

## ⚠️ Protection : `if (this != &other)`

```cpp
if (this != &other) {
    // ...
}
```

Cette vérification protège contre l'**auto-assignation** :

```cpp
dog1 = dog1;  // Sans la protection, on ferait delete puis new sur le même objet !
```

Sans cette protection :
1. `delete _brain` → On supprime notre propre Brain
2. `new Brain(*other._brain)` → On essaie de copier un Brain supprimé → **CRASH**

---

## 🔍 Démonstration dans le main

```cpp
// Test deep copy
Dog dog1;
dog1.getBrain()->setIdea(0, "I love bones");
Dog dog2(dog1);

std::cout << dog1.getBrain()->getIdea(0);  // "I love bones"
std::cout << dog2.getBrain()->getIdea(0);  // "I love bones" (copie)

dog2.getBrain()->setIdea(0, "I love running");

std::cout << dog1.getBrain()->getIdea(0);  // "I love bones" ✅ (pas modifié)
std::cout << dog2.getBrain()->getIdea(0);  // "I love running" ✅
```

Si c'était une **shallow copy**, modifier `dog2` aurait aussi modifié `dog1` !

---

## 📊 Résumé : Shallow vs Deep Copy

| Aspect | Shallow Copy | Deep Copy |
|--------|--------------|-----------|
| Copie des pointeurs | Juste l'adresse | Nouveau objet alloué |
| Mémoire | Partagée | Indépendante |
| Modification | Affecte les deux | Indépendante |
| Destruction | Double free 💥 | Sûre ✅ |
| Complexité | Simple | Plus de code |

---

## 🎓 Règles à retenir

1. **Si une classe a un pointeur** → implémenter la copie profonde
2. **Constructeur par copie** : `new` pour créer une copie de l'objet pointé
3. **Opérateur d'assignation** : `delete` l'ancien, puis `new` pour le nouveau
4. **Toujours vérifier l'auto-assignation** (`if (this != &other)`)
5. **Destructeur** : `delete` le pointeur pour éviter les fuites mémoire

---

## 📝 Ordre des appels (création et destruction)

```
=== Création Dog dog1 ===
Animal Default constructed.
Brain Default constructed.
Dog Default constructed.

=== Copie Dog dog2(dog1) ===
Animal copy constructed.
Brain copy constructed.      ← Nouveau Brain créé
Dog copy constructed.

=== Destruction ===
Dog destructed.
Brain destructed.            ← Brain de dog2 libéré
Animal destructed.
Dog destructed.
Brain destructed.            ← Brain de dog1 libéré
Animal destructed.
```

---

## 🔗 Lien avec le polymorphisme

Le destructeur `virtual` de `Animal` est essentiel ici :

```cpp
Animal* ptr = new Dog();  // Dog a un Brain alloué
delete ptr;               // Appelle ~Dog() puis ~Animal()
```

Sans `virtual ~Animal()`, seul `~Animal()` serait appelé → **fuite mémoire** du Brain !
