// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_AMONG_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_AMONG_H

#include "conceptrodon/pagelivore/among.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include <utility>

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestAmong {




/******************************************************************************************************/
template<size_t>
struct Tester 
{
    template<auto...>
    struct ProtoPage {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Tester<
#define SHEEP_SUFFIX    \
    >::Page<0>
#define SHEEP_SEPARATOR \
    ,

using SupposedResult = Capsule<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult
/******************************************************************************************************/



/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Tester<
#define SHEEP_SUFFIX    \
    >::Page
#define SHEEP_SEPARATOR \
    ,

using Amongus = Among<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR


#define SHEEP_PREFIX    \
    Amongus::Page<
#define SHEEP_SUFFIX    \
    >::Page<0>
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(Capsule<SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif