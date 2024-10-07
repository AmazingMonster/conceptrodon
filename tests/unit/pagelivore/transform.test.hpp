// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_TRANSFORM_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_TRANSFORM_H

#include <type_traits>
#include <concepts>
#include "conceptrodon/descend/pagelivore/transform.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/double_sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace TestTransform {




/******************************************************************************************************/
template<auto Integer>
struct IsEven
{
    static constexpr bool value {Integer % 2 == 0};
};
/******************************************************************************************************/




/******************************************************************************************************/
template<auto Integer>
struct PlusOne
{
    static constexpr auto value {Integer + 1};
};
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 240)
struct Tester {};
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX
#define DOUBLE_SHEEP_MIDDLE \
    * 2 + 1, 
#define DOUBLE_SHEEP_SUFFIX \
    * 2 + 1
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

using SupposedResult = Tester<DOUBLE_SHEEP_SPROUT(120)>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Transform<Tester>::Rail<IsEven>::Rail<PlusOne>::Page<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_double_sheep.hpp"

}}}

#endif