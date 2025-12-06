// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_CLASSIC_PLUME_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_CLASSIC_PLUME_H

#include <utility>

#include "conceptrodon/mouldivore/bi_cognate_classic_plume.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/llama.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_llama.hpp"


namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestBiCognateClassicPlume {




/******************************************************************************************************/
template<auto I>
struct Dummy
{
    template<typename T>
    struct ProtoMold
    {
        using type = std::integral_constant<int, I + T::value>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<auto V>
    struct ProtoPage
    {
        using type = std::integral_constant<int, I + V>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<typename...Elements>
requires (sizeof...(Elements) == 240)
struct Operation;
/******************************************************************************************************/




/**** First Test ****/
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
    >::Mold
#define SHEEP_SEPARATOR \
    ,

#include "macaron/fragmental/amenity/instances/define_integral_constant_llama.hpp"
SAME_TYPE(BiCognateClassicPlume<Operation>::Road<SHEEP_SPROUT(240)>::Mold<LLAMA_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_llama.hpp"

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/**** Second Test ****/
/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_1 = Operation<SHEEP_SPROUT(240, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#define SUPPOSED_TYPE   \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integral_constant_llama.hpp"
SAME_TYPE(BiCognateClassicPlume<Operation>::Road<Dummy<1>::Mold>::Mold<LLAMA_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_llama.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/**** Third Test ****/
/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_2 = Operation<SHEEP_SPROUT(240, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#define SUPPOSED_TYPE   \
    SupposedResult_2

#define SHEEP_PREFIX    \
    Dummy<
#define SHEEP_SUFFIX    \
    >::Mold
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(BiCognateClassicPlume<Operation>::Road<SHEEP_SPROUT(240)>::Mold<std::integral_constant<int, 1>>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/**** Fourth Test ****/
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
SAME_TYPE(BiCognateClassicPlume<Operation>::Rail<SHEEP_SPROUT(240)>::Page<LLAMA_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_llama.hpp"

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/





/**** Fifth Test ****/
/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integer_llama.hpp"
SAME_TYPE(BiCognateClassicPlume<Operation>::Rail<Dummy<1>::Page>::Page<LLAMA_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integer_llama.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/





/**** Sixth Test ****/
/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult_2

#define SHEEP_PREFIX    \
    Dummy<
#define SHEEP_SUFFIX    \
    >::Page
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(BiCognateClassicPlume<Operation>::Rail<SHEEP_SPROUT(240)>::Page<1>);

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