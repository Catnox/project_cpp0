# Exercice 03 : Factory Pattern et Pointeurs de Fonctions

## Concepts clés : Factory Pattern, Pointeurs de fonctions membres

---

## 1. Le problème

Comment créer différents types de formulaires **sans if/else excessifs** ?

### ❌ Mauvaise approche (interdite) :
```cpp
AForm* makeForm(const std::string& name, const std::string& target)
{
    if (name == "shrubbery creation")
        return new ShrubberyCreationForm(target);
    else if (name == "robotomy request")
        return new RobotomyRequestForm(target);
    else if (name == "presidential pardon")
        return new PresidentialPardonForm(target);
    else
        throw FormNotFoundException();
}
```

### Problèmes :
- Difficile à maintenir (ajout = modification)
- Code répétitif
- Violation du principe Open/Closed

---

## 2. Solution : Pointeurs de fonctions membres

### Déclaration du type :
```cpp
class Intern
{
    private:
        // Typedef pour un pointeur vers une fonction membre
        typedef AForm* (Intern::*FormCreator)(const std::string& target) const;
};
```

### Décomposition :
```
AForm*              → Type de retour
(Intern::*          → Pointeur vers membre de Intern
FormCreator)        → Nom du type
(const std::string&)→ Paramètre
const               → Fonction const
```

---

## 3. Méthodes de création

```cpp
class Intern
{
    private:
        AForm* createShrubberyCreationForm(const std::string& target) const;
        AForm* createRobotomyRequestForm(const std::string& target) const;
        AForm* createPresidentialPardonForm(const std::string& target) const;
};

AForm* Intern::createShrubberyCreationForm(const std::string& target) const
{
    return new ShrubberyCreationForm(target);
}
// ... idem pour les autres
```

---

## 4. Tableaux parallèles

```cpp
AForm* Intern::makeForm(const std::string& formName, const std::string& target)
{
    // Tableau des noms de formulaires
    const std::string formNames[] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };

    // Tableau des fonctions de création correspondantes
    FormCreator formCreators[] = {
        &Intern::createShrubberyCreationForm,
        &Intern::createRobotomyRequestForm,
        &Intern::createPresidentialPardonForm
    };

    const int numForms = 3;

    // Recherche et création
    for (int i = 0; i < numForms; i++)
    {
        if (formName == formNames[i])
        {
            AForm* form = (this->*formCreators[i])(target);
            std::cout << "Intern creates " << form->getName() << std::endl;
            return form;
        }
    }

    throw FormNotFoundException();
}
```

---

## 5. Syntaxe d'appel d'un pointeur de fonction membre

```cpp
// Déclaration
FormCreator creator = &Intern::createShrubberyCreationForm;

// Appel
AForm* form = (this->*creator)(target);
//            ^^^^^^^^^^^^^^^^
//            Syntaxe spéciale pour appeler via pointeur membre
```

### Décomposition :
- `this->*` : déréférence le pointeur de fonction membre sur l'objet courant
- `creator` : le pointeur de fonction
- `(target)` : les arguments

---

## 6. Factory Pattern

Le **Factory Pattern** est un patron de conception qui :
- Encapsule la création d'objets
- Permet de créer des objets sans spécifier leur classe exacte

```
┌─────────┐     makeForm("robotomy request", "Bender")     ┌───────────────────┐
│  Intern │ ──────────────────────────────────────────────>│ RobotomyRequest   │
│ (Factory)│                                                │      Form         │
└─────────┘                                                └───────────────────┘
     │
     │ Crée le bon type selon le paramètre
     │
     ▼
┌─────────────────────────────────────────────────────┐
│ "shrubbery creation" → ShrubberyCreationForm        │
│ "robotomy request"   → RobotomyRequestForm          │
│ "presidential pardon"→ PresidentialPardonForm       │
└─────────────────────────────────────────────────────┘
```

---

## 7. Avantages de cette approche

