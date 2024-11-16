// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_MODIFY_VARIABLES_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_MODIFY_VARIABLES_H

#include <type_traits>
#include <concepts>
#include "conceptrodon/descend/omennivore/modify_variables.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/double_sheep.hpp"
#include "macaron/fragmental/alkane.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestModifyVariables {




/******************************************************************************************************/
template<auto Integer>
struct PlusOne
{
    static constexpr auto value {Integer + 1};
};
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX
#define DOUBLE_SHEEP_MIDDLE \
    * 2 + 1,
#define DOUBLE_SHEEP_SUFFIX \
    * 2 + 1
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

using SupposedResult = Shuttle<DOUBLE_SHEEP_SPROUT(120)>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    std::make_index_sequence<1>
#define ALKANE_SUFFIX   
#define ALKANE_SEPARATOR    \
    ,

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE
(
    ModifyVariables<std::make_index_sequence<0>, ALKANE_SPROUT(119)>
    ::Rail<PlusOne>
    ::Page<SHEEP_SPROUT(240)>
);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX   
#undef ALKANE_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_double_sheep.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

}}}}

#endif