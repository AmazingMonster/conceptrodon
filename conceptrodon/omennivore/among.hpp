// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_AMONG_H
#define CONCEPTRODON_OMENNIVORE_AMONG_H

#include "conceptrodon/microbiota/typella/among.hpp"
#include "conceptrodon/microbiota/varbola/among.hpp"
#include "conceptrodon/microbiota/moldiae/among.hpp"
#include "conceptrodon/microbiota/pagelis/among.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename>
struct Among {};

template<template<typename...> class Container, typename...Elements>
struct Among<Container<Elements...>>
: public Typella::Among<Elements...>
{};

template<template<auto...> class Sequence, auto...Variables>
struct Among<Sequence<Variables...>>
: public Varbola::Among<Variables...>
{};

template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
struct Among<Warehouse<Containers...>>
: public Moldiae::Among<Containers...>
{};

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct Among<Stockroom<Sequences...>>
: public Pagelis::Among<Sequences...>
{};


template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
struct Among<Sequence<Type, Variables...>>
: public Varbola::Among<Variables...>
{};

}}

#endif