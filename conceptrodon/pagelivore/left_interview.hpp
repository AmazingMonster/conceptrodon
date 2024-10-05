// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_LEFT_INTERVIEW_H
#define CONCEPTRODON_PAGELIVORE_LEFT_INTERVIEW_H

#include "conceptrodon/microbiota/varbola/sensible_left_interview.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate>
struct LeftInterview
{
    template<auto Interviewer>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Varbola::SensibleLeftInterview<Variables...>
        ::template ProtoRail<Predicate>
        ::template Page<Interviewer>;

        template<auto...Variables>
        static constexpr auto Page_v
        {
            Varbola::SensibleLeftInterview<Variables...>
            ::template ProtoRail<Predicate>
            ::template Page_v<Interviewer>
        };
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

}}

#endif