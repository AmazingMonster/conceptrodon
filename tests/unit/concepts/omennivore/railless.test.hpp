// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_RAILLESS_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_RAILLESS_H

#include "conceptrodon/omennivore/concepts/railless.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestRailless {




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
static_assert(Railless<WorkingClass>);
static_assert(Railless<PseudoOwner>);
static_assert(Railless<MoldOwner>);
static_assert(Railless<PageOwner>);
static_assert(Railless<RoadOwner>);
static_assert(! Railless<RailOwner>);
static_assert(Railless<FlowOwner>);
static_assert(Railless<SailOwner>);
static_assert(Railless<SnowOwner>);
static_assert(Railless<HailOwner>);
static_assert(Railless<CoolOwner>);
static_assert(Railless<CalmOwner>);
static_assert(Railless<GritOwner>);
static_assert(Railless<WillOwner>);
static_assert(Railless<GlowOwner>);
static_assert(Railless<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif