#ifndef LIBOSU_INCLUDE_EXCEPTIONS_HPP
#define LIBOSU_INCLUDE_EXCEPTIONS_HPP

#include <iostream>

namespace osu {
	const std::out_of_range POS_OUT_OF_RANGE = std::out_of_range("Position is out of range!");
	const std::logic_error IS_NOT_STRING = std::logic_error("Could not read string!");
}

#endif