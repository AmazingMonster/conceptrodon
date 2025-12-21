// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMINUCI_IS_VALUE_IMMEDIATE_H
#define CONCEPTRODON_OMINUCI_IS_VALUE_IMMEDIATE_H

namespace Conceptrodon {
namespace Ominuci {

template<typename Type>
constexpr bool is_value_immediate(Type value)
{ return true; }

template<auto I>
concept ImmediateValue = is_value_immediate(I);

}}

#endif