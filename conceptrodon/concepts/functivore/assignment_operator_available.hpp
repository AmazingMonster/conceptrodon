// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ASSIGNMENT_OPERATOR_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_ASSIGNMENT_OPERATOR_AVAILABLE_H

#include "conceptrodon/concepts/typelivore/nice.hpp"
#include <utility>

namespace Conceptrodon {
namespace Functivore {

template<typename To, typename By>
concept AssignmentOperatorAvailable
= Typelivore::Nice<decltype(std::declval<To&>()=std::declval<By>())>;

}}

#endif