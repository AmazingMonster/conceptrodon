// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GRITLY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_GRITLY_H

#include "conceptrodon/omennivore/concepts/gritly.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestGritly {




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
static_assert(! Gritly<WorkingClass>);
static_assert(! Gritly<PseudoOwner>);
static_assert(! Gritly<MoldOwner>);
static_assert(! Gritly<PageOwner>);
static_assert(! Gritly<RoadOwner>);
static_assert(! Gritly<RailOwner>);
static_assert(! Gritly<FlowOwner>);
static_assert(! Gritly<SailOwner>);
static_assert(! Gritly<SnowOwner>);
static_assert(! Gritly<HailOwner>);
static_assert(! Gritly<CoolOwner>);
static_assert(! Gritly<CalmOwner>);
static_assert(Gritly<GritOwner>);
static_assert(! Gritly<WillOwner>);
static_assert(! Gritly<GlowOwner>);
static_assert(! Gritly<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif