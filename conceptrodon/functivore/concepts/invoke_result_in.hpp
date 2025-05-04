// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_INVOKE_RESULT_IN_H
#define CONCEPTRODON_FUNCTIVORE_INVOKE_RESULT_IN_H

#include "conceptrodon/functivore/get_invoke_return_type.hpp"
#include <concepts>

namespace Conceptrodon {
namespace Functivore {

template<typename Fun, typename Result, typename...Args>
concept InvokeResultIn
= std::same_as<typename GetInvokeReturnType<Fun>::template Mold<Args...>, Result>;

}}

#endif