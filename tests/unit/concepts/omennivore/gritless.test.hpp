// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GRITLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GRITLESS_H

#include "conceptrodon/omennivore/concepts/gritless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestGritless {




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
static_assert(Gritless<WorkingClass>);
static_assert(Gritless<PseudoOwner>);
static_assert(Gritless<MoldOwner>);
static_assert(Gritless<PageOwner>);
static_assert(Gritless<RoadOwner>);
static_assert(Gritless<RailOwner>);
static_assert(Gritless<FlowOwner>);
static_assert(Gritless<SailOwner>);
static_assert(Gritless<SnowOwner>);
static_assert(Gritless<HailOwner>);
static_assert(Gritless<CoolOwner>);
static_assert(Gritless<CalmOwner>);
static_assert(! Gritless<GritOwner>);
static_assert(Gritless<WillOwner>);
static_assert(Gritless<GlowOwner>);
static_assert(Gritless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif