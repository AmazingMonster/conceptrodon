// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_SENSIBLE_GRADE_H
#define CONCEPTRODON_TYPELIVORE_SENSIBLE_GRADE_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct SensibleGrade
{
    template<template<auto...> class Operation>
    struct ProtoRail 
    {
        template<template<typename...> class Paper>
        using Road = Operation<Paper<Elements>::value...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

}}

#endif