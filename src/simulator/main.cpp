#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>

#include "base/memory.h"
#include "base/virtualmachine.h"

void printHelpMessage() {
	std::cout << "\nMIPS Junior Simulator\n\n";
	std::cout << "Usage: Simulator [input] [iterations]\n\n";
	std::cout << "Options: \n";
	std::cout << "input - The input hex file, in Logisim v2.0 raw format.\n";
	std::cout << "iterations - The number of instructions to execute before halting.\n\n";
}

int main(int argc, char** argv) {
	try {
		if(argc != 3) {
			printHelpMessage();
			return 1;
		}

		size_t n_iterations = boost::lexical_cast<size_t, char*>(argv[2]);

		std::ifstream str(argv[1]);

		MipsJunior::Base::Memory imemory;
		imemory.Deserialize(str);

		str.close();

		MipsJunior::Base::Memory dmemory;

		MipsJunior::Base::VirtualMachine vm(imemory, dmemory, std::cout);

		vm.Execute(n_iterations);

		std::cout << "\nDone" << std::endl;
	}
	catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		printHelpMessage();
		return 1;
	}
}
