// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PAGELY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_PAGELY_H

#include "conceptrodon/omennivore/concepts/pagely.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestPagely {




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
static_assert(! Pagely<WorkingClass>);
static_assert(! Pagely<PseudoOwner>);
static_assert(! Pagely<MoldOwner>);
static_assert(Pagely<PageOwner>);
static_assert(! Pagely<RoadOwner>);
static_assert(! Pagely<RailOwner>);
static_assert(! Pagely<FlowOwner>);
static_assert(! Pagely<SailOwner>);
static_assert(! Pagely<SnowOwner>);
static_assert(! Pagely<HailOwner>);
static_assert(! Pagely<CoolOwner>);
static_assert(! Pagely<CalmOwner>);
static_assert(! Pagely<GritOwner>);
static_assert(! Pagely<WillOwner>);
static_assert(! Pagely<GlowOwner>);
static_assert(! Pagely<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif