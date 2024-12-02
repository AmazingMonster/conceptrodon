// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_MOLDLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_MOLDLESS_H

#include "conceptrodon/omennivore/concepts/moldless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestMoldless {




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
static_assert(Moldless<WorkingClass>);
static_assert(Moldless<PseudoOwner>);
static_assert(! Moldless<MoldOwner>);
static_assert(Moldless<PageOwner>);
static_assert(Moldless<RoadOwner>);
static_assert(Moldless<RailOwner>);
static_assert(Moldless<FlowOwner>);
static_assert(Moldless<SailOwner>);
static_assert(Moldless<SnowOwner>);
static_assert(Moldless<HailOwner>);
static_assert(Moldless<CoolOwner>);
static_assert(Moldless<CalmOwner>);
static_assert(Moldless<GritOwner>);
static_assert(Moldless<WillOwner>);
static_assert(Moldless<GlowOwner>);
static_assert(Moldless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif