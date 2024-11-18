// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_VALUABLE_H
#define CONCEPTRODON_OMENNIVORE_ALL_VALUABLE_H

#include <type_traits>
#include "conceptrodon/varybivore/concepts/divulge.hpp"

#include "conceptrodon/descend/microbiota/ominuci/is_value_immediate.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllValuable 
= (...&&(
       std::is_const<const decltype(Structures::value)>::value
    && Varybivore::Divulge
    <
        Ominuci::isValueImmediate<decltype(Structures::value)>,
        Structures::value
    >
));

}}

#endif