// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_COOLLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_COOLLESS_H

#include "conceptrodon/omennivore/concepts/coolless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestCoolless {




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
static_assert(Coolless<WorkingClass>);
static_assert(Coolless<PseudoOwner>);
static_assert(Coolless<MoldOwner>);
static_assert(Coolless<PageOwner>);
static_assert(Coolless<RoadOwner>);
static_assert(Coolless<RailOwner>);
static_assert(Coolless<FlowOwner>);
static_assert(Coolless<SailOwner>);
static_assert(Coolless<SnowOwner>);
static_assert(Coolless<HailOwner>);
static_assert(! Coolless<CoolOwner>);
static_assert(Coolless<CalmOwner>);
static_assert(Coolless<GritOwner>);
static_assert(Coolless<WillOwner>);
static_assert(Coolless<GlowOwner>);
static_assert(Coolless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif