// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EASY_KINDRED_REPACK_MOLD_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EASY_KINDRED_REPACK_MOLD_H

#include <concepts>

#include "conceptrodon/omennivore/easy_kindred_repack.hpp"
#include "conceptrodon/vehicle.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"


namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestEasyKindredRepackMold {




/******************************************************************************************************/
template<size_t>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

template<template<typename...> class...>
struct Transport {};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Operation<
#define SHEEP_SUFFIX    \
    >::Mold
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
    Vehicle<Operation<
#define SHEEP_SUFFIX    \
    >::Mold>
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(EasyKindredRepack<SHEEP_SPROUT(240)>::UniFlow<Transport>);
SAME_TYPE(EasyKindredRepack<SHEEP_SPROUT(240)>::Flow<Transport>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/




}}}}

#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif