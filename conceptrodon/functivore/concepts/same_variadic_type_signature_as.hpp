// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_SAME_VARIADIC_TYPE_SIGNATURE_AS_H
#define CONCEPTRODON_FUNCTIVORE_SAME_VARIADIC_TYPE_SIGNATURE_AS_H

#include <concepts>
#include "conceptrodon/functivore/get_variadic_type_signature.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename Arg, typename Given>
concept SameTypeSignatureAs
= std::same_as<GetVariadicTypeSignature<Arg>, GetVariadicTypeSignature<Given>>;

}}

#endif