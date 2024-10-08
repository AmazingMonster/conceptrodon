// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_FOLD_RIGHT_LAST_2ND_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_FOLD_RIGHT_LAST_2ND_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/pagelivore/fold_right_last.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "macaron/fragmental/sheep_reversed.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"
#include "macaron/fragmental/amenity/define_sheep_reversed.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestFoldRightLast2nd {




/******************************************************************************************************/
template<auto Left, auto Right>
struct BinaryOperation
{ static constexpr auto value = Left + Right; };

template<auto Left, auto Right>
requires (Right < Left)
struct BinaryOperation<Left, Right>
{ static constexpr auto value = 1; };

template<auto Left, auto Right>
static constexpr auto BinaryOperation_v = BinaryOperation<Left, Right>::type;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    1 + 239 * 240 / 2

#include "macaron/fragmental/amenity/instances/define_integer_sheep_reversed.hpp"
EQUAL_VALUE(FoldRightLast<BinaryOperation>::Page_v<SHEEP_REVERSED_SPROUT(240), 1>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep_reversed.hpp"

#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    1 + 7 * 8 / 2

#include "macaron/fragmental/amenity/instances/define_integer_sheep_reversed.hpp"
EQUAL_VALUE(FoldRightLast<BinaryOperation>::Page_v<SHEEP_REVERSED_SPROUT(8), 1>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep_reversed.hpp"

#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    1

#include "macaron/fragmental/amenity/instances/define_integer_sheep_reversed.hpp"
EQUAL_VALUE(FoldRightLast<BinaryOperation>::Page_v<SHEEP_REVERSED_SPROUT(1), 1>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep_reversed.hpp"

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"
#include "macaron/fragmental/amenity/undef_sheep_reversed.hpp"

#endif