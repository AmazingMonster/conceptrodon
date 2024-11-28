// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMINUCI_IS_VALUE_IMMEDIATE_H
#define CONCEPTRODON_OMINUCI_IS_VALUE_IMMEDIATE_H

namespace Conceptrodon {
namespace Ominuci {

template<typename Type>
constexpr bool isValueImmediate(Type value)
{ return true; }

template<auto I>
concept ImmediateValue = isValueImmediate(I);

}}

#endif