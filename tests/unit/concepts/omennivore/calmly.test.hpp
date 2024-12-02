// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_CALMLY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_CALMLY_H

#include "conceptrodon/omennivore/concepts/calmly.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestCalmly {




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
static_assert(! Calmly<WorkingClass>);
static_assert(! Calmly<PseudoOwner>);
static_assert(! Calmly<MoldOwner>);
static_assert(! Calmly<PageOwner>);
static_assert(! Calmly<RoadOwner>);
static_assert(! Calmly<RailOwner>);
static_assert(! Calmly<FlowOwner>);
static_assert(! Calmly<SailOwner>);
static_assert(! Calmly<SnowOwner>);
static_assert(! Calmly<HailOwner>);
static_assert(! Calmly<CoolOwner>);
static_assert(Calmly<CalmOwner>);
static_assert(! Calmly<GritOwner>);
static_assert(! Calmly<WillOwner>);
static_assert(! Calmly<GlowOwner>);
static_assert(! Calmly<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif