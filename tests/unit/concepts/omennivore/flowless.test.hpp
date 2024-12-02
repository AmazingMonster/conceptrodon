// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_FLOWLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_FLOWLESS_H

#include "conceptrodon/omennivore/concepts/flowless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestFlowless {




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
    using Flow = void;
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
static_assert(Flowless<WorkingClass>);
static_assert(Flowless<PseudoOwner>);
static_assert(Flowless<MoldOwner>);
static_assert(Flowless<PageOwner>);
static_assert(Flowless<RoadOwner>);
static_assert(Flowless<RailOwner>);
static_assert(! Flowless<FlowOwner>);
static_assert(Flowless<SailOwner>);
static_assert(Flowless<SnowOwner>);
static_assert(Flowless<HailOwner>);
static_assert(Flowless<CoolOwner>);
static_assert(Flowless<CalmOwner>);
static_assert(Flowless<GritOwner>);
static_assert(Flowless<WillOwner>);
static_assert(Flowless<GlowOwner>);
static_assert(Flowless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif