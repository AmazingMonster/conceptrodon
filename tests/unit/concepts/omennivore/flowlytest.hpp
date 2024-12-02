// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_FLOWLY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_FLOWLY_H

#include "conceptrodon/omennivore/concepts/flowly.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestFlowly {




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
    using Flow = void;
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
static_assert(! Flowly<WorkingClass>);
static_assert(! Flowly<PseudoOwner>);
static_assert(! Flowly<MoldOwner>);
static_assert(! Flowly<PageOwner>);
static_assert(! Flowly<RoadOwner>);
static_assert(! Flowly<RailOwner>);
static_assert(Flowly<FlowOwner>);
static_assert(! Flowly<SailOwner>);
static_assert(! Flowly<SnowOwner>);
static_assert(! Flowly<HailOwner>);
static_assert(! Flowly<CoolOwner>);
static_assert(! Flowly<CalmOwner>);
static_assert(! Flowly<GritOwner>);
static_assert(! Flowly<WillOwner>);
static_assert(! Flowly<GlowOwner>);
static_assert(! Flowly<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif