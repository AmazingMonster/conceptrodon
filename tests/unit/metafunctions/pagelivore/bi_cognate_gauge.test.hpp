// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_BI_COGNATE_GAUGE_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_BI_COGNATE_GAUGE_H

#include <type_traits>
#include "conceptrodon/pagelivore/bi_cognate_gauge.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/llama.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_llama.hpp"


namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestBiCognateGauge {




/******************************************************************************************************/
template<auto I>
struct Dummy
{
    template<auto V>
    struct ProtoPage
    {
        static constexpr auto value {I + V};
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<typename T>
    struct ProtoMold
    {
        static constexpr auto value {I + T::value};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
/******************************************************************************************************/

// In this example,
// we will place
//  0, ..., 239
// into
//  Dummy<0>::Page,
//  ...,
//  Dummy<239>::Page.
// The result will be collected in a Shuttle.

/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = Shuttle<SHEEP_SPROUT(240, *2)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
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
SAME_TYPE(BiCognateGauge<Shuttle>::Rail<SHEEP_SPROUT(240)>::Page<LLAMA_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_llama.hpp"

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/

// In this example,
// we will pack each
//  0, ..., 239
// into Dummy<1>::Page.
// The result will be collected in a Shuttle.

/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult_1 = Shuttle<SHEEP_SPROUT(240, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integer_llama.hpp"
SAME_TYPE(BiCognateGauge<Shuttle>::Rail<Dummy<1>::Page>::Page<LLAMA_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_llama.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/

// In this example,
// we will pack 1 into
//  Dummy<0>::Page,
//  ...,
//  Dummy<239>::Page.
// The result will be collected in a Shuttle.

/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult_2 = Shuttle<SHEEP_SPROUT(240, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
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

SAME_TYPE(BiCognateGauge<Shuttle>::Rail<SHEEP_SPROUT(240)>::Page<1>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/

// In this example,
// we will place
//  std::integral_constant<0>,
//  ...,
//  std::integral_constant<239>
// into
//  Dummy<0>::Mold,
//  ...,
//  Dummy<239>::Mold.
// The result will be collected in a Shuttle.

/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    Dummy<
#define SHEEP_SUFFIX    \
    >::Mold
#define SHEEP_SEPARATOR \
    ,

#include "macaron/fragmental/amenity/instances/define_integral_constant_llama.hpp"
SAME_TYPE(BiCognateGauge<Shuttle>::Road<SHEEP_SPROUT(240)>::Mold<LLAMA_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_llama.hpp"

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/

// In this example,
// we will pack each
//  std::integral_constant<0>,
//  ...,
//  std::integral_constant<239>
// into
//  Dummy<1>::Mold.
// The result will be collected in a Shuttle.

/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integral_constant_llama.hpp"
SAME_TYPE(BiCognateGauge<Shuttle>::Road<Dummy<1>::Mold>::Mold<LLAMA_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_llama.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/

// In this example,
// we will pack each
//  std::integral_constant<1>
// into
//  Dummy<0>::Mold,
//  ...,
//  Dummy<239>::Mold.
// The result will be collected in a Shuttle.

/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_2

#define SHEEP_PREFIX    \
    Dummy<
#define SHEEP_SUFFIX    \
    >::Mold
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(BiCognateGauge<Shuttle>::Road<SHEEP_SPROUT(240)>::Mold<std::integral_constant<int, 1>>);

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