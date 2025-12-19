# Exercice 00 : Exceptions en C++

## Concept clé : Les Exceptions

Les **exceptions** sont un mécanisme de gestion des erreurs en C++ qui permet de séparer le code de traitement normal du code de gestion des erreurs.

---

## 1. Pourquoi les exceptions ?

### Sans exceptions (style C) :
```cpp
int createBureaucrat(int grade) {
    if (grade < 1 || grade > 150)
        return -1;  // Code d'erreur
    // ...
}

// Appel :
if (createBureaucrat(200) == -1) {
    // Gérer l'erreur
}
```

### Avec exceptions (style C++) :
```cpp
Bureaucrat::Bureaucrat(int grade) {
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}

// Appel :
try {
    Bureaucrat b("Bob", 200);
} catch (std::exception& e) {
    std::cout << e.what() << std::endl;
}
```

---

## 2. Structure try/catch/throw

```cpp
try {
    // Code susceptible de lever une exception
    throw MonException();  // Lève une exception
}
catch (MonException& e) {
    // Gère spécifiquement MonException
}
catch (std::exception& e) {
    // Gère toute exception héritant de std::exception
}
```

---

## 3. Créer une classe d'exception personnalisée

```cpp
class GradeTooHighException : public std::exception
{
    public:
        virtual const char* what() const throw();
};

const char* GradeTooHighException::what() const throw()
{
    return "Grade is too high!";
}
```

### Éléments importants :
- **Hérite de `std::exception`** : permet d'être attrapée par `catch (std::exception& e)`
- **Méthode `what()`** : retourne un message décrivant l'erreur
- **`const throw()`** : spécification C++98 indiquant que `what()` ne lève pas d'exception

---

## 4. Classes d'exception imbriquées

Dans cet exercice, les exceptions sont **imbriquées dans la classe Bureaucrat** :

```cpp
class Bureaucrat
{
    public:
        class GradeTooHighException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };
        
        class GradeTooLowException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };
};
```

### Avantages :
- **Encapsulation** : les exceptions sont liées à leur classe
- **Clarté** : `Bureaucrat::GradeTooHighException` est explicite
- **Pas de pollution** : n'encombre pas l'espace de noms global

---

## 5. Orthodox Canonical Form (OCF)

Rappel : toute classe (sauf exceptions) doit avoir :

```cpp
class Bureaucrat
{
    public:
        Bureaucrat();                                // Constructeur par défaut
        Bureaucrat(const Bureaucrat& other);         // Constructeur de copie
        Bureaucrat& operator=(const Bureaucrat& other); // Opérateur d'assignation
        ~Bureaucrat();                               // Destructeur
};
```

### Note importante :
> **Les classes d'exception n'ont PAS besoin de suivre l'OCF** selon le sujet.

---

## 6. Attribut const et constructeur

```cpp
class Bureaucrat
{
    private:
        const std::string _name;  // const !
        int _grade;
};
```

Un attribut `const` doit être initialisé dans la **liste d'initialisation** :

```cpp
Bureaucrat::Bureaucrat(const std::string& name, int grade) 
    : _name(name), _grade(grade)  // Initialisation avant le corps
{
    // Validation ici
}
```

---

## 7. Questions d'évaluation possibles

1. **Qu'est-ce qu'une exception ?**
   > Un mécanisme de gestion d'erreurs qui "lance" un objet quand une erreur survient, permettant au code appelant de le "rattraper".

2. **Pourquoi hériter de std::exception ?**
   > Pour pouvoir attraper toutes les exceptions avec `catch (std::exception& e)` et avoir accès à la méthode `what()`.

3. **Que signifie `throw()` après une fonction ?**
   > C'est une spécification d'exception (C++98) indiquant que la fonction ne lève aucune exception.

4. **Pourquoi les exceptions sont-elles imbriquées dans la classe ?**
   > Pour l'encapsulation et la clarté : `Bureaucrat::GradeTooHighException` est plus explicite que `GradeTooHighException`.

5. **Pourquoi `_name` est const ?**
   > Le nom d'un bureaucrate ne doit pas changer après sa création.

---

## 8. Flux d'exécution avec exceptions

```
main()
  └─> try {
        └─> Bureaucrat b("Bob", 0);
              └─> if (grade < 1) throw GradeTooHighException();
                    │
                    │ Exception levée !
                    │ Le reste du constructeur n'est PAS exécuté
                    │ L'objet n'est PAS créé
                    ▼
      } catch (std::exception& e) {
              └─> e.what() → "Grade is too high!"
      }
```

---

## Résumé

| Concept | Description |
|---------|-------------|
| `throw` | Lance une exception |
| `try` | Bloc où les exceptions peuvent survenir |
| `catch` | Attrape et gère une exception |
| `what()` | Retourne le message d'erreur |
| `std::exception` | Classe de base pour toutes les exceptions standard |
