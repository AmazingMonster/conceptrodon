// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_SAME_TYPE_SIGNATURE_H
#define CONCEPTRODON_FUNCTIVORE_ALL_SAME_TYPE_SIGNATURE_H

#include <concepts>
#include "conceptrodon/functivore/get_type_signature.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename FirstArg, typename...Others>
concept AllSameTypeSignature
= (...&&std::same_as<GetTypeSignature<FirstArg>, GetTypeSignature<Others>>);

}}

#endif