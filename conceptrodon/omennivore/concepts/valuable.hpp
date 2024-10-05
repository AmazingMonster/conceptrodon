// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_VALUABLE_H
#define CONCEPTRODON_OMENNIVORE_VALUABLE_H

#include <type_traits>

namespace Conceptrodon {
namespace Ominuci {

consteval bool isValueImmediate(auto value) { return true; }

}

namespace Omennivore {

template<typename Structure>
concept Valuable 
=   std::is_const_v<const decltype(Structure::value)>
&&  Ominuci::isValueImmediate(Structure::value);

}}

#endif