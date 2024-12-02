// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_DAWNLY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_DAWNLY_H

#include "conceptrodon/omennivore/concepts/dawnly.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestDawnly {




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
static_assert(! Dawnly<WorkingClass>);
static_assert(! Dawnly<PseudoOwner>);
static_assert(! Dawnly<MoldOwner>);
static_assert(! Dawnly<PageOwner>);
static_assert(! Dawnly<RoadOwner>);
static_assert(! Dawnly<RailOwner>);
static_assert(! Dawnly<FlowOwner>);
static_assert(! Dawnly<SailOwner>);
static_assert(! Dawnly<SnowOwner>);
static_assert(! Dawnly<HailOwner>);
static_assert(! Dawnly<CoolOwner>);
static_assert(! Dawnly<CalmOwner>);
static_assert(! Dawnly<GritOwner>);
static_assert(! Dawnly<WillOwner>);
static_assert(! Dawnly<GlowOwner>);
static_assert(Dawnly<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif