# Les différents types de cast en C++

En C++, il existe quatre types de cast explicites qui remplacent le cast de style C `(type)value`. Chacun a un usage spécifique et des garanties de sécurité différentes.

---

## Upcasting vs Downcasting

### Upcasting (Classe dérivée → Classe de base)

**Conversion d'un pointeur/référence d'une classe dérivée vers sa classe de base.**

```cpp
class Animal { virtual ~Animal() {} };
class Dog : public Animal {};

Dog* dog = new Dog();
Animal* animal = dog;  // Upcasting implicite - TOUJOURS SÛR
```

**Caractéristiques :**
- ✅ **Toujours sûr** (un Dog EST un Animal)
- ✅ **Implicite** (pas besoin de cast explicite)
- ✅ **Polymorphisme** : on peut traiter un Dog comme un Animal

### Downcasting (Classe de base → Classe dérivée)

**Conversion d'un pointeur/référence d'une classe de base vers une classe dérivée.**

```cpp
Animal* animal = new Dog();
Dog* dog = static_cast<Dog*>(animal);  // Downcasting - POTENTIELLEMENT DANGEREUX
```

**Caractéristiques :**
- ⚠️ **Potentiellement dangereux** (un Animal n'est pas forcément un Dog)
- ❌ **Doit être explicite**
- ⚠️ **Risque d'UB** si l'objet n'est pas du bon type

### Quelle différence avec les casts ?

| Situation | `static_cast` | `dynamic_cast` |
|-----------|---------------|----------------|
| **Upcasting** | ✅ Fonctionne (mais inutile, implicite) | ✅ Fonctionne |
| **Downcasting** | ⚠️ Pas de vérification runtime | ✅ Vérifie à runtime, retourne `nullptr` si échec |

### Exemple complet

```cpp
class Animal {
public:
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void bark() { std::cout << "Woof!" << std::endl; }
};

class Cat : public Animal {
public:
    void meow() { std::cout << "Meow!" << std::endl; }
};

int main() {
    // UPCASTING (implicite, toujours sûr)
    Dog* myDog = new Dog();
    Animal* animal1 = myDog;  // OK : Dog → Animal
    
    // DOWNCASTING avec static_cast (rapide mais dangereux)
    Animal* animal2 = new Dog();
    Dog* dog1 = static_cast<Dog*>(animal2);  // OK si on SAIT que c'est un Dog
    dog1->bark();  // OK
    
    // DOWNCASTING DANGEREUX avec static_cast
    Animal* animal3 = new Cat();
    Dog* dog2 = static_cast<Dog*>(animal3);  // Compile mais c'est un Cat !
    dog2->bark();  // UNDEFINED BEHAVIOR !
    
    // DOWNCASTING SÉCURISÉ avec dynamic_cast
    Animal* animal4 = new Cat();
    Dog* dog3 = dynamic_cast<Dog*>(animal4);  // Retourne nullptr car animal4 est un Cat
    if (dog3) {
        dog3->bark();  // Ne sera jamais exécuté
    } else {
        std::cout << "Ce n'est pas un Dog !" << std::endl;
    }
    
    return 0;
}
```

**Règle d'or :**
- **Upcasting** : Toujours sûr, souvent implicite
- **Downcasting avec `static_cast`** : Rapide mais tu dois SAVOIR que le type est correct
- **Downcasting avec `dynamic_cast`** : Plus lent mais VÉRIFIE que le type est correct

---

## 1. `static_cast<T>()`

### Usage
Le cast le plus courant et le plus sûr. Utilisé pour les conversions vérifiables au moment de la compilation.

### Cas d'utilisation
- Conversions entre types numériques (int → float, double → int, etc.)
- Conversions dans une hiérarchie de classes (upcasting et downcasting)
- Conversions explicites définies par des constructeurs ou opérateurs de conversion
- Conversion de pointeurs void* vers des types spécifiques

### Caractéristiques
- ✅ Vérifié à la compilation
- ✅ Pas de vérification à l'exécution (rapide)
- ❌ Pas de vérification de type polymorphique
- ❌ Downcasting non sûr si le type réel est incorrect

### Exemples
```cpp
// Conversion numérique
int i = 42;
double d = static_cast<double>(i);

// Upcasting (toujours sûr)
class Base { virtual ~Base() {} };
class Derived : public Base {};
Derived* derived = new Derived();
Base* base = static_cast<Base*>(derived);  // OK

// Downcasting (peut être dangereux!)
Base* base2 = new Base();
Derived* derived2 = static_cast<Derived*>(base2);  // Compilable mais UB!

// Conversion void*
void* ptr = malloc(sizeof(int));
int* intPtr = static_cast<int*>(ptr);
```

---

## 2. `reinterpret_cast<T>()`

### Usage
Cast "brutal" qui réinterprète les bits d'un type comme un autre type, sans conversion.

### Cas d'utilisation
- Conversion entre types de pointeurs incompatibles
- Conversion pointeur ↔ entier
- Manipulation de bas niveau (sérialisation, drivers, etc.)

### Caractéristiques
- ⚠️ Aucune vérification à la compilation
- ⚠️ Très dangereux et non portable
- ⚠️ Le résultat dépend de la plateforme
- ❌ Ne devrait être utilisé que dans du code système/bas niveau

### Exemples
```cpp
// Conversion pointeur → entier
int* ptr = new int(42);
uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);

// Conversion entre pointeurs incompatibles
float f = 3.14f;
int* intPtr = reinterpret_cast<int*>(&f);  // Interprète les bits du float comme un int

// Exemple pratique : manipulation binaire
struct Data {
    int a;
    char b;
};
Data data = {42, 'x'};
char* bytes = reinterpret_cast<char*>(&data);  // Accès aux bytes bruts
```

### ⚠️ Attention
```cpp
// DANGEREUX : undefined behavior
int i = 42;
float* f = reinterpret_cast<float*>(&i);  // Les bits de l'int ne forment pas un float valide
std::cout << *f << std::endl;  // UB!
```

---

## 3. `dynamic_cast<T>()`

### Usage
Cast sûr pour les conversions dans une hiérarchie polymorphique (avec fonctions virtuelles).

### Cas d'utilisation
- Downcasting sécurisé dans une hiérarchie de classes
- Vérification du type réel d'un objet à l'exécution
- Nécessite des fonctions virtuelles (RTTI activé)

### Caractéristiques
- ✅ Vérifie le type à l'exécution (RTTI)
- ✅ Retourne `nullptr` (pointeur) ou lance `bad_cast` (référence) en cas d'échec
- ❌ Plus lent (overhead runtime)
- ❌ Nécessite au moins une fonction virtuelle dans la classe

### Exemples
```cpp
class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void derivedMethod() {}
};

class Other : public Base {};

// Downcasting sûr
Base* base = new Derived();
Derived* derived = dynamic_cast<Derived*>(base);
if (derived != nullptr) {
    derived->derivedMethod();  // OK
}

// Cast échoue si le type est incorrect
Base* other = new Other();
Derived* failed = dynamic_cast<Derived*>(other);  // Retourne nullptr

// Avec référence (lance une exception)
try {
    Base& baseRef = *other;
    Derived& derivedRef = dynamic_cast<Derived&>(baseRef);  // Lance bad_cast
} catch (std::bad_cast& e) {
    std::cerr << "Cast failed: " << e.what() << std::endl;
}
```

### Quand l'utiliser ?
```cpp
// Situation typique : identifier le type d'un objet polymorphique
void processAnimal(Animal* animal) {
    if (Dog* dog = dynamic_cast<Dog*>(animal)) {
        dog->bark();
    } else if (Cat* cat = dynamic_cast<Cat*>(animal)) {
        cat->meow();
    }
}
```

---

## 4. `const_cast<T>()` (bonus)

### Usage
Ajoute ou retire le qualificateur `const` ou `volatile`.

### Cas d'utilisation
- Interfacer avec du code legacy non-const
- Garantir qu'une fonction ne modifie pas un objet (rare)

### Caractéristiques
- ⚠️ Modifier un objet réellement const → undefined behavior
- ⚠️ À utiliser avec précaution

### Exemples
```cpp
// Retirer const (attention au UB!)
const int ci = 42;
int& i = const_cast<int&>(ci);
// i = 43;  // UB! ci était vraiment const

// Cas valide : objet non-const casté en const puis recasté
int value = 10;
const int* cPtr = &value;
int* ptr = const_cast<int*>(cPtr);  // OK, value n'est pas vraiment const
*ptr = 20;  // OK

// Interfacer avec API legacy
void legacyFunction(char* str);  // Ne modifie pas str mais n'est pas const

void modernCode() {
    const char* message = "Hello";
    // legacyFunction(message);  // Erreur de compilation
    legacyFunction(const_cast<char*>(message));  // OK si on sait que la fonction ne modifie pas
}
```

---

## Tableau récapitulatif

| Cast | Vérification | Performance | Sécurité | Usage typique |
|------|-------------|-------------|----------|---------------|
| `static_cast` | Compilation | Rapide | Moyenne | Conversions standards |
| `reinterpret_cast` | Aucune | Rapide | Faible | Code bas niveau |
| `dynamic_cast` | Runtime (RTTI) | Lent | Élevée | Downcasting polymorphique |
| `const_cast` | Aucune | Rapide | Faible | Manipulation const/volatile |

---

## Règles générales

1. **Préférez `static_cast`** pour la plupart des conversions
2. **Utilisez `dynamic_cast`** quand vous avez besoin de vérifier le type à l'exécution
3. **Évitez `reinterpret_cast`** sauf pour du code système/bas niveau
4. **Évitez `const_cast`** autant que possible (signe de mauvaise conception)
5. **Évitez les casts de style C** `(Type)value` - préférez les casts C++ explicites

---

## Exemple comparatif

```cpp
class Base {
public:
    virtual ~Base() {}
    int baseValue = 10;
};

class Derived : public Base {
public:
    int derivedValue = 20;
};

int main() {
    Derived* d = new Derived();
    Base* b = d;
    
    // static_cast : rapide mais pas de vérification runtime
    Derived* d1 = static_cast<Derived*>(b);  // OK (on sait que b pointe vers Derived)
    
    // dynamic_cast : plus lent mais sûr
    Derived* d2 = dynamic_cast<Derived*>(b);  // OK, vérifie à runtime
    if (d2) {
        std::cout << d2->derivedValue << std::endl;
    }
    
    // Si b pointait vers Base au lieu de Derived:
    Base* b2 = new Base();
    Derived* d3 = static_cast<Derived*>(b2);    // Compile mais UB!
    Derived* d4 = dynamic_cast<Derived*>(b2);   // Retourne nullptr - SÉCURISÉ
    
    return 0;
}
```
