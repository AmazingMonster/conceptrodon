// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_SENSIBLE_PLUME_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_SENSIBLE_PLUME_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/typelivore/sensible_plume.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/llama.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_llama.hpp"


namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestSensiblePlume {




/******************************************************************************************************/
template<auto I>
struct Tester
{
    template<typename T>
    struct ProtoMold
    {
        using type = std::integral_constant<int, I + T::value>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Capsule<SHEEP_SPROUT(240, *2)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    Tester<
#define SHEEP_SUFFIX    \
    >::Mold
#define SHEEP_SEPARATOR \
    ,

#include "macaron/fragmental/amenity/instances/define_integral_constant_llama.hpp"
SAME_TYPE(SensiblePlume<LLAMA_SPROUT(240)>::Road<Capsule>::Road<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_llama.hpp"

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