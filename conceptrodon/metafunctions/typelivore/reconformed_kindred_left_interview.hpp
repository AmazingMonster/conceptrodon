// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_RECONFORMED_KINDRED_LEFT_INTERVIEW_H
#define CONCEPTRODON_TYPELIVORE_RECONFORMED_KINDRED_LEFT_INTERVIEW_H

#include "conceptrodon/metafunctions/microbiota/typella/unconformed_left_interview.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct ReconformedKindredLeftInterview
{
    template<typename Interviewer>
    struct ProtoMold 
    {
        template<template<typename...> class Operation>
        using Road = Typella::UnconformedLeftInterview<Operation, Interviewer, Elements...>;

        template<template<typename...> class Operation>
        static constexpr std::make_signed_t<size_t> Road_v 
        {Typella::UnconformedLeftInterview<Operation, Interviewer, Elements...>::value};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif