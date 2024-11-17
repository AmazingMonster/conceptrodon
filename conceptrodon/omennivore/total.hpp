// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_TOTAL_H
#define CONCEPTRODON_OMENNIVORE_TOTAL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct Total {};

// Element
template
<
    template<typename...> class Container,
    typename...Elements
>
struct Total<Container<Elements...>>
{ static constexpr size_t value = sizeof...(Elements); };

// Variable
template
<
    template<auto...> class Sequence,
    auto...Variables
>
struct Total<Sequence<Variables...>>
{ static constexpr size_t value = sizeof...(Variables); };

// Variable
template
<
    template<typename, auto...> class Sequence,
    typename Type,
    auto...Variables
>
struct Total<Sequence<Type, Variables...>>
{ static constexpr size_t value = sizeof...(Variables); };

// Mold
template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
struct Total<Warehouse<Containers...>>
{ static constexpr size_t value = sizeof...(Containers); };

// Page
template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
struct Total<Stockroom<Sequences...>>
{ static constexpr size_t value = sizeof...(Sequences); };

// Road
template
<
    template<template<template<typename...> class...> class...> class Sorrow,
    template<template<typename...> class...> class...Warehouses
>
struct Total<Sorrow<Warehouses...>>
{ static constexpr size_t value = sizeof...(Warehouses); };

// Rail
template
<
    template<template<template<auto...> class...> class...> class Melancholy,
    template<template<auto...> class...> class...Stockrooms
>
struct Total<Melancholy<Stockrooms...>>
{ static constexpr size_t value = sizeof...(Stockrooms); };

// Flow
template
<
    template<template<template<template<typename...> class...> class...> class...> class Silence,
    template<template<template<typename...> class...> class...> class...Sorrow
>
struct Total<Silence<Sorrow...>>
{ static constexpr size_t value = sizeof...(Sorrow); };

// Sail
template
<
    template<template<template<template<auto...> class...> class...> class...> class Tranquil,
    template<template<template<auto...> class...> class...> class...Melancholy
>
struct Total<Tranquil<Melancholy...>>
{ static constexpr size_t value = sizeof...(Melancholy); };

// Snow
template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<typename...> class...> class...> class...> class...Silence
>
struct Total<Sunshine<Silence...>>
{ static constexpr size_t value = sizeof...(Silence); };

// Hail
template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<auto...> class...> class...> class...> class...Silence
>
struct Total<Sunshine<Silence...>>
{ static constexpr size_t value = sizeof...(Silence); };

// Cool
template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...Sunshines
>
struct Total<Sunshine<Sunshines...>>
{ static constexpr size_t value = sizeof...(Sunshines); };

// Calm
template
<
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class...Sunshines
>
struct Total<Sunshine<Sunshines...>>
{ static constexpr size_t value = sizeof...(Sunshines); };

// Grit
template
<
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines
>
struct Total<Sunshine<Sunshines...>>
{ static constexpr size_t value = sizeof...(Sunshines); };

// Will
template
<
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines
>
struct Total<Sunshine<Sunshines...>>
{ static constexpr size_t value = sizeof...(Sunshines); };

// Glow
template
<
    template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...Sunshines
>
struct Total<Sunshine<Sunshines...>>
{ static constexpr size_t value = sizeof...(Sunshines); };


// Dawn
template
<
    template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...Sunshines
>
struct Total<Sunshine<Sunshines...>>
{ static constexpr size_t value = sizeof...(Sunshines); };


}}

#endif