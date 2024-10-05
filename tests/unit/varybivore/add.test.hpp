#ifndef CONCEPTRODON_VARYBIVORE_TEST_ADD_H
#define CONCEPTRODON_VARYBIVORE_TEST_ADD_H

#include <concepts>
#include "conceptrodon/varybivore/add.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestAdd {




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    2

EQUAL_VALUE(Add_v<1, 1>);
EQUAL_VALUE(Add_v<1, 1.0>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    2.0

EQUAL_VALUE(AddTo<1>::Page_v<1>);
EQUAL_VALUE(AddTo<1>::Page_v<1.0>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif