// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_KINDRED_FOLD_LEFT_H
#define CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_KINDRED_FOLD_LEFT_H

#include <utility>

#include "conceptrodon/metafunctions/typelivore/kindred_fold_left.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestKindredFoldLeft {




/******************************************************************************************************/
template<typename Left, typename Right>
struct BinaryOperation
{ using type = std::integral_constant<int, Left::value + Right::value>; };

template<typename Left, typename Right>
requires (Left::value < Right::value)
struct BinaryOperation<Left, Right>
{ using type = std::integral_constant<int, Left::value>; };

template<typename Left, typename Right>
using BinaryOperation_t = BinaryOperation<Left, Right>::type;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    std::integral_constant<int, 1 + 239 * 240 / 2>

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE
(
    KindredFoldLeft<SHEEP_SPROUT(240)>
    ::Mold<std::integral_constant<int, 1>>
    ::Road<BinaryOperation_t>
);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    std::integral_constant<int, -1>

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE
(
    KindredFoldLeft<SHEEP_SPROUT(240)>
    ::Mold<std::integral_constant<int, -1>>
    ::Road<BinaryOperation_t>
);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    std::integral_constant<int, 1 + 7 * 8 / 2>
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE
(
    KindredFoldLeft<SHEEP_SPROUT(8)>
    ::Mold<std::integral_constant<int, 1>>
    ::Road<BinaryOperation_t>
);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif