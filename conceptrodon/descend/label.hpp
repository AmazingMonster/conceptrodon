// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_LABEL_H
#define CONCEPTRODON_LABEL_H

namespace Conceptrodon {

template<typename Element, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Element;
    static constexpr auto lark(Element) -> Key;
};
 
}

#endif