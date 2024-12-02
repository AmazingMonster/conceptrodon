// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_WILLLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_WILLLESS_H

#include "conceptrodon/omennivore/concepts/willless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestWillless {




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
static_assert(Willless<WorkingClass>);
static_assert(Willless<PseudoOwner>);
static_assert(Willless<MoldOwner>);
static_assert(Willless<PageOwner>);
static_assert(Willless<RoadOwner>);
static_assert(Willless<RailOwner>);
static_assert(Willless<FlowOwner>);
static_assert(Willless<SailOwner>);
static_assert(Willless<SnowOwner>);
static_assert(Willless<HailOwner>);
static_assert(Willless<CoolOwner>);
static_assert(Willless<CalmOwner>);
static_assert(Willless<GritOwner>);
static_assert(! Willless<WillOwner>);
static_assert(Willless<GlowOwner>);
static_assert(Willless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif