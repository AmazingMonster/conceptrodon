// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_KINDRED_FIND_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_KINDRED_FIND_H

#include <concepts>
#include "conceptrodon/typelivore/kindred_find.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/typelivore/is_same_as.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestKindred_Find {




/******************************************************************************************************/
template<auto I>
struct AreNoGreaterThan
{
    template<typename...Args>
    using Mold = std::bool_constant<(...&&(Args::value <= I))>;
};


template<auto I>
struct AreNoLessThan
{
    template<typename...Args>
    using Mold = std::bool_constant<(...&&(Args::value >= I))>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
template<int I>
constexpr auto Found = KindredFind<SHEEP_SPROUT(120)>
::Road_v<AreNoGreaterThan<I>::template Mold, AreNoLessThan<I>::template Mold>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = SignedArk<SHEEP_SPROUT(120)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#define SHEEP_PREFIX    \
    Found <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,
    
SAME_TYPE(Shuttle<SHEEP_SPROUT(120)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
template<int I>
constexpr auto FailFound = KindredFind<SHEEP_SPROUT(120), std::integral_constant<int, I>>
::template Road_v<AreNoGreaterThan<-1>::template Mold, AreNoLessThan<-1>::template Mold>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_negative_one_alkane.hpp"
using SupposedFailedResult = SignedArk<ALKANE_SPROUT(120)>;
#include "macaron/fragmental/amenity/instances/undef_integer_negative_one_alkane.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedFailedResult

#define SHEEP_PREFIX    \
    FailFound <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,
    
SAME_TYPE(Shuttle<SHEEP_SPROUT(120)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/fragmental/amenity/undef_alkane.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif