// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_RIGHT_INTERVIEW_H
#define CONCEPTRODON_PAGELIVORE_RIGHT_INTERVIEW_H

#include "conceptrodon/metafunctions/microbiota/varbola/sensible_right_interview.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Predicates>
struct RightInterview
{
    template<auto...Interviewers>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Varbola::SensibleRightInterview<Variables...>
        ::template ProtoRail<Predicates...>
        ::template ProtoPage<Interviewers...>;

        template<auto...Variables>
        static constexpr auto Page_v
        {
            Varbola::SensibleRightInterview<Variables...>
            ::template ProtoRail<Predicates...>
            ::template Page_v<Interviewers...>
        };
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

}}

#endif