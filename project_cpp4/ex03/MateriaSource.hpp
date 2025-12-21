#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include "IMateriaSource.hpp"
# include "AMateria.hpp"

class MateriaSource : public IMateriaSource
{
private:
	AMateria*	_templates[4];

public:
	// Canonical form
	MateriaSource();
	MateriaSource(MateriaSource const & other);
	MateriaSource & operator=(MateriaSource const & other);
	virtual ~MateriaSource();
	// Member functions
	virtual void learnMateria(AMateria* m);
	virtual AMateria* createMateria(std::string const & type);
};

#endif
