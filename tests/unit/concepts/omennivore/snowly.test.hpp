// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SNOWLY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_SNOWLY_H

#include "conceptrodon/omennivore/concepts/snowly.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestSnowly {




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
    using Snow = void;
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
static_assert(! Snowly<WorkingClass>);
static_assert(! Snowly<PseudoOwner>);
static_assert(! Snowly<MoldOwner>);
static_assert(! Snowly<PageOwner>);
static_assert(! Snowly<RoadOwner>);
static_assert(! Snowly<RailOwner>);
static_assert(! Snowly<FlowOwner>);
static_assert(! Snowly<SailOwner>);
static_assert(Snowly<SnowOwner>);
static_assert(! Snowly<HailOwner>);
static_assert(! Snowly<CoolOwner>);
static_assert(! Snowly<CalmOwner>);
static_assert(! Snowly<GritOwner>);
static_assert(! Snowly<WillOwner>);
static_assert(! Snowly<GlowOwner>);
static_assert(! Snowly<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif