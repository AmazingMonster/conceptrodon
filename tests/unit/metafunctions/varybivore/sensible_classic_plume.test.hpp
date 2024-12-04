// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_SENSIBLE_CLASSIC_PLUME_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_SENSIBLE_CLASSIC_PLUME_H

#include <utility>

#include "conceptrodon/varybivore/sensible_classic_plume.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/llama.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_llama.hpp"


namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestSensibleClassicPlume {




/******************************************************************************************************/
template<typename...Args>
requires (sizeof...(Args) == 240)
struct Operation {};

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




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Operation<SHEEP_SPROUT(240, *2)>;
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
SAME_TYPE(SensibleClassicPlume<LLAMA_SPROUT(240)>::Road<Operation>::Rail<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_llama.hpp"

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_1 = Operation<SHEEP_SPROUT(240, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integer_llama.hpp"
SAME_TYPE(SensibleClassicPlume<LLAMA_SPROUT(240)>::Road<Operation>::Rail<Dummy<1>::Page>);
#include "macaron/fragmental/amenity/instances/undef_integer_llama.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_2 = Operation<SHEEP_SPROUT(240, +1)>;
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

SAME_TYPE(SensibleClassicPlume<1>::Road<Operation>::Rail<SHEEP_SPROUT(240)>);

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