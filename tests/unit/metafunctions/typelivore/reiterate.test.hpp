// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_REITERATE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_REITERATE_H

#include <concepts>

#include "conceptrodon/typelivore/reiterate.hpp"

#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestReiterate {




/******************************************************************************************************/
#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    int, float, double
#define ALKANE_SUFFIX
#define ALKANE_SEPARATOR    \
    ,

using SupposedResult = Capsule<ALKANE_SPROUT(240)>;

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX
#undef ALKANE_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

SAME_TYPE(Reiterate<int, float, double>::Page<240>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif