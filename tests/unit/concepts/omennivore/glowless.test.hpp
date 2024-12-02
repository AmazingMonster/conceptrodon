// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GLOWLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GLOWLESS_H

#include "conceptrodon/omennivore/concepts/glowless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestGlowless {




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
static_assert(Glowless<WorkingClass>);
static_assert(Glowless<PseudoOwner>);
static_assert(Glowless<MoldOwner>);
static_assert(Glowless<PageOwner>);
static_assert(Glowless<RoadOwner>);
static_assert(Glowless<RailOwner>);
static_assert(Glowless<FlowOwner>);
static_assert(Glowless<SailOwner>);
static_assert(Glowless<SnowOwner>);
static_assert(Glowless<HailOwner>);
static_assert(Glowless<CoolOwner>);
static_assert(Glowless<CalmOwner>);
static_assert(Glowless<GritOwner>);
static_assert(Glowless<WillOwner>);
static_assert(! Glowless<GlowOwner>);
static_assert(Glowless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif