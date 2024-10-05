// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_PLUME_H
#define CONCEPTRODON_TYPELIVORE_PLUME_H

#include "conceptrodon/capsule.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Plume
{
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { using type = Capsule<typename Cosmetics<Elements>::type...>; };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;

    template<template<typename...> class...Cosmetics>
    using Road_t = Capsule<typename Cosmetics<Elements>::type...>;
};

}}

#endif