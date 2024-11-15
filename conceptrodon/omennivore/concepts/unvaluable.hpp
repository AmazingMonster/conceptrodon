// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNVALUABLE_H
#define CONCEPTRODON_OMENNIVORE_UNVALUABLE_H

#include <type_traits>
#include "conceptrodon/microbiota/ominuci/is_value_immediate.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Unvaluable = not requires 
{
    requires std::is_const_v<const decltype(Structure::value)>;
    requires Ominuci::isValueImmediate(Structure::value); 
};

}}

#endif