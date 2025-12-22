# Bitcoin Exchange - Ex00

## Concept : std::map et Recherche par Date

Cet exercice utilise `std::map` pour stocker et rechercher efficacement des taux de change Bitcoin par date.

## Pourquoi std::map ?

```cpp
std::map<std::string, double> _database;
```

| Caractéristique | Avantage |
|-----------------|----------|
| Clés triées | Les dates sont automatiquement ordonnées |
| Recherche O(log n) | Efficace pour trouver une date |
| `lower_bound` | Trouve la date inférieure la plus proche |

## Fonctionnement de lower_bound

Le sujet demande : "si la date n'existe pas, utiliser la date inférieure la plus proche".

```cpp
double BitcoinExchange::getExchangeRate(std::string const &date) const
{
    // Chercher la date exacte
    std::map<std::string, double>::const_iterator it = _database.find(date);
    if (it != _database.end())
        return it->second;  // Date trouvée

    // Sinon, trouver la date inférieure la plus proche
    it = _database.lower_bound(date);  // Premier élément >= date
    if (it == _database.begin())
        return -1;  // Pas de date antérieure
    --it;  // Reculer d'un élément
    return it->second;
}
```

### Exemple visuel

```
Database: 2011-01-01, 2011-01-05, 2011-01-10
Recherche: 2011-01-07

lower_bound(2011-01-07) -> pointe vers 2011-01-10 (premier >= 2011-01-07)
--it -> pointe vers 2011-01-05 (date inférieure la plus proche)
```

## Validation des données

### Format de date (YYYY-MM-DD)

```cpp
bool BitcoinExchange::isValidDate(std::string const &date) const
{
    // Vérifier la longueur (10 caractères)
    if (date.length() != 10) return false;
    
    // Vérifier les tirets aux bonnes positions
    if (date[4] != '-' || date[7] != '-') return false;
    
    // Vérifier que le reste sont des chiffres
    // Vérifier les limites (mois 1-12, jour 1-31)
    // Vérifier les jours par mois et années bissextiles
}
```

### Validation de la valeur

- Doit être un nombre (float ou int)
- Doit être positif (>= 0)
- Doit être <= 1000

## Parsing du fichier CSV

```cpp
void BitcoinExchange::loadDatabase(std::string const &filename)
{
    std::ifstream file(filename.c_str());
    std::string line;
    
    std::getline(file, line);  // Skip header
    
    while (std::getline(file, line))
    {
        size_t commaPos = line.find(',');
        std::string date = line.substr(0, commaPos);
        std::string rate = line.substr(commaPos + 1);
        
        _database[date] = std::strtod(rate.c_str(), NULL);
    }
}
```

## Parsing du fichier d'entrée

Format attendu : `date | value`

```cpp
size_t pipePos = line.find(" | ");
std::string date = line.substr(0, pipePos);
std::string value = line.substr(pipePos + 3);
```

## Messages d'erreur

| Erreur | Message |
|--------|---------|
| Valeur négative | `Error: not a positive number.` |
| Valeur > 1000 | `Error: too large a number.` |
| Format invalide | `Error: bad input => <ligne>` |
| Fichier introuvable | `Error: could not open file.` |

## Sortie attendue

```
2011-01-03 => 3 = 0.9
```
= date => quantité = quantité × taux_du_jour

## Container utilisé

✅ **std::map** - Ne peut plus être utilisé dans les exercices suivants
