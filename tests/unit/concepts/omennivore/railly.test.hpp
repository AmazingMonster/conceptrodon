// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_RAILLY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_RAILLY_H

#include "conceptrodon/omennivore/concepts/railly.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestRailly {




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
static_assert(! Railly<WorkingClass>);
static_assert(! Railly<PseudoOwner>);
static_assert(! Railly<MoldOwner>);
static_assert(! Railly<PageOwner>);
static_assert(! Railly<RoadOwner>);
static_assert(Railly<RailOwner>);
static_assert(! Railly<FlowOwner>);
static_assert(! Railly<SailOwner>);
static_assert(! Railly<SnowOwner>);
static_assert(! Railly<HailOwner>);
static_assert(! Railly<CoolOwner>);
static_assert(! Railly<CalmOwner>);
static_assert(! Railly<GritOwner>);
static_assert(! Railly<WillOwner>);
static_assert(! Railly<GlowOwner>);
static_assert(! Railly<DawnOwner>);
/******************************************************************************************************/




}}}}

#endif