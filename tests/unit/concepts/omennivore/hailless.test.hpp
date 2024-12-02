// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_HAILLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_HAILLESS_H

#include "conceptrodon/omennivore/concepts/hailless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestHailless {




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
    using Hail = void;
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
static_assert(Hailless<WorkingClass>);
static_assert(Hailless<PseudoOwner>);
static_assert(Hailless<MoldOwner>);
static_assert(Hailless<PageOwner>);
static_assert(Hailless<RoadOwner>);
static_assert(Hailless<RailOwner>);
static_assert(Hailless<FlowOwner>);
static_assert(Hailless<SailOwner>);
static_assert(Hailless<SnowOwner>);
static_assert(! Hailless<HailOwner>);
static_assert(Hailless<CoolOwner>);
static_assert(Hailless<CalmOwner>);
static_assert(Hailless<GritOwner>);
static_assert(Hailless<WillOwner>);
static_assert(Hailless<GlowOwner>);
static_assert(Hailless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif