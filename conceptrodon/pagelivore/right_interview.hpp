// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_RIGHT_INTERVIEW_H
#define CONCEPTRODON_PAGELIVORE_RIGHT_INTERVIEW_H

#include "conceptrodon/microbiota/varbola/sensible_right_interview.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate>
struct RightInterview
{
    template<auto Interviewer>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Varbola::SensibleRightInterview<Variables...>
        ::template ProtoRail<Predicate>
        ::template Page<Interviewer>;

        template<auto...Variables>
        static constexpr auto Page_v
        {
            Varbola::SensibleRightInterview<Variables...>
            ::template ProtoRail<Predicate>
            ::template Page_v<Interviewer>
        };
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

}}

#endif