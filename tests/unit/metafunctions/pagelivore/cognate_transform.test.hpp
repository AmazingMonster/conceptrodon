// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_COGNATE_TRANSFORM_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_COGNATE_TRANSFORM_H

#include <utility>

#include "conceptrodon/pagelivore/cognate_transform.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/double_sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestCognateTransform {




/******************************************************************************************************/
template<auto Integer>
struct IsEven
{
    static constexpr bool value {Integer % 2 == 0};
};

template<auto Integer>
struct IsPositive
{
    static constexpr bool value {Integer > 0};
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
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    (
#define DOUBLE_SHEEP_MIDDLE \
    + 1) * 2 + 1, (
#define DOUBLE_SHEEP_SUFFIX \
    + 1) * 2 + 1
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

using SupposedResult = Operation<0, 1, DOUBLE_SHEEP_SPROUT(119)>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE
(
    CognateTransform<Operation>
    ::Rail<IsEven, IsPositive>
    ::Rail<PlusOne>
    ::Page<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_double_sheep.hpp"

#endif