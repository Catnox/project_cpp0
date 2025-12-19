# Exercice 01 : Formulaires et Relations entre Classes

## Concepts clés : Composition et Interaction entre objets

---

## 1. Architecture des classes

```
┌─────────────┐         ┌─────────────┐
│  Bureaucrat │ ──────> │    Form     │
└─────────────┘ signForm└─────────────┘
       │                       │
       │                       │ beSigned()
       └───────────────────────┘
```

Le **Bureaucrat** interagit avec le **Form** :
- `Bureaucrat::signForm(Form&)` → appelle `Form::beSigned(Bureaucrat&)`

---

## 2. Forward Declaration

### Problème : dépendance circulaire
```cpp
// Form.hpp veut utiliser Bureaucrat
// Bureaucrat.hpp veut utiliser Form
// → Inclusion circulaire !
```

### Solution : Forward Declaration
```cpp
// Form.hpp
class Bureaucrat;  // Forward declaration (pas #include)

class Form
{
    void beSigned(const Bureaucrat& bureaucrat);
};
```

```cpp
// Form.cpp
#include "Form.hpp"
#include "Bureaucrat.hpp"  // Include ici, dans le .cpp
```

### Quand utiliser ?
- **Forward declaration** : quand on utilise seulement des références ou pointeurs
- **#include** : quand on a besoin de la définition complète (accès aux membres)

---

## 3. Attributs const et Constructeur

```cpp
class Form
{
    private:
        const std::string   _name;           // const
        bool                _isSigned;       // modifiable
        const int           _gradeToSign;    // const
        const int           _gradeToExecute; // const
};
```

### Liste d'initialisation obligatoire pour const :
```cpp
Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name),                    // Initialisé ici
      _isSigned(false),               // false à la construction
      _gradeToSign(gradeToSign),      // Initialisé ici
      _gradeToExecute(gradeToExecute) // Initialisé ici
{
    // Validation après initialisation
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
}
```

---

## 4. Opérateur d'assignation avec attributs const

```cpp
Form& Form::operator=(const Form& other)
{
    if (this != &other)
    {
        // _name, _gradeToSign, _gradeToExecute sont const
        // On ne peut copier que _isSigned !
        _isSigned = other._isSigned;
    }
    return *this;
}
```

> **Note** : Avec des attributs const, l'opérateur d'assignation a un comportement limité.

---

## 5. Logique de signature

### Règle : grade 1 = meilleur, grade 150 = pire

```cpp
void Form::beSigned(const Bureaucrat& bureaucrat)
{
    // bureaucrat.getGrade() doit être <= _gradeToSign
    // Si grade = 30 et gradeToSign = 50 → OK (30 <= 50)
    // Si grade = 100 et gradeToSign = 50 → KO (100 > 50)
    
    if (bureaucrat.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}
```

### Visualisation :
```
Grade 1 ─────────────────────────────────> Grade 150
  MEILLEUR                                    PIRE
     ↑                    ↑
   Peut tout            Ne peut presque
   signer               rien signer
```

---

## 6. Pattern : Délégation avec gestion d'erreur

```cpp
void Bureaucrat::signForm(Form& form)
{
    try
    {
        form.beSigned(*this);  // Délègue au Form
        std::cout << _name << " signed " << form.getName() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << _name << " couldn't sign " << form.getName() 
                  << " because " << e.what() << std::endl;
    }
}
```

### Avantages :
- Le **Form** gère sa propre logique de validation
- Le **Bureaucrat** gère l'affichage du résultat
- L'exception est **attrapée et convertie** en message lisible

---

## 7. Surcharge de l'opérateur <<

```cpp
std::ostream& operator<<(std::ostream& os, const Form& form)
{
    os << "Form: " << form.getName()
       << ", Signed: " << (form.getIsSigned() ? "Yes" : "No")
       << ", Grade to sign: " << form.getGradeToSign()
       << ", Grade to execute: " << form.getGradeToExecute();
    return os;
}
```

### Usage :
```cpp
Form f("Contract", 50, 25);
std::cout << f << std::endl;
// Output: Form: Contract, Signed: No, Grade to sign: 50, Grade to execute: 25
```

---

## 8. Questions d'évaluation possibles

1. **Qu'est-ce qu'une forward declaration ?**
   > Une déclaration qui annonce l'existence d'une classe sans la définir. Utilisée pour éviter les inclusions circulaires.

2. **Pourquoi utiliser une référence const dans beSigned ?**
   > `const Bureaucrat&` : on ne modifie pas le bureaucrat, et on évite une copie.

3. **Que se passe-t-il si on essaie de signer un formulaire avec un grade insuffisant ?**
   > Une exception `Form::GradeTooLowException` est levée et attrapée par `signForm()`.

4. **Pourquoi le Form a deux grades différents ?**
   > Un pour signer (`gradeToSign`) et un pour exécuter (`gradeToExecute`). Un bureaucrate peut signer mais pas forcément exécuter.

5. **Comment fonctionne l'opérateur << ?**
   > C'est une fonction libre (non-membre) qui prend un ostream et l'objet, retourne l'ostream pour permettre le chaînage.

---

## 9. Diagramme de séquence

```
Bureaucrat              Form
    │                     │
    │  signForm(form)     │
    │─────────────────────>
    │                     │
    │  beSigned(*this)    │
    │────────────────────>│
    │                     │ Vérifie grade
    │                     │
    │    [grade OK]       │
    │<────────────────────│ _isSigned = true
    │                     │
    │  [ou exception]     │
    │<════════════════════│ throw GradeTooLowException
    │                     │
    │  Affiche résultat   │
    │                     │
```

---

## Résumé

| Concept | Description |
|---------|-------------|
| Forward Declaration | Déclare une classe sans l'inclure |
| Liste d'initialisation | Obligatoire pour les membres const |
| Délégation | Une classe délègue une action à une autre |
| Exception | Gestion des erreurs de grade |
| Opérateur << | Affichage personnalisé d'un objet |
