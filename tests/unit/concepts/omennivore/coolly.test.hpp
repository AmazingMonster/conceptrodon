// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_COOLLY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_COOLLY_H

#include "conceptrodon/omennivore/concepts/coolly.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestCoolly {




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
    using Cool = void;
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
static_assert(! Coolly<WorkingClass>);
static_assert(! Coolly<PseudoOwner>);
static_assert(! Coolly<MoldOwner>);
static_assert(! Coolly<PageOwner>);
static_assert(! Coolly<RoadOwner>);
static_assert(! Coolly<RailOwner>);
static_assert(! Coolly<FlowOwner>);
static_assert(! Coolly<SailOwner>);
static_assert(! Coolly<SnowOwner>);
static_assert(! Coolly<HailOwner>);
static_assert(Coolly<CoolOwner>);
static_assert(! Coolly<CalmOwner>);
static_assert(! Coolly<GritOwner>);
static_assert(! Coolly<WillOwner>);
static_assert(! Coolly<GlowOwner>);
static_assert(! Coolly<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif