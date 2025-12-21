// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_TYPICAL_REITERATE_H
#define CONCEPTRODON_VARYBIVORE_UNIT_TESTS_TEST_TYPICAL_REITERATE_H

#include "conceptrodon/metafunctions/varybivore/typical_reiterate.hpp"

#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestTypicalReiterate {




/******************************************************************************************************/
#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    1, 2, 3
#define ALKANE_SUFFIX
#define ALKANE_SEPARATOR    \
    ,

using SupposedResult = Shuttle<ALKANE_SPROUT(240)>;

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX
#undef ALKANE_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

SAME_TYPE(TypicalReiterate<1, 2, 3>::Page<240>::type);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif