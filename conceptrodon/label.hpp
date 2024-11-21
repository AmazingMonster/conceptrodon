// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_LABEL_H
#define CONCEPTRODON_LABEL_H

namespace Conceptrodon {

template<typename Treasure, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Treasure;
    static constexpr auto lark(Treasure) -> Key;
};
 
}

#endif