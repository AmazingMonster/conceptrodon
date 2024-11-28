// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ANY_H
#define CONCEPTRODON_VARYBIVORE_ANY_H

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Any
{
    static constexpr bool value
    { (...||(static_cast<bool>(Variables))) };
};

template<auto...Variables>
constexpr bool Any_v
{ (...||(static_cast<bool>(Variables))) };

}}

#endif