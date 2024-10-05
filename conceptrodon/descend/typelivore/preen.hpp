// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_PREEN_H
#define CONCEPTRODON_TYPELIVORE_PREEN_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Preen
{
    template<template<typename...> class Cosmetic>
    struct ProtoRoad 
    { using type = Capsule<typename Cosmetic<Elements>::type...>; };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    template<template<typename...> class...Args>
    using Road_t = ProtoRoad<Args...>::type;

    template<template<typename...> class Cosmetic>
    using UniRoad = Capsule<typename Cosmetic<Elements>::type...>;
};

}}

#endif