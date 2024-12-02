// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_FLOWLY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_FLOWLY_H

#include "conceptrodon/omennivore/concepts/descend/all_flowly.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAllFlowly {




/******************************************************************************************************/
struct WorkingClass {};

struct PseudoOwner
{
    using Dawn = void;
};

struct MoldOwner
{
    template<typename...>
    using Mold = void;
};

struct PageOwner
{
    template<auto...>
    using Page = void;
};

struct RoadOwner
{
    template<template<typename...> class...>
    using Road = void;
};

struct RailOwner
{
    template<template<auto...> class...>
    using Rail = void;
};

struct FlowOwner
{
    template<template<template<typename...> class...> class...>
    using Flow = void;
};

struct SailOwner
{
    template<template<template<auto...> class...> class...>
    using Sail = void;
};

struct SnowOwner
{
    template<template<template<template<typename...> class...> class...> class...>
    using Snow = void;
};

struct HailOwner
{
    template<template<template<template<auto...> class...> class...> class...>
    using Hail = void;
};

struct CoolOwner
{
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    using Cool = void;
};

struct CalmOwner
{
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    using Calm = void;
};

struct GritOwner
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    using Grit = void;
};

struct WillOwner
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    using Will = void;
};

struct GlowOwner
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    using Glow = void;
};

struct DawnOwner
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    using Dawn = void;
};
/******************************************************************************************************/




/******************************************************************************************************/
struct MoldProprietor
{
    template<typename...>
    using Mold = void;
};

struct PageProprietor
{
    template<auto...>
    using Page = void;
};

struct RoadProprietor
{
    template<template<typename...> class...>
    using Road = void;
};

struct RailProprietor
{
    template<template<auto...> class...>
    using Rail = void;
};

struct FlowProprietor
{
    template<template<template<typename...> class...> class...>
    using Flow = void;
};

struct SailProprietor
{
    template<template<template<auto...> class...> class...>
    using Sail = void;
};

struct SnowProprietor
{
    template<template<template<template<typename...> class...> class...> class...>
    using Snow = void;
};

struct HailProprietor
{
    template<template<template<template<auto...> class...> class...> class...>
    using Hail = void;
};

struct CoolProprietor
{
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    using Cool = void;
};

struct CalmProprietor
{
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    using Calm = void;
};

struct GritProprietor
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    using Grit = void;
};

struct WillProprietor
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    using Will = void;
};

struct GlowProprietor
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    using Glow = void;
};

struct DawnProprietor
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    using Dawn = void;
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(! AllFlowly<WorkingClass, WorkingClass>);
static_assert(! AllFlowly<PseudoOwner, WorkingClass>);
static_assert(AllFlowly<FlowOwner, FlowProprietor>);
static_assert(! AllFlowly<FlowOwner, FlowProprietor, WorkingClass>);
/******************************************************************************************************/




}}}}

#endif