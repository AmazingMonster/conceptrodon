// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CYTOPLASM_SELECT_SCALE_H
#define CONCEPTRODON_CYTOPLASM_SELECT_SCALE_H


namespace Conceptrodon {
namespace Cytoplasm {

consteval size_t select_scale(size_t count) 
{ 
    size_t depth {8}; 

    while(depth != 3)
    {
        if ((1 << depth) < count) 
        { return 1 << depth; };

        depth --;
    }

    return count;
}

}}

#endif