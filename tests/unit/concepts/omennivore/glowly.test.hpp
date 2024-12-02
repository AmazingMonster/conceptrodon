// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GLOWLY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GLOWLY_H

#include "conceptrodon/omennivore/concepts/glowly.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestGlowly {




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
static_assert(! Glowly<WorkingClass>);
static_assert(! Glowly<PseudoOwner>);
static_assert(! Glowly<MoldOwner>);
static_assert(! Glowly<PageOwner>);
static_assert(! Glowly<RoadOwner>);
static_assert(! Glowly<RailOwner>);
static_assert(! Glowly<FlowOwner>);
static_assert(! Glowly<SailOwner>);
static_assert(! Glowly<SnowOwner>);
static_assert(! Glowly<HailOwner>);
static_assert(! Glowly<CoolOwner>);
static_assert(! Glowly<CalmOwner>);
static_assert(! Glowly<GritOwner>);
static_assert(! Glowly<WillOwner>);
static_assert(Glowly<GlowOwner>);
static_assert(! Glowly<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif