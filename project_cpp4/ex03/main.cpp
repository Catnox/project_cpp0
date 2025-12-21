#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"

int main()
{
	std::cout << "=== Test du sujet ===" << std::endl;
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter* bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;

	std::cout << std::endl << "=== Tests supplementaires ===" << std::endl;

	// Test de copie profonde de Character
	std::cout << std::endl << "--- Test copie profonde Character ---" << std::endl;
	Character* original = new Character("original");
	original->equip(new Ice());
	original->equip(new Cure());

	Character* copy = new Character(*original);
	std::cout << "Original: " << original->getName() << std::endl;
	std::cout << "Copy: " << copy->getName() << std::endl;

	ICharacter* target = new Character("target");
	std::cout << "Original use:" << std::endl;
	original->use(0, *target);
	original->use(1, *target);
	std::cout << "Copy use:" << std::endl;
	copy->use(0, *target);
	copy->use(1, *target);
	std::cout << "\n--- Modification de l'original après copie ---" << std::endl;
	original->equip(new Ice());
	std::cout << "Original utilise la nouvelle Materia (slot 2):" << std::endl;
	original->use(2, *target);
	std::cout << "Copy tente d'utiliser le slot 2 (doit etre vide car copie profonde):" << std::endl;
	copy->use(2, *target);

	delete target;
	delete copy;
	delete original;

	// Test unequip (ne doit pas delete)
	std::cout << std::endl << "--- Test unequip ---" << std::endl;
	Character* unequipTest = new Character("unequipTest");
	AMateria* ice = new Ice();
	unequipTest->equip(ice);
	unequipTest->unequip(0);
	// ice est maintenant "par terre", on peut le reutiliser ou le delete manuellement
	unequipTest->equip(ice);
	unequipTest->unequip(0);
	delete ice;
	delete unequipTest;
	std::cout << "unequip OK (pas de double free)" << std::endl;

	// Test inventaire plein
	std::cout << std::endl << "--- Test inventaire plein ---" << std::endl;
	Character* fullInv = new Character("fullInv");
	fullInv->equip(new Ice());
	fullInv->equip(new Cure());
	fullInv->equip(new Ice());
	fullInv->equip(new Cure());
	AMateria* extra = new Ice();
	fullInv->equip(extra); // Devrait ne rien faire car inventaire plein
	delete extra; // On doit supprimer manuellement car pas equipe
	delete fullInv;
	std::cout << "Inventaire plein gere correctement" << std::endl;

	// Test use avec index invalide
	std::cout << std::endl << "--- Test use avec index invalide ---" << std::endl;
	Character* invalidTest = new Character("invalidTest");
	invalidTest->equip(new Ice());
	ICharacter* dummy = new Character("dummy");
	invalidTest->use(5, *dummy);   // Index hors limite
	invalidTest->use(-1, *dummy);  // Index negatif
	invalidTest->use(1, *dummy);   // Slot vide
	std::cout << "Aucun crash avec index invalide" << std::endl;
	delete dummy;
	delete invalidTest;

	return 0;
}