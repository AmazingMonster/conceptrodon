// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_UNIT_TESTS_TEST_BIND_BACK_H
#define CONCEPTRODON_RAILLIVORE_UNIT_TESTS_TEST_BIND_BACK_H

#include <concepts>

#include "conceptrodon/metafunctions/raillivore/bind_back.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Raillivore {
namespace UnitTests {
namespace TestBindBack {


    

/******************************************************************************************************/
template<template<auto...> class...Args>
requires (sizeof...(Args) == 240)
struct Operation {};

template<auto>
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
    >::Page
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(BindBack<Operation>::Rail<SHEEP_SPROUT(140)>::Rail<SHEEP_SPROUT(100)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/



}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif