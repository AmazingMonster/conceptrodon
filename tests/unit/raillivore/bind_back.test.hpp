// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_RAILLIVORE_BIND_BACK_H
#define CONCEPTRODON_TESTS_UNIT_RAILLIVORE_BIND_BACK_H

#include <concepts>
#include "conceptrodon/raillivore/bind_back.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/phantom.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Raillivore {
namespace UnitTests {
namespace TestBindBack {

// In this test,
// we will bind 
//  Dummy<0>::Page,
//  ...,
//  Dummy<139>::Page
// to the back of Phantom.
// Then, we will invoke the resulting metafunction by
//  Dummy<0>::Page,
//  ...,
//  Dummy<99>::Page.

/******************************************************************************************************/
template<auto>
struct Dummy
{
    template<auto...Variables>
    using Page = Shuttle<Variables...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Dummy<
#define SHEEP_SUFFIX    \
    >::Page
#define SHEEP_SEPARATOR \
    ,

using SupposedResult = Phantom<SHEEP_SPROUT(100), SHEEP_SPROUT(140)>;

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

SAME_TYPE(BindBack<Phantom>::Rail<SHEEP_SPROUT(140)>::Rail<SHEEP_SPROUT(100)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/



}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif