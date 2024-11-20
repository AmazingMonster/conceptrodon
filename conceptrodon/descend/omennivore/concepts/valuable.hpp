// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_VALUABLE_H
#define CONCEPTRODON_OMENNIVORE_VALUABLE_H

#include <type_traits>
#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include "conceptrodon/varybivore/concepts/clarify.hpp"

#include "conceptrodon/descend/microbiota/ominuci/is_value_immediate.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Valuable
=   Mouldivore::Confess<std::is_const, const decltype(Structure::value)>
&&  Varybivore::Clarify
<
    Ominuci::isValueImmediate<decltype(Structure::value)>,
    Structure::value
>;

}}

#endif