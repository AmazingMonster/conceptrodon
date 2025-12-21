// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UPEND_H
#define CONCEPTRODON_TYPELIVORE_UPEND_H

#include <cstddef>
#include "conceptrodon/utilities/label.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Upend
{
    template<template<typename...> class, typename>
    struct Detail {};

    template<template<typename...> class Operation, size_t...I>
    struct Detail<Operation, std::index_sequence<I...>>
    : public Label<Elements, std::integral_constant<size_t, I>>...
    {
        using Label<Elements, std::integral_constant<size_t, I>>::idyl...;
        using type = Operation
        <decltype(idyl(std::integral_constant<size_t, sizeof...(I) - I - 1>{}))...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements..., std::make_index_sequence<sizeof...(Elements)>>::type;
};

}}

#endif