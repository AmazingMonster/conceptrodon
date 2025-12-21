// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_NOT_RVALUE_REFERENCE_QUALIFIED_H
#define CONCEPTRODON_FUNCTIVORE_NOT_RVALUE_REFERENCE_QUALIFIED_H

#include "conceptrodon/concepts/mouldivore/deceive.hpp"
#include "conceptrodon/metafunctions/functivore/is_rvalue_reference.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename F>
concept NotRvalueReferenceQualified
= Mouldivore::Deceive<IsRvalueReference, F>;

}}

#endif