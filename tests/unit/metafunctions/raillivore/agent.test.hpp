// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_UNIT_TESTS_TEST_AGENT_H
#define CONCEPTRODON_RAILLIVORE_UNIT_TESTS_TEST_AGENT_H

#include <utility>

#include "conceptrodon/metafunctions/raillivore/agent.hpp"
#include "conceptrodon/utilities/carrier.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Raillivore {
namespace UnitTests {
namespace TestAgent {




/******************************************************************************************************/
template<template<auto...> class...Args>
requires (sizeof...(Args) == 240)
struct Operation {};

template<auto>
struct DummyArg
{
    template<auto...>
    struct ProtoPage {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    DummyArg<
#define SHEEP_SUFFIX    \
    >::template Page
#define SHEEP_SEPARATOR \
    ,

using SupposedResult = Operation<SHEEP_SPROUT(240)>;
using PackedVessel = Carrier<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

SAME_TYPE(Agent<Operation>::Mold<PackedVessel>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/


}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif