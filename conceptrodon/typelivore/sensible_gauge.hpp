// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_SENSIBLE_GAUGE_H
#define CONCEPTRODON_TYPELIVORE_SENSIBLE_GAUGE_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct SensibleGauge
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template<template<typename...> class...Devices>
        using Road = Operation<Devices<Elements>::value...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

}}

#endif