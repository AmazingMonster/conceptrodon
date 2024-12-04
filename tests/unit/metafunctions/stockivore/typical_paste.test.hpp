// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_STOCKIVORE_TYPICAL_PASTE_H
#define CONCEPTRODON_TESTS_UNIT_STOCKIVORE_TYPICAL_PASTE_H

#include <concepts>

#include "conceptrodon/stockivore/paste.hpp"
#include "conceptrodon/carrier.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"


namespace Conceptrodon {
namespace Stockivore {
namespace UnitTests {
namespace TestTypicalPaste {

// In this test, we will paste
//  FirstPackedVessel<>,
//  Carrier<Dummy<0>::Page>,
//  Carrier<Dummy<239>::Page>
// together.

/******************************************************************************************************/
template<template<auto...> class...Sequences>
struct FirstPackedVessel;

template<size_t>
struct Dummy
{
    template<auto...>
    struct ProtoPage {};

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Dummy<
#define SHEEP_SUFFIX    \
    >::Page
#define SHEEP_SEPARATOR \
    ,

using SupposedResult = FirstPackedVessel<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    Carrier<Dummy<
#define SHEEP_SUFFIX    \
    >::Page>
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(TypicalPaste<FirstPackedVessel<>, SHEEP_SPROUT(240)>::type);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/




}}}}

#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif