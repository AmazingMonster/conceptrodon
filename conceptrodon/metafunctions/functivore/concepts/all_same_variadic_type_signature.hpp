// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_SAME_VARIADIC_TYPE_SIGNATURE_H
#define CONCEPTRODON_FUNCTIVORE_ALL_SAME_VARIADIC_TYPE_SIGNATURE_H

#include <concepts>
#include "conceptrodon/metafunctions/functivore/get_variadic_type_signature.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename FirstArg, typename...Others>
concept AllSameVariadicTypeSignature
= (...&&std::same_as<GetVariadicTypeSignature<FirstArg>, GetVariadicTypeSignature<Others>>);

}}

#endif