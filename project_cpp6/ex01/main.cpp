#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main()
{
	std::cout << "=== Serializer Test ===" << std::endl << std::endl;

	// Create a Data object
	Data original;
	original.id = 42;
	original.name = "Test Data";
	original.value = 3.14159;

	std::cout << "Original Data:" << std::endl;
	std::cout << "  Address: " << &original << std::endl;
	std::cout << "  id:      " << original.id << std::endl;
	std::cout << "  name:    " << original.name << std::endl;
	std::cout << "  value:   " << original.value << std::endl;
	std::cout << std::endl;

	// Serialize: pointer -> uintptr_t
	uintptr_t serialized = Serializer::serialize(&original);
	std::cout << "Serialized (uintptr_t): " << serialized << std::endl;
	std::cout << std::endl;

	// Deserialize: uintptr_t -> pointer
	Data* deserialized = Serializer::deserialize(serialized);

	std::cout << "Deserialized Data:" << std::endl;
	std::cout << "  Address: " << deserialized << std::endl;
	std::cout << "  id:      " << deserialized->id << std::endl;
	std::cout << "  name:    " << deserialized->name << std::endl;
	std::cout << "  value:   " << deserialized->value << std::endl;
	std::cout << std::endl;

	// Verify pointers are equal
	std::cout << "=== Verification ===" << std::endl;
	if (deserialized == &original)
	{
		std::cout << "SUCCESS: deserialized pointer == original pointer" << std::endl;
	}
	else
	{
		std::cout << "FAILURE: pointers are different!" << std::endl;
	}

	// Additional test with heap-allocated Data
	std::cout << std::endl << "=== Test with heap-allocated Data ===" << std::endl;
	
	Data* heapData = new Data;
	heapData->id = 100;
	heapData->name = "Heap Data";
	heapData->value = 2.71828;

	std::cout << "Original heap pointer: " << heapData << std::endl;
	
	uintptr_t heapSerialized = Serializer::serialize(heapData);
	std::cout << "Serialized: " << heapSerialized << std::endl;
	
	Data* heapDeserialized = Serializer::deserialize(heapSerialized);
	std::cout << "Deserialized pointer: " << heapDeserialized << std::endl;

	if (heapDeserialized == heapData)
	{
		std::cout << "SUCCESS: heap pointers match!" << std::endl;
		std::cout << "  Accessing data: id=" << heapDeserialized->id 
				  << ", name=" << heapDeserialized->name << std::endl;
	}
	else
	{
		std::cout << "FAILURE: heap pointers don't match!" << std::endl;
	}

	delete heapData;

	return 0;
}
