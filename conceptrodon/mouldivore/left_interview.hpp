// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_LEFT_INTERVIEW_H
#define CONCEPTRODON_MOULDIVORE_LEFT_INTERVIEW_H

#include "conceptrodon/microbiota/typella/sensible_left_interview.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class...Predicates>
struct LeftInterview
{
    template<typename...Interviewers>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Typella::SensibleLeftInterview<Elements...>
        ::template ProtoRoad<Predicates...>
        ::template Mold<Interviewers...>;

        template<typename...Elements>
        static constexpr auto Mold_v
        {
            Typella::SensibleLeftInterview<Elements...>
            ::template ProtoRoad<Predicates...>
            ::template Mold_v<Interviewers...>
        };
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

}}

#endif