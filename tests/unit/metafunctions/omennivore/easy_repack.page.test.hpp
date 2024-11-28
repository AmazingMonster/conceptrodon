// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EASY_REPACK_PAGE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EASY_REPACK_PAGE_H

#include <concepts>
#include "conceptrodon/descend/descend/omennivore/easy_repack.hpp"
#include "conceptrodon/carrier.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"


namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestEasyRepackPage {




/******************************************************************************************************/
template<size_t>
struct Tester
{
    template<auto...>
    struct ProtoPage {};

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

template<template<auto...> class...>
struct Transport {};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Tester<
#define SHEEP_SUFFIX    \
    >::Page
#define SHEEP_SEPARATOR \
    ,

using SupposedResult = Transport<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    Carrier<Tester<
#define SHEEP_SUFFIX    \
    >::Page>
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(EasyRepack<SHEEP_SPROUT(240)>::UniSail<Transport>);
SAME_TYPE(EasyRepack<SHEEP_SPROUT(240)>::Sail<Transport>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/


}}}}


#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif