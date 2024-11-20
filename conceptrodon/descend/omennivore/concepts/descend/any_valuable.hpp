// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_VALUABLE_H
#define CONCEPTRODON_OMENNIVORE_ANY_VALUABLE_H

#include <type_traits>
#include "conceptrodon/varybivore/concepts/confess.hpp"
#include "conceptrodon/descend/microbiota/ominuci/is_value_immediate.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_valuable.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyValuable 
= (...||(
       std::is_const<const decltype(Structures::value)>::value
    && Varybivore::Confess
    <
        Ominuci::isValueImmediate<decltype(Structures::value)>,
        Structures
    >
));

template<typename...Args>
concept AnyValuable
=   JustAnyValuable<Args...>
||  AllValuable<Args...>;

}}

#endif