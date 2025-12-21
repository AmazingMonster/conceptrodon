// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_AMONG_H
#define CONCEPTRODON_OMENNIVORE_AMONG_H

#include "conceptrodon/metafunctions/omennivore/typical_among.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...PackedVessels>
struct Among
: public TypicalAmong<PackedVessels...>
{

};

template<template<typename...> class Container, typename...Elements>
struct Among<Container<Elements...>>
{
    template<auto I>
    struct Detail
    {
        using type = Typella::TypicalAmong<Elements...>
        ::template ProtoPage<I>
        ::type;
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};

}}

#endif