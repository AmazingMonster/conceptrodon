// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_ROADRIVORE_UNIT_TESTS_TEST_BIND_FRONT_H
#define CONCEPTRODON_ROADRIVORE_UNIT_TESTS_TEST_BIND_FRONT_H

#include <concepts>

#include "conceptrodon/metafunctions/roadrivore/bind_front.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Roadrivore {
namespace UnitTests {
namespace TestBindFront {

// In this test,
// we will bind 
//  Dummy<0>::Mold,
//  ...,
//  Dummy<99>::Mold
// to the back of Operation.
// Then, we will invoke the resulting metafunction by
//  Dummy<0>::Mold,
//  ...,
//  Dummy<139>::Mold.

/******************************************************************************************************/
template<template<typename...> class...Args>
requires (sizeof...(Args) == 240)
struct Operation {};

template<auto>
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

using SupposedResult = Operation<SHEEP_SPROUT(100), SHEEP_SPROUT(140)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
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

SAME_TYPE(BindFront<Operation>::Road<SHEEP_SPROUT(100)>::Road<SHEEP_SPROUT(140)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/



}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif