// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_KINDRED_FOLD_LEFT_FIRST_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_KINDRED_FOLD_LEFT_FIRST_H

#include <utility>

#include "conceptrodon/typelivore/kindred_fold_left_first.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestKindredFoldLeftFirst {




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
    KindredFoldLeftFirst<std::integral_constant<int, 1>, SHEEP_SPROUT(240)>
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
    KindredFoldLeftFirst<std::integral_constant<int, -1>, SHEEP_SPROUT(240)>
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
    KindredFoldLeftFirst<std::integral_constant<int, 1>, SHEEP_SPROUT(8)>
    ::UniRoad<BinaryOperation_t>
);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif