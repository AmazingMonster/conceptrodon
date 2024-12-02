// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SAILLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SAILLESS_H

#include "conceptrodon/omennivore/concepts/sailless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestSailless {




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
    using Sail = void;
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
static_assert(Sailless<WorkingClass>);
static_assert(Sailless<PseudoOwner>);
static_assert(Sailless<MoldOwner>);
static_assert(Sailless<PageOwner>);
static_assert(Sailless<RoadOwner>);
static_assert(Sailless<RailOwner>);
static_assert(Sailless<FlowOwner>);
static_assert(! Sailless<SailOwner>);
static_assert(Sailless<SnowOwner>);
static_assert(Sailless<HailOwner>);
static_assert(Sailless<CoolOwner>);
static_assert(Sailless<CalmOwner>);
static_assert(Sailless<GritOwner>);
static_assert(Sailless<WillOwner>);
static_assert(Sailless<GlowOwner>);
static_assert(Sailless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif