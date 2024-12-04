// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_DUPLICATE_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_DUPLICATE_H

#include "conceptrodon/typelivore/duplicate.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/alkane.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestDuplicate {




/******************************************************************************************************/
template<typename...Args>
requires (sizeof...(Args) == 240)
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    int
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

SAME_TYPE(Duplicate<int>::Page<240>::UniRoad<Operation>);
SAME_TYPE(Duplicate<int>::Page<240>::Road<Operation>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif