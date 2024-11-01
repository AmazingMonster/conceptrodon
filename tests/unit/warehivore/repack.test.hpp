// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_WAREHIVORE_REPACK_H
#define CONCEPTRODON_TESTS_UNIT_WAREHIVORE_REPACK_H

#include <concepts>
#include "conceptrodon/descend/warehivore/repack.hpp"
#include "conceptrodon/reverie.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"


namespace Conceptrodon {
namespace Warehivore {
namespace UnitTests {
namespace TestRepack {

// In this test, we will paste
//  Reverie<Dummy<0>::Mold>,
//  ...,
//  Reverie<Dummy<239>::Mold>
// together and place the result in Tester.

/******************************************************************************************************/
template<template<typename...> class...Warehouses>
requires (sizeof...(Warehouses) == 240)
struct Tester {};

template<size_t>
struct Dummy
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Dummy<
#define SHEEP_SUFFIX    \
    >::Mold
#define SHEEP_SEPARATOR \
    ,

using SupposedResult = Tester<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    Reverie<Dummy<
#define SHEEP_SUFFIX    \
    >::Mold>
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(Repack<SHEEP_SPROUT(240)>::UniFlow<Tester>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/


}}}}


#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif