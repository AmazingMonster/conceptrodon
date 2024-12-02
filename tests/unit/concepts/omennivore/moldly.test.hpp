// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_MOLDLY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_MOLDLY_H

#include "conceptrodon/omennivore/concepts/moldly.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestMoldly {




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
static_assert(! Moldly<WorkingClass>);
static_assert(! Moldly<PseudoOwner>);
static_assert(Moldly<MoldOwner>);
static_assert(! Moldly<PageOwner>);
static_assert(! Moldly<RoadOwner>);
static_assert(! Moldly<RailOwner>);
static_assert(! Moldly<FlowOwner>);
static_assert(! Moldly<SailOwner>);
static_assert(! Moldly<SnowOwner>);
static_assert(! Moldly<HailOwner>);
static_assert(! Moldly<CoolOwner>);
static_assert(! Moldly<CalmOwner>);
static_assert(! Moldly<GritOwner>);
static_assert(! Moldly<WillOwner>);
static_assert(! Moldly<GlowOwner>);
static_assert(! Moldly<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif