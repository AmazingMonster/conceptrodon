// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDVORE_UNIT_TESTS_TEST_COGNATE_REPEAT_H
#define CONCEPTRODON_MOULDVORE_UNIT_TESTS_TEST_COGNATE_REPEAT_H

#include <utility>

#include "conceptrodon/metafunctions/mouldivore/cognate_repeat.hpp"

#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestCognateRepeat {




/******************************************************************************************************/
template<typename...Elements>
requires (sizeof...(Elements) == 240 * 3)
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    int, float, double
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

SAME_TYPE(CognateRepeat<Operation>::Page<240>::Mold<int, float, double>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif