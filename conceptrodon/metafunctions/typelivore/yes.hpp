// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_YES_H
#define CONCEPTRODON_TYPELIVORE_YES_H

namespace Conceptrodon {
namespace Typelivore {

template<typename...>
struct Yes
{
    static constexpr bool value {true};
};

}}

#endif