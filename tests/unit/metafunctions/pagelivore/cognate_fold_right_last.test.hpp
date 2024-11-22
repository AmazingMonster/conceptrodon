// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_COGNATE_FOLD_RIGHT_LAST_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_COGNATE_FOLD_RIGHT_LAST_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/pagelivore/cognate_fold_right_last.hpp"
#include "macaron/judgmental/equal_value.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestFoldRightLast {




/******************************************************************************************************/
template<auto Left, auto Right>
struct BinaryOperation
{ static constexpr auto value = Left + Right; };

template<auto Left, auto Right>
requires (Left < Right)
struct BinaryOperation<Left, Right>
{ static constexpr auto value = 1; };

template<auto Left, auto Right>
static constexpr auto BinaryOperation_v = BinaryOperation<Left, Right>::type;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    2

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
EQUAL_VALUE(CognateFoldRightLast<BinaryOperation>::Page_v<1, SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    2

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
EQUAL_VALUE(CognateFoldRightLast<BinaryOperation>::Page_v<1, SHEEP_SPROUT(8)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    1

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
EQUAL_VALUE(CognateFoldRightLast<BinaryOperation>::Page_v<1, SHEEP_SPROUT(1)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif