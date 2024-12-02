// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_CALMLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_CALMLESS_H

#include "conceptrodon/omennivore/concepts/calmless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestCalmless {




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
static_assert(Calmless<WorkingClass>);
static_assert(Calmless<PseudoOwner>);
static_assert(Calmless<MoldOwner>);
static_assert(Calmless<PageOwner>);
static_assert(Calmless<RoadOwner>);
static_assert(Calmless<RailOwner>);
static_assert(Calmless<FlowOwner>);
static_assert(Calmless<SailOwner>);
static_assert(Calmless<SnowOwner>);
static_assert(Calmless<HailOwner>);
static_assert(Calmless<CoolOwner>);
static_assert(! Calmless<CalmOwner>);
static_assert(Calmless<GritOwner>);
static_assert(Calmless<WillOwner>);
static_assert(Calmless<GlowOwner>);
static_assert(Calmless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif