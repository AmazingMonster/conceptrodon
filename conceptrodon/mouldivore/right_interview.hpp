// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_RIGHT_INTERVIEW_H
#define CONCEPTRODON_MOULDIVORE_RIGHT_INTERVIEW_H

#include "conceptrodon/microbiota/typella/sensible_right_interview.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate>
struct RightInterview
{
    template<typename Interviewer>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Typella::SensibleRightInterview<Elements...>
        ::template ProtoRoad<Predicate>
        ::template Mold<Interviewer>;

        template<typename...Elements>
        static constexpr auto Mold_v
        {
            Typella::SensibleRightInterview<Elements...>
            ::template ProtoRoad<Predicate>
            ::template Mold_v<Interviewer>
        };
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

}}

#endif