// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_GRADE_H
#define CONCEPTRODON_TYPELIVORE_GRADE_H

#include "conceptrodon/shuttle.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Grade
{
    template<template<typename...> class Paper>
    struct ProtoRoad 
    { using type = Shuttle<Paper<Elements>::value...>; };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    template<template<typename...> class...Args>
    using Road_t = ProtoRoad<Args...>::type;

    template<template<typename...> class Paper>
    using UniRoad = Shuttle<Paper<Elements>::value...>;
};

}}

#endif