// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PAGELESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PAGELESS_H

#include "conceptrodon/omennivore/concepts/pageless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestPageless {




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
static_assert(Pageless<WorkingClass>);
static_assert(Pageless<PseudoOwner>);
static_assert(Pageless<MoldOwner>);
static_assert(! Pageless<PageOwner>);
static_assert(Pageless<RoadOwner>);
static_assert(Pageless<RailOwner>);
static_assert(Pageless<FlowOwner>);
static_assert(Pageless<SailOwner>);
static_assert(Pageless<SnowOwner>);
static_assert(Pageless<HailOwner>);
static_assert(Pageless<CoolOwner>);
static_assert(Pageless<CalmOwner>);
static_assert(Pageless<GritOwner>);
static_assert(Pageless<WillOwner>);
static_assert(Pageless<GlowOwner>);
static_assert(Pageless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif