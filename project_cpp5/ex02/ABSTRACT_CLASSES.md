# Exercice 02 : Classes Abstraites et Héritage

## Concepts clés : Abstraction, Polymorphisme et Héritage

---

## 1. Classe Abstraite (AForm)

Une **classe abstraite** est une classe qui ne peut pas être instanciée directement.

### Définition :
```cpp
class AForm  // Préfixe 'A' pour Abstract
{
    public:
        // Fonction virtuelle pure = rend la classe abstraite
        virtual void executeAction() const = 0;
};
```

### Caractéristiques :
- Contient au moins une **fonction virtuelle pure** (`= 0`)
- **Ne peut pas être instanciée** : `AForm f;` → Erreur !
- Sert de **contrat** pour les classes dérivées

---

## 2. Fonction Virtuelle Pure

```cpp
virtual void executeAction() const = 0;
//                               ^^^
//                               Syntaxe "= 0" = pure
```

### Signification :
- Pas d'implémentation dans la classe de base
- **Oblige** les classes dérivées à l'implémenter
- Rend la classe abstraite

---

## 3. Hiérarchie des classes

```
                    ┌─────────────────┐
                    │     AForm       │ (abstraite)
                    │  executeAction()│ = 0
                    └────────┬────────┘
                             │
        ┌────────────────────┼────────────────────┐
        │                    │                    │
        ▼                    ▼                    ▼
┌───────────────┐   ┌───────────────┐   ┌───────────────┐
│  Shrubbery    │   │   Robotomy    │   │ Presidential  │
│ CreationForm  │   │  RequestForm  │   │  PardonForm   │
└───────────────┘   └───────────────┘   └───────────────┘
```

---

## 4. Implémentation dans les classes dérivées

### Classe de base (AForm) :
```cpp
class AForm
{
    public:
        void execute(Bureaucrat const& executor) const;  // Non virtuelle
        virtual void executeAction() const = 0;          // Virtuelle pure
};

void AForm::execute(Bureaucrat const& executor) const
{
    if (!_isSigned)
        throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
    executeAction();  // Appel polymorphique
}
```

### Classe dérivée (ShrubberyCreationForm) :
```cpp
class ShrubberyCreationForm : public AForm
{
    public:
        virtual void executeAction() const;  // Implémentation obligatoire
};

void ShrubberyCreationForm::executeAction() const
{
    // Crée un fichier avec des arbres ASCII
    std::ofstream file((_target + "_shrubbery").c_str());
    file << "ASCII trees..." << std::endl;
}
```

---

## 5. Pattern Template Method

La méthode `execute()` dans AForm utilise le **pattern Template Method** :

```cpp
void AForm::execute(Bureaucrat const& executor) const
{
    // 1. Vérifications communes (dans la classe de base)
    if (!_isSigned)
        throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
    
    // 2. Action spécifique (déléguée aux classes dérivées)
    executeAction();  // Polymorphisme !
}
```

### Avantages :
- **DRY** (Don't Repeat Yourself) : validations centralisées
- **Extensibilité** : nouvelles formes sans modifier AForm
- **Sécurité** : impossible d'oublier les vérifications

---

## 6. Constructeurs et Héritage

```cpp
// Classe dérivée appelle le constructeur de la classe de base
ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", 145, 137),  // Appel constructeur parent
      _target(target)                             // Initialisation membre propre
{
}
```

### Ordre d'appel des constructeurs :
1. Constructeur de la classe de base (AForm)
2. Constructeur de la classe dérivée (ShrubberyCreationForm)

### Ordre d'appel des destructeurs (inverse) :
1. Destructeur de la classe dérivée
2. Destructeur de la classe de base

---

## 7. Destructeur Virtuel

```cpp
class AForm
{
    public:
        virtual ~AForm();  // IMPORTANT : virtuel !
};
```

### Pourquoi virtuel ?
```cpp
AForm* form = new ShrubberyCreationForm("garden");
delete form;  // Sans virtual ~AForm(), seul ~AForm() est appelé !
              // Avec virtual, ~ShrubberyCreationForm() puis ~AForm()
```

> **Règle** : Si une classe a des fonctions virtuelles, son destructeur doit être virtuel.

---

## 8. Les trois formulaires concrets

| Formulaire | Sign Grade | Exec Grade | Action |
|------------|------------|------------|--------|
| ShrubberyCreationForm | 145 | 137 | Crée fichier `<target>_shrubbery` avec arbres ASCII |
| RobotomyRequestForm | 72 | 45 | Bruit de perceuse + 50% succès robotomisation |
| PresidentialPardonForm | 25 | 5 | Annonce pardon par Zaphod Beeblebrox |

---

## 9. Polymorphisme en action

```cpp
void Bureaucrat::executeForm(AForm const& form) const
{
    try
    {
        form.execute(*this);  // Appel polymorphique
        // execute() → vérifie → appelle executeAction()
        // executeAction() est celle de la classe RÉELLE de form
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
```

### Exemple :
```cpp
AForm* form = new RobotomyRequestForm("Bender");
bureaucrat.executeForm(*form);
// → Appelle RobotomyRequestForm::executeAction()
// → "DRILLING NOISES... Bender has been robotomized!"
```

---

## 10. Questions d'évaluation possibles

1. **Qu'est-ce qu'une classe abstraite ?**
   > Une classe qui contient au moins une fonction virtuelle pure et ne peut pas être instanciée.

2. **Qu'est-ce qu'une fonction virtuelle pure ?**
   > Une fonction déclarée avec `= 0`, sans implémentation dans la classe de base, que les classes dérivées doivent obligatoirement implémenter.

3. **Pourquoi renommer Form en AForm ?**
   > Le préfixe 'A' indique que c'est une classe abstraite. Convention de nommage pour la clarté.

4. **Pourquoi execute() n'est pas virtuelle pure ?**
   > Parce qu'elle contient la logique commune (vérifications). Seule executeAction() est spécifique à chaque formulaire.

5. **Pourquoi le destructeur doit être virtuel ?**
   > Pour que `delete` sur un pointeur de base appelle le bon destructeur de la classe dérivée.

6. **Qu'est-ce que le pattern Template Method ?**
   > Un pattern où la classe de base définit le squelette d'un algorithme, et les classes dérivées implémentent certaines étapes.

---

## 11. Flux d'exécution

```
bureaucrat.executeForm(shrubForm)
    │
    ▼
AForm::execute(executor)
    │
    ├─ Vérifie: form signée? ──────> Non: throw FormNotSignedException
    │
    ├─ Vérifie: grade suffisant? ──> Non: throw GradeTooLowException
    │
    └─ executeAction() ◄─────────── Polymorphisme
           │
           ▼
    ShrubberyCreationForm::executeAction()
           │
           └─> Crée fichier avec arbres ASCII
```

---

## Résumé

| Concept | Description |
|---------|-------------|
| Classe abstraite | Classe avec `= 0`, non instanciable |
| Fonction virtuelle pure | `virtual void f() = 0;` |
| Template Method | Squelette dans base, détails dans dérivées |
| Polymorphisme | Appel de la bonne méthode selon le type réel |
| Destructeur virtuel | Obligatoire si fonctions virtuelles |
