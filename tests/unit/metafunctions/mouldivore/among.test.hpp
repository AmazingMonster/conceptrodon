// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_AMONG_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_AMONG_H

#include <utility>

#include "conceptrodon/mouldivore/among.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/vay.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestAmong {




/******************************************************************************************************/
template<int I>
struct Tester 
{
    template<typename...Agreements>
    struct Detail
    {
        using type = void;
    };

    
    template<>
    struct Detail<int>
    {
        using type = Vay<I>;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Vay<
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

using SupposedResult = Capsule<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Tester<
#define SHEEP_SUFFIX    \
    >::Mold
#define SHEEP_SEPARATOR \
    ,

using Amongus = Among<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Amongus::Page<
#define SHEEP_SUFFIX    \
    >::Mold<int>
#define SHEEP_SEPARATOR \
    ,

#define SUPPOSED_TYPE \
    SupposedResult

SAME_TYPE(Capsule<SHEEP_SPROUT(240)>);

#undef SUPPOSED_TYPE

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif