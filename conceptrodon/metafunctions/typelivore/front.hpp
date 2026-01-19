// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_FRONT_H
#define CONCEPTRODON_TYPELIVORE_FRONT_H

#include "conceptrodon/metafunctions/microbiota/typella/fore.hpp"
#include "conceptrodon/utilities/tyy.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename First, typename...Elements>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Typella::Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Tyy<First>{}, Tyy<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<First>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    using type = First;
};

}}

#endif