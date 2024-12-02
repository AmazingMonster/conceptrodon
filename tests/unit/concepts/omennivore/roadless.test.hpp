// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ROADLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ROADLESS_H

#include "conceptrodon/omennivore/concepts/roadless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestRoadless {




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
static_assert(Roadless<WorkingClass>);
static_assert(Roadless<PseudoOwner>);
static_assert(Roadless<MoldOwner>);
static_assert(Roadless<PageOwner>);
static_assert(! Roadless<RoadOwner>);
static_assert(Roadless<RailOwner>);
static_assert(Roadless<FlowOwner>);
static_assert(Roadless<SailOwner>);
static_assert(Roadless<SnowOwner>);
static_assert(Roadless<HailOwner>);
static_assert(Roadless<CoolOwner>);
static_assert(Roadless<CalmOwner>);
static_assert(Roadless<GritOwner>);
static_assert(Roadless<WillOwner>);
static_assert(Roadless<GlowOwner>);
static_assert(Roadless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif