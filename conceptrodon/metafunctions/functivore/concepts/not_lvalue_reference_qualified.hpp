// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_NOT_LVALUE_REFERENCE_QUALIFIED_H
#define CONCEPTRODON_FUNCTIVORE_NOT_LVALUE_REFERENCE_QUALIFIED_H

#include "conceptrodon/metafunctions/mouldivore/concepts/deceive.hpp"
#include "conceptrodon/metafunctions/functivore/is_lvalue_reference.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename F>
concept NotLvalueReferenceQualified
= Mouldivore::Deceive<IsLvalueReference, F>;

}}

#endif