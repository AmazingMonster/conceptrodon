// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SNOWLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SNOWLESS_H

#include "conceptrodon/omennivore/concepts/snowless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestSnowless {




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
    using Snow = void;
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
static_assert(Snowless<WorkingClass>);
static_assert(Snowless<PseudoOwner>);
static_assert(Snowless<MoldOwner>);
static_assert(Snowless<PageOwner>);
static_assert(Snowless<RoadOwner>);
static_assert(Snowless<RailOwner>);
static_assert(Snowless<FlowOwner>);
static_assert(Snowless<SailOwner>);
static_assert(! Snowless<SnowOwner>);
static_assert(Snowless<HailOwner>);
static_assert(Snowless<CoolOwner>);
static_assert(Snowless<CalmOwner>);
static_assert(Snowless<GritOwner>);
static_assert(Snowless<WillOwner>);
static_assert(Snowless<GlowOwner>);
static_assert(Snowless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif