// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_RETURN_TYPE_CONSTRAINED_ASSIGNMENT_OPERATOR_AVAILABLE_H
#define CONCEPTRODON_FUNCTIVORE_RETURN_TYPE_CONSTRAINED_ASSIGNMENT_OPERATOR_AVAILABLE_H

#include <utility>

namespace Conceptrodon {
namespace Functivore {

template<typename To, template<typename...> class Predicate, typename By>
concept ReturnTypeConstrainedAssignmentOperatorAvailable
= Predicate<decltype(std::declval<To&>()=std::declval<By>())>::value;

}}

#endif