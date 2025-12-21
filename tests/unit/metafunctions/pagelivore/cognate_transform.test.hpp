// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_COGNATE_TRANSFORM_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_COGNATE_TRANSFORM_H

#include <type_traits>
#include <utility>

#include "conceptrodon/metafunctions/pagelivore/cognate_transform.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/llama.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/fragmental/double_sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_llama.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestCognateTransform {




/******************************************************************************************************/
template<auto Integer>
struct IsEven
{
    static constexpr bool value {Integer % 2 == 0};
};


template<auto Integer>
struct IsPositive
{
    static constexpr bool value {Integer > 0};
};
/******************************************************************************************************/




/******************************************************************************************************/
template<auto GivenInteger>
struct PlusGivenInteger {
    template<auto Integer>
    struct ProtoPage
    {
        static constexpr auto value {Integer + GivenInteger};
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 240)
struct Operation {};
/******************************************************************************************************/



/**** One Transformation ****/
/**** Multiple Elements ****/
/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    (
#define DOUBLE_SHEEP_MIDDLE \
    + 1) * 2 + 1, (
#define DOUBLE_SHEEP_SUFFIX \
    + 1) * 2 + 1
#define DOUBLE_SHEEP_SEPARATOR  \
    ,


using SupposedResult = Operation
<
    0,
    1,
    DOUBLE_SHEEP_SPROUT(119)
>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE
(
    CognateTransform<Operation>
    ::Rail<IsEven, IsPositive>
    ::Rail<PlusGivenInteger<1>::Page>
    ::Page<SHEEP_SPROUT(240)>
);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/**** Multiple Transformation ****/
/**** Multiple Elements ****/
/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    (
#define DOUBLE_SHEEP_MIDDLE \
    + 1 ) * 2 * 2 + 1, (
#define DOUBLE_SHEEP_SUFFIX \
    + 1 ) * 2 + 1
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

using SupposedResult_1 = Operation
<
    0,
    1,
    DOUBLE_SHEEP_SPROUT(119)
>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define LLAMA_PREFIX \
    PlusGivenInteger< (
#define LLAMA_SUFFIX \
    + 1 ) >::Page
#define LLAMA_SEPARATOR  \
    ,

#define SUPPOSED_TYPE \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE
(
    CognateTransform<Operation>
    ::Rail<IsEven, IsPositive>
    ::Rail<LLAMA_SPROUT(240)>
    ::Page<SHEEP_SPROUT(240)>
);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE

#undef LLAMA_PREFIX
#undef LLAMA_SUFFIX
#undef LLAMA_SEPARATOR
/******************************************************************************************************/




/**** Multiple Transformation ****/
/**** One Element ****/
/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult_2 = Operation<SHEEP_SPROUT(240, + 2)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define LLAMA_PREFIX \
    PlusGivenInteger<
#define LLAMA_SUFFIX \
    >::Page
#define LLAMA_SEPARATOR  \
    ,

#define SUPPOSED_TYPE \
    SupposedResult_2

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE
(
    CognateTransform<Operation>
    ::Rail<IsEven, IsPositive>
    ::Rail<LLAMA_SPROUT(240)>
    ::Page<2>
);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE

#undef LLAMA_PREFIX
#undef LLAMA_SUFFIX
#undef LLAMA_SEPARATOR
/******************************************************************************************************/




/**** Multiple Transformation ****/
/**** One Element ****/
/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_zero_alkane.hpp"
using SupposedResult_3 = Operation<ALKANE_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_zero_alkane.hpp"

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define LLAMA_PREFIX \
    PlusGivenInteger<
#define LLAMA_SUFFIX \
    >::Page
#define LLAMA_SEPARATOR  \
    ,

#define SUPPOSED_TYPE \
    SupposedResult_3

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE
(
    CognateTransform<Operation>
    ::Rail<IsEven, IsPositive>
    ::Rail<LLAMA_SPROUT(240)>
    ::Page<0>
);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE

#undef LLAMA_PREFIX
#undef LLAMA_SUFFIX
#undef LLAMA_SEPARATOR
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_llama.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"
#include "macaron/fragmental/amenity/undef_double_sheep.hpp"

#endif