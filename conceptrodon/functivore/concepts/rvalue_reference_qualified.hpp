// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_RVALUE_REFERENCE_QUALIFIED_H
#define CONCEPTRODON_FUNCTIVORE_RVALUE_REFERENCE_QUALIFIED_H

#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include "conceptrodon/functivore/is_rvalue_reference.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename F>
concept RvalueReferenceQualified
= Mouldivore::Confess<IsRvalueReference, F>;

}}

#endif