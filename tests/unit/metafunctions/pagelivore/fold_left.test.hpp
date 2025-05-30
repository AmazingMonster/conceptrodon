// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_FOLD_LEFT_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_FOLD_LEFT_H

#include <utility>

#include "conceptrodon/pagelivore/fold_left.hpp"

#include "macaron/judgmental/equal_value.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestCognateFoldLeft {




/******************************************************************************************************/
template<auto Left, auto Right>
struct BinaryOperation
{ static constexpr auto value {Left + Right}; };

template<auto Left, auto Right>
requires (Left < Right)
struct BinaryOperation<Left, Right>
{ static constexpr auto value {Left}; };
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    1 + 239 * 240 / 2

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
EQUAL_VALUE(FoldLeft<BinaryOperation>::Page<1>::Page_v<SHEEP_SPROUT(240)>);
EQUAL_VALUE(FoldLeft<BinaryOperation>::Page<1>::Page<SHEEP_SPROUT(240)>::value);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    -1

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
EQUAL_VALUE(FoldLeft<BinaryOperation>::Page<-1>::Page_v<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    1 + 7 * 8 / 2

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
EQUAL_VALUE(FoldLeft<BinaryOperation>::Page<1>::Page_v<SHEEP_SPROUT(8)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif