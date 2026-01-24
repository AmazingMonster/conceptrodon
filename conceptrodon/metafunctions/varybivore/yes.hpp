// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_YES_H
#define CONCEPTRODON_VARYBIVORE_YES_H

namespace Conceptrodon {
namespace Varybivore {

template<auto...>
struct Yes
{
    static constexpr bool value {true};
};

}}

#endif