// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_WILLLY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_WILLLY_H

#include "conceptrodon/omennivore/concepts/willly.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestWillly {




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
static_assert(! Willly<WorkingClass>);
static_assert(! Willly<PseudoOwner>);
static_assert(! Willly<MoldOwner>);
static_assert(! Willly<PageOwner>);
static_assert(! Willly<RoadOwner>);
static_assert(! Willly<RailOwner>);
static_assert(! Willly<FlowOwner>);
static_assert(! Willly<SailOwner>);
static_assert(! Willly<SnowOwner>);
static_assert(! Willly<HailOwner>);
static_assert(! Willly<CoolOwner>);
static_assert(! Willly<CalmOwner>);
static_assert(! Willly<GritOwner>);
static_assert(Willly<WillOwner>);
static_assert(! Willly<GlowOwner>);
static_assert(! Willly<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif