// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_RAILLIVORE_AGENT_H
#define CONCEPTRODON_RAILLIVORE_AGENT_H

namespace Conceptrodon {
namespace Raillivore {

template<template<template<auto...> class...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
    struct Detail<Stockroom<Sequences...>>
    { using type = Operation<Sequences...>; };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

}}

#endif