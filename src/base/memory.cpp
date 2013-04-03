#include "memory.h"

#include <string>
#include <iostream>
#include <sstream>
#include <boost/tokenizer.hpp>

// Allocate entire memory range (it's only 128 KiB)
MipsJunior::Base::Memory::Memory()
	: data(131072, 0) {
	return;
}

void MipsJunior::Base::Memory::Serialize(std::ostream& os) const {
	os << "v2.0 raw\n";

	os << std::hex;

	int seenZeros = 0;
	for(value_t em : data) {
		if(em == 0) {
			++seenZeros;
		}
		else {
			if(seenZeros > 1) {
				os << std::dec << seenZeros << "*0" << std::endl << std::hex;
			}
			else if(seenZeros == 1) {
				os << "00" << std::endl;
			}

			seenZeros = 0;
			os << em << std::endl;
		}
	}
}

void MipsJunior::Base::Memory::Deserialize(std::istream& is) {
	std::string magic;
	std::getline(is, magic);

	std::vector<value_t>::iterator jt = data.begin();

	boost::char_separator<char> delim; // Tokenize on whitespace

	std::stringstream cstrm;

	std::string buffer;
	while(std::getline(is, buffer)) {
		boost::tokenizer<boost::char_separator<char>> tokenizer(buffer, delim);

		auto kt = tokenizer.end();
		for(auto it = tokenizer.begin(); it != tokenizer.end(); ++it) {
			if(*it == "*") {
				++it;

				int num;
				cstrm << *kt;
				cstrm >> std::dec >> num;
				cstrm.clear();

				int value;
				cstrm << *it;
				cstrm >> std::hex >> value;
				cstrm.clear();

				for(int i = 0; i < num; ++i) {
					*jt = value;
					++jt;
				}

				kt = tokenizer.end();
			}
			else {
				if(kt != tokenizer.end()) {
					int value;
					cstrm << *kt;
					cstrm >> std::hex >> value;
					cstrm.clear();

					*jt = value;
					++jt;
				}

				kt = it;
			}
		}

		if(kt != tokenizer.end()) {
			int value;
			cstrm << *kt;
			cstrm >> std::hex >> value;
			cstrm.clear();

			*jt = value;
			++jt;
		}
	}

	for( ; jt != data.end(); ++jt) {
		*jt = 0;
	}

	return;
}
