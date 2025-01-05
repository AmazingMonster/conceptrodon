// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_REITERATE_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_REITERATE_H

#include "conceptrodon/varybivore/reiterate.hpp"

#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestReiterate {




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

SAME_TYPE(Reiterate<1, 2, 3>::Page<240>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif