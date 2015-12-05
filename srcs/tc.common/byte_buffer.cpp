#include "stdafx.h"
#include "byte_buffer.hpp"

namespace tc {
namespace buffer {

position::position(void) 
	: read(0), write(0) {}

position::position(const position& rhs) 
	: read(rhs.read), write(rhs.write) {}

position& position::operator=(const position& rhs) {
	read = rhs.read;
	write = rhs.write;
	return *this;
}

void position::swap( position& rhs) {
	std::swap(read, rhs.read);
	std::swap(write, rhs.write);
}

}
}