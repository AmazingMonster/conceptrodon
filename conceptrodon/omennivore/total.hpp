// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_TOTAL_H
#define CONCEPTRODON_OMENNIVORE_TOTAL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct Total {};

template<template<typename...> class Container, typename...Elements>
struct Total<Container<Elements...>>
{ static constexpr size_t value = sizeof...(Elements); };

template<template<auto...> class Sequence, auto...Variables>
struct Total<Sequence<Variables...>>
{ static constexpr size_t value = sizeof...(Variables); };

template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
struct Total<Sequence<Type, Variables...>>
{ static constexpr size_t value = sizeof...(Variables); };

template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
struct Total<Warehouse<Containers...>>
{ static constexpr size_t value = sizeof...(Containers); };

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct Total<Stockroom<Sequences...>>
{ static constexpr size_t value = sizeof...(Sequences); };

}}

#endif