| Aspect | Avantage |
|--------|----------|
| **Extensibilité** | Ajouter un form = ajouter 1 ligne dans chaque tableau |
| **Lisibilité** | Pas de if/else imbriqués |
| **Maintenabilité** | Logique centralisée |
| **DRY** | Pas de répétition de code |

### Pour ajouter un nouveau formulaire :
```cpp
// 1. Ajouter dans le tableau des noms
"new form name",

// 2. Ajouter dans le tableau des créateurs
&Intern::createNewForm,

// 3. Implémenter la méthode de création
AForm* Intern::createNewForm(const std::string& target) const {
    return new NewForm(target);
}
```

---

## 8. L'Intern : une classe simple

```cpp
class Intern
{
    public:
        Intern();
        Intern(const Intern& other);
        Intern& operator=(const Intern& other);
        ~Intern();

        AForm* makeForm(const std::string& formName, const std::string& target);
};
```

### Caractéristiques :
- Pas de nom
- Pas de grade
- Suit l'Orthodox Canonical Form
- Seule utilité : créer des formulaires

---

## 9. Gestion de la mémoire

```cpp
// L'Intern crée le formulaire avec new
AForm* form = intern.makeForm("robotomy request", "Bender");

// L'appelant est responsable de delete
delete form;
```

> **Règle** : Celui qui appelle `makeForm()` doit gérer la mémoire du formulaire retourné.

---

## 10. Questions d'évaluation possibles

1. **Qu'est-ce que le Factory Pattern ?**
   > Un patron de conception qui encapsule la création d'objets, permettant de créer des instances sans connaître leur classe exacte.

2. **Pourquoi éviter les if/else excessifs ?**
   > Code difficile à maintenir, violation du principe Open/Closed, duplication de logique.

3. **Qu'est-ce qu'un pointeur de fonction membre ?**
   > Un pointeur qui stocke l'adresse d'une fonction membre d'une classe. Syntaxe : `ReturnType (Class::*name)(params)`.

4. **Comment appeler une fonction via un pointeur de fonction membre ?**
   > Avec la syntaxe `(object.*pointer)(args)` ou `(this->*pointer)(args)`.

5. **Qui est responsable de libérer la mémoire du formulaire créé ?**
   > L'appelant de `makeForm()`, pas l'Intern.

6. **Pourquoi l'Intern n'a pas de nom ni de grade ?**
   > Selon le sujet, l'Intern n'a "pas de caractéristiques uniques". C'est juste une "usine" à formulaires.

---

## 11. Alternative : Tableau de structures

Une autre approche valide (sans pointeurs de fonctions) :

```cpp
struct FormInfo {
    std::string name;
    AForm* (*creator)(const std::string&);  // Pointeur de fonction libre
};

// Fonctions libres
AForm* createShrubbery(const std::string& target) {
    return new ShrubberyCreationForm(target);
}

// Tableau
FormInfo forms[] = {
    {"shrubbery creation", createShrubbery},
    // ...
};
```

---

## 12. Diagramme de séquence

```
  Client              Intern                    Factory Logic
     │                   │                            │
     │ makeForm("robotomy│request", "Bender")         │
     │──────────────────>│                            │
     │                   │                            │
     │                   │ Parcourt tableaux          │
     │                   │───────────────────────────>│
     │                   │                            │
     │                   │ Trouve "robotomy request"  │
     │                   │<───────────────────────────│
     │                   │                            │
     │                   │ (this->*creator)(target)   │
     │                   │───────────────────────────>│
     │                   │                            │
     │                   │ new RobotomyRequestForm    │
     │                   │<───────────────────────────│
     │                   │                            │
     │   AForm* form     │                            │
     │<──────────────────│                            │
     │                   │                            │
     │ delete form       │                            │
     │                   │                            │
```

---

## Résumé

| Concept | Description |
|---------|-------------|
| Factory Pattern | Création d'objets encapsulée |
| Pointeur de fonction membre | `ReturnType (Class::*name)(params)` |
| Tableaux parallèles | Noms + créateurs alignés |
| Responsabilité mémoire | Appelant doit delete |
| Extensibilité | Ajout facile de nouveaux types |
