// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_ROADRIVORE_AGENT_H
#define CONCEPTRODON_TESTS_UNIT_ROADRIVORE_AGENT_H

#include <concepts>
#include <utility>
#include "conceptrodon/roadrivore/agent.hpp"
#include "conceptrodon/vehicle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "type_traits"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Roadrivore {
namespace UnitTests {
namespace TestAgent {




/******************************************************************************************************/
template<template<typename...> class...>
struct Operation;

template<auto>
struct DummyArg
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    DummyArg<
#define SHEEP_SUFFIX    \
    >::template Mold
#define SHEEP_SEPARATOR \
    ,

using SupposedResult = Operation<SHEEP_SPROUT(240)>;
using PackedVessel = Vehicle<SHEEP_SPROUT(240)>;

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