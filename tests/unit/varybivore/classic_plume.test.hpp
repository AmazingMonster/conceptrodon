// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_CLASSIC_PLUME_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_CLASSIC_PLUME_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/varybivore/classic_plume.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/llama.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_llama.hpp"


namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestClassicPlume {




/******************************************************************************************************/
template<auto I>
struct Dummy
{
    template<auto V>
    struct ProtoPage
    {
        using type = std::integral_constant<int, I + V>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
/******************************************************************************************************/

// In this example,
// we will place
//  0, ..., 239
// into
//  Dummy<0>::Page,
//  ...,
//  Dummy<239>::Page.
// The result will be collected in a Capsule.

/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Capsule<SHEEP_SPROUT(240, *2)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    Dummy<
#define SHEEP_SUFFIX    \
    >::Page
#define SHEEP_SEPARATOR \
    ,

#include "macaron/fragmental/amenity/instances/define_integer_llama.hpp"
SAME_TYPE(ClassicPlume<LLAMA_SPROUT(240)>::Rail<SHEEP_SPROUT(240)>::Road<Capsule>);
SAME_TYPE(ClassicPlume<LLAMA_SPROUT(240)>::Rail<SHEEP_SPROUT(240)>::UniRoad<Capsule>);
#include "macaron/fragmental/amenity/instances/undef_integer_llama.hpp"

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/

// In this example,
// we will pack each
//  0, ..., 239
// into
//  Dummy<1>::Page.
// The result will be collected in a Capsule.

/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_1 = Capsule<SHEEP_SPROUT(240, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integer_llama.hpp"
SAME_TYPE(ClassicPlume<LLAMA_SPROUT(240)>::Rail<Dummy<1>::Page>::Road<Capsule>);
SAME_TYPE(ClassicPlume<LLAMA_SPROUT(240)>::Rail<Dummy<1>::Page>::UniRoad<Capsule>);
#include "macaron/fragmental/amenity/instances/undef_integer_llama.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/

// In this example,
// we will pack each 1 into
//  Dummy<0>::Page,
//  ...,
//  Dummy<239>::Page.
// The result will be collected in a Capsule.

/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_2 = Capsule<SHEEP_SPROUT(240, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_2

#define SHEEP_PREFIX    \
    Dummy<
#define SHEEP_SUFFIX    \
    >::Page
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(ClassicPlume<1>::Rail<SHEEP_SPROUT(240)>::Road<Capsule>);
SAME_TYPE(ClassicPlume<1>::Rail<SHEEP_SPROUT(240)>::UniRoad<Capsule>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_llama.hpp"

#endif