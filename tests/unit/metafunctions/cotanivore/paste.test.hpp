// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_COTANIVORE_UNIT_TESTS_TEST_PASTE_H
#define CONCEPTRODON_COTANIVORE_UNIT_TESTS_TEST_PASTE_H

#include <utility>

#include "conceptrodon/metafunctions/cotanivore/paste.hpp"
#include "conceptrodon/utilities/capsule.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"


namespace Conceptrodon {
namespace Cotanivore {
namespace UnitTests {
namespace TestPaste {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = std::tuple<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    Capsule<std::integral_constant<int,
#define SHEEP_SUFFIX    \
    >>
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(Paste<std::tuple<>, SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/


}}}}


#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif