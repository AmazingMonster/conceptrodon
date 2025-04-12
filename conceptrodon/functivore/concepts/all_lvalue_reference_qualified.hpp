// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ALL_LVALUE_REFERENCE_QUALIFIED_H
#define CONCEPTRODON_FUNCTIVORE_ALL_LVALUE_REFERENCE_QUALIFIED_H

#include "conceptrodon/mouldivore/concepts/all_confess.hpp"
#include "conceptrodon/functivore/is_lvalue_reference.hpp"

namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
concept AllLvalueReferenceQualified
= Mouldivore::AllConfess<IsLvalueReference, Args...>;

}}

#endif