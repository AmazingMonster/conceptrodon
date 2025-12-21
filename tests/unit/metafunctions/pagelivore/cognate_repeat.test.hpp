// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_UNIT_TESTS_TEST_COGNATE_REPEAT_H
#define CONCEPTRODON_PAGELIVORE_UNIT_TESTS_TEST_COGNATE_REPEAT_H

#include <concepts>
#include <utility>
#include "conceptrodon/metafunctions/pagelivore/cognate_repeat.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestCognateRepeat {




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 240 * 3)
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    1, 2, 3
#define ALKANE_SUFFIX
#define ALKANE_SEPARATOR    \
    ,

using SupposedResult = Operation<ALKANE_SPROUT(240)>;

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX
#undef ALKANE_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

SAME_TYPE(CognateRepeat<Operation>::Page<240>::Page<1, 2, 3>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    1, 2, 3
#define ALKANE_SUFFIX
#define ALKANE_SEPARATOR    \
    ,

using SupposedIndexSequence = std::index_sequence<ALKANE_SPROUT(64)>;

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX
#undef ALKANE_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedIndexSequence

SAME_TYPE(CognateRepeat<std::index_sequence>::Page<64>::Page<1, 2, 3>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif