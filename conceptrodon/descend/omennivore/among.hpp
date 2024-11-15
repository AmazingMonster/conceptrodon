// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_AMONG_H
#define CONCEPTRODON_OMENNIVORE_AMONG_H

#include "conceptrodon/microbiota/typella/typical_among.hpp"
#include "conceptrodon/microbiota/varbola/among.hpp"
#include "conceptrodon/microbiota/moldiae/among.hpp"
#include "conceptrodon/microbiota/pagelis/among.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename>
struct TypicalAmong {};

template<template<typename...> class Container, typename...Elements>
struct TypicalAmong<Container<Elements...>>
: public Typella::TypicalAmong<Elements...>
{};

template<template<auto...> class Sequence, auto...Variables>
struct TypicalAmong<Sequence<Variables...>>
: public Varbola::Among<Variables...>
{};

template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
struct TypicalAmong<Warehouse<Containers...>>
: public Moldiae::Among<Containers...>
{};

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct TypicalAmong<Stockroom<Sequences...>>
: public Pagelis::Among<Sequences...>
{};

template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
struct TypicalAmong<Sequence<Type, Variables...>>
: public Varbola::Among<Variables...>
{};

template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
struct TypicalAmong<Warehouse<Containers...>>
: public Moldiae::Among<Containers...>
{};

}}

#endif