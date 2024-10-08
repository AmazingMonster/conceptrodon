// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_RECONFORMED_LEFT_INTERVIEW_H
#define CONCEPTRODON_TYPELIVORE_RECONFORMED_LEFT_INTERVIEW_H

#include "conceptrodon/microbiota/typella/unconformed_left_interview.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct ReconformedLeftInterview
{
    template<typename Interviewer>
    struct ProtoMold 
    {
        template<template<typename...> class Operation>
        using Road = Typella::UnconformedLeftInterview<Operation, Interviewer, Elements...>;

        template<template<typename...> class Operation>
        static constexpr auto Road_v 
        {Typella::UnconformedLeftInterview<Operation, Interviewer, Elements...>::value};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif