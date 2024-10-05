// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_REFURBISH_H
#define CONCEPTRODON_TYPELIVORE_REFURBISH_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Refurbish
{
    template<template<typename...> class Decoration>
    struct ProtoRoad 
    { using type = Capsule<Decoration<Elements>...>; };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    template<template<typename...> class...Args>
    using Road_t = ProtoRoad<Args...>::type;

    template<template<typename...> class Decoration>
    using UniRoad = Capsule<Decoration<Elements>...>;
};

}}

#endif