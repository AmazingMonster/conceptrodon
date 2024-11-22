// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_COGNATE_LEFT_INTERVIEW_H
#define CONCEPTRODON_PAGELIVORE_COGNATE_LEFT_INTERVIEW_H

#include "conceptrodon/microbiota/varbola/sensible_left_interview.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Predicates>
struct CognateLeftInterview
{
    template<auto...Interviewers>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Varbola::SensibleLeftInterview<Variables...>
        ::template ProtoRail<Predicates...>
        ::template ProtoPage<Interviewers...>;

        template<auto...Variables>
        static constexpr auto Page_v
        {
            Varbola::SensibleLeftInterview<Variables...>
            ::template ProtoRail<Predicates...>
            ::template Page_v<Interviewers...>
        };
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

}}

#endif