// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_DAWNLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_DAWNLESS_H

#include "conceptrodon/omennivore/concepts/dawnless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestDawnless {




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
static_assert(Dawnless<WorkingClass>);
static_assert(Dawnless<PseudoOwner>);
static_assert(Dawnless<MoldOwner>);
static_assert(Dawnless<PageOwner>);
static_assert(Dawnless<RoadOwner>);
static_assert(Dawnless<RailOwner>);
static_assert(Dawnless<FlowOwner>);
static_assert(Dawnless<SailOwner>);
static_assert(Dawnless<SnowOwner>);
static_assert(Dawnless<HailOwner>);
static_assert(Dawnless<CoolOwner>);
static_assert(Dawnless<CalmOwner>);
static_assert(Dawnless<GritOwner>);
static_assert(Dawnless<WillOwner>);
static_assert(Dawnless<GlowOwner>);
static_assert(! Dawnless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif