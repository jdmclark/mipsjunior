#pragma once

#ifdef WIN32
namespace MipsJunior {
namespace Base {

typedef unsigned __int16 address_t;
typedef __int16 value_t;
typedef unsigned __int16 unsigned_value_t;

}
}
#else

#include <stdint.h>
#include <stddef.h>
namespace MipsJunior {
namespace Base {

typedef uint16_t address_t;
typedef int16_t value_t;
typedef uint16_t unsigned_value_t;

}
}
#endif
