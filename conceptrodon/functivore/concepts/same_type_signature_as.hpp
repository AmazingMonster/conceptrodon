// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_SAME_TYPE_SIGNATURE_AS_H
#define CONCEPTRODON_FUNCTIVORE_SAME_TYPE_SIGNATURE_AS_H

#include <concepts>
#include "conceptrodon/functivore/get_type_signature.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename Arg, typename Given>
concept SameTypeSignatureAs
= std::same_as<GetTypeSignature<Arg>, GetTypeSignature<Given>>;

}}

#endif