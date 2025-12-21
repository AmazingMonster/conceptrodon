// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_DUPLICATE_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_DUPLICATE_H

#include "conceptrodon/metafunctions/varybivore/duplicate.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/alkane.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestDuplicate {




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 240)
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_zero_alkane.hpp"
using SupposedResult = Operation<ALKANE_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_zero_alkane.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

SAME_TYPE(Duplicate<0>::Page<240>::UniRail<Operation>);
SAME_TYPE(Duplicate<0>::Page<240>::Rail<Operation>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif