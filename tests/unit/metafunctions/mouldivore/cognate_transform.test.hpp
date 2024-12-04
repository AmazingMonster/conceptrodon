// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_COGNATE_TRANSFORM_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_COGNATE_TRANSFORM_H

#include <utility>

#include "conceptrodon/descend/mouldivore/cognate_transform.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/double_sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestCognateTransform {




/******************************************************************************************************/
template<typename Integer>
struct IsEven
{
    static constexpr bool value {Integer::value % 2 == 0};
};

template<typename Integer>
struct IsPositive
{
    static constexpr bool value {Integer::value > 0};
};

template<typename Integer>
using PlusOne = std::integral_constant<int, Integer::value + 1>;

template<typename...Elements>
requires (sizeof...(Elements) == 240)
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    std::integral_constant<int,(
#define DOUBLE_SHEEP_MIDDLE \
    + 1) * 2 + 1>, std::integral_constant<int, (
#define DOUBLE_SHEEP_SUFFIX \
    + 1) * 2 + 1>
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

using SupposedResult = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    DOUBLE_SHEEP_SPROUT(119)
>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE
(
    CognateTransform<Operation>
    ::Road<IsEven, IsPositive>
    ::Road<PlusOne>
    ::Mold<SHEEP_SPROUT(240)>
);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/



}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_double_sheep.hpp"

#endif