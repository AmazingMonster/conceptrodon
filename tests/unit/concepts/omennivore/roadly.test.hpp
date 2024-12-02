// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ROADLY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ROADLY_H

#include "conceptrodon/omennivore/concepts/roadly.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestRoadly {




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
static_assert(! Roadly<WorkingClass>);
static_assert(! Roadly<PseudoOwner>);
static_assert(! Roadly<MoldOwner>);
static_assert(! Roadly<PageOwner>);
static_assert(Roadly<RoadOwner>);
static_assert(! Roadly<RailOwner>);
static_assert(! Roadly<FlowOwner>);
static_assert(! Roadly<SailOwner>);
static_assert(! Roadly<SnowOwner>);
static_assert(! Roadly<HailOwner>);
static_assert(! Roadly<CoolOwner>);
static_assert(! Roadly<CalmOwner>);
static_assert(! Roadly<GritOwner>);
static_assert(! Roadly<WillOwner>);
static_assert(! Roadly<GlowOwner>);
static_assert(! Roadly<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif