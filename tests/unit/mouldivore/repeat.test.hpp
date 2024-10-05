// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_TEST_REPEAT_H
#define CONCEPTRODON_MOULDIVORE_TEST_REPEAT_H

#include <concepts>
#include <tuple>
#include "conceptrodon/descend/mouldivore/repeat.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace TestRepeat {




/******************************************************************************************************/
template<typename...Elements>
requires (sizeof...(Elements) == 240 * 3)
struct Tester {};
/******************************************************************************************************/




/******************************************************************************************************/
#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    int, float, double
#define ALKANE_SUFFIX
#define ALKANE_SEPARATOR    \
    ,

using SupposedResult = Tester<ALKANE_SPROUT(240)>;

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX
#undef ALKANE_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

SAME_TYPE(Repeat<Tester>::Page<240>::Mold<int, float, double>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    int, float, double
#define ALKANE_SUFFIX
#define ALKANE_SEPARATOR    \
    ,

using SupposedTuple = std::tuple<ALKANE_SPROUT(64)>;

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX
#undef ALKANE_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedTuple

SAME_TYPE(Repeat<std::tuple>::Page<64>::Mold<int, float, double>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif