# Exercice 02 : Identification de Types avec dynamic_cast

## Concept clé : dynamic_cast et RTTI (Run-Time Type Information)

---

## 1. Problème à résoudre

On a un pointeur `Base*` qui pointe vers un objet `A`, `B`, ou `C`.
**Comment savoir le type réel de l'objet ?**

```cpp
Base* ptr = generate();  // A, B, ou C ?
identify(ptr);           // → Doit afficher "A", "B", ou "C"
```

---

## 2. dynamic_cast

### Avec un pointeur :
```cpp
Base* ptr = new A();

A* a = dynamic_cast<A*>(ptr);
if (a != NULL)
    std::cout << "C'est un A !" << std::endl;
```

### Comportement :
- **Succès** : retourne un pointeur valide vers le type demandé
- **Échec** : retourne `NULL` (ou `nullptr` en C++11)

### Avec une référence :
```cpp
Base& ref = *ptr;

try {
    A& a = dynamic_cast<A&>(ref);
    std::cout << "C'est un A !" << std::endl;
}
catch (...) {
    std::cout << "Ce n'est pas un A" << std::endl;
}
```

### Comportement :
- **Succès** : retourne une référence valide
- **Échec** : **lance une exception** `std::bad_cast`

---

## 3. Pourquoi dynamic_cast fonctionne ?

### Prérequis : classe polymorphique
```cpp
class Base
{
    public:
        virtual ~Base();  // Au moins une fonction virtuelle !
};
```

### RTTI (Run-Time Type Information)
- Le compilateur stocke des informations de type dans chaque objet polymorphique
- `dynamic_cast` consulte ces informations à l'exécution
- C'est pourquoi on a besoin d'au moins une fonction virtuelle

---

## 4. Structure de l'exercice

```
        ┌──────────┐
        │   Base   │  (destructeur virtuel)
        └────┬─────┘
             │
    ┌────────┼────────┐
    │        │        │
    ▼        ▼        ▼
┌──────┐ ┌──────┐ ┌──────┐
│  A   │ │  B   │ │  C   │
└──────┘ └──────┘ └──────┘
```

### Classes vides qui héritent de Base :
```cpp
class A : public Base {};
class B : public Base {};
class C : public Base {};
```

---

## 5. Fonction generate()

```cpp
Base* generate(void)
{
    int random = std::rand() % 3;
    
    switch (random)
    {
        case 0: return new A();
        case 1: return new B();
        default: return new C();
    }
}
```

Retourne aléatoirement un `A`, `B`, ou `C` comme `Base*`.

---

## 6. Fonction identify(Base* p)

### Avec pointeur → utilise le retour NULL :
```cpp
void identify(Base* p)
{
    if (dynamic_cast<A*>(p) != NULL)
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p) != NULL)
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p) != NULL)
        std::cout << "C" << std::endl;
}
```

---

## 7. Fonction identify(Base& p)

### Avec référence → utilise les exceptions :
```cpp
void identify(Base& p)
{
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    }
    catch (...) {}
    
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    }
    catch (...) {}
    
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    }
    catch (...) {}
}
```

### Pourquoi `catch (...)` ?
- Le sujet interdit `#include <typeinfo>`
- On ne peut donc pas attraper `std::bad_cast` spécifiquement
- `catch (...)` attrape **toutes** les exceptions

### Pourquoi `(void)` ?
- On ne veut pas utiliser le résultat du cast
- `(void)` supprime le warning "unused variable"

---

## 8. Interdit : typeinfo

### Ce qu'on ne peut PAS faire :
```cpp
#include <typeinfo>  // INTERDIT !

void identify(Base* p)
{
    std::cout << typeid(*p).name() << std::endl;  // INTERDIT !
}
```

### Pourquoi ?
- L'exercice veut nous faire comprendre `dynamic_cast`
- `typeid` serait trop facile et ne montre pas le mécanisme

---

## 9. Comparaison : Pointeur vs Référence

| Aspect | Pointeur | Référence |
|--------|----------|-----------|
| Échec | Retourne `NULL` | Lance exception |
| Test | `if (ptr != NULL)` | `try/catch` |
| Peut être null | Oui | Non |
| Syntaxe | `dynamic_cast<T*>(p)` | `dynamic_cast<T&>(p)` |

---

## 10. Questions d'évaluation possibles

1. **Qu'est-ce que dynamic_cast ?**
   > Un opérateur de conversion C++ qui vérifie le type à l'exécution pour les classes polymorphiques.

2. **Pourquoi Base doit avoir un destructeur virtuel ?**
   > Pour que la classe soit polymorphique et que dynamic_cast puisse fonctionner (RTTI).

3. **Quelle est la différence entre dynamic_cast sur pointeur et référence ?**
   > Avec un pointeur, l'échec retourne NULL. Avec une référence, l'échec lance une exception.

4. **Pourquoi ne pas utiliser typeid ?**
   > C'est interdit par le sujet. De plus, dynamic_cast montre mieux le mécanisme de RTTI.

5. **Que signifie RTTI ?**
   > Run-Time Type Information. Informations de type stockées par le compilateur pour les classes polymorphiques.

6. **Pourquoi catch(...) et pas catch(std::bad_cast&) ?**
   > Le sujet interdit l'inclusion de `<typeinfo>` où `std::bad_cast` est défini.

---

## 11. Diagramme : dynamic_cast en action

```
Base* ptr = new B();

dynamic_cast<A*>(ptr)
        │
        ▼
   ┌─────────────────┐
   │ RTTI Check:     │
   │ ptr pointe vers │
   │ un objet B      │
   │                 │
   │ A* demandé      │
   │ mais c'est B    │
   └────────┬────────┘
            │
            ▼
      Retourne NULL


dynamic_cast<B*>(ptr)
        │
        ▼
   ┌─────────────────┐
   │ RTTI Check:     │
   │ ptr pointe vers │
   │ un objet B      │
   │                 │
   │ B* demandé      │
   │ C'EST B ! ✓     │
   └────────┬────────┘
            │
            ▼
   Retourne B* valide
```

---

## 12. Downcasting vs Upcasting

### Upcasting (toujours sûr) :
```cpp
A* a = new A();
Base* base = a;  // Pas besoin de cast, implicite
```

### Downcasting (nécessite vérification) :
```cpp
Base* base = new A();
A* a = dynamic_cast<A*>(base);  // Vérification à l'exécution
```

---

## Résumé

| Concept | Description |
|---------|-------------|
| `dynamic_cast` | Cast vérifié à l'exécution pour classes polymorphiques |
| RTTI | Run-Time Type Information |
| Polymorphisme | Nécessite au moins une fonction virtuelle |
| Pointeur : échec | Retourne NULL |
| Référence : échec | Lance std::bad_cast |
| `catch (...)` | Attrape toutes les exceptions |
