// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_INVOKE_RESULT_IN_H
#define CONCEPTRODON_FUNCTIVORE_INVOKE_RESULT_IN_H

#include "conceptrodon/concepts/mouldivore/passed.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Functivore {

template<typename Fun, typename Result, typename...Args>
concept InvokeResultIn
= Mouldivore::Passed<std::is_invocable_r, Result, Fun, Args...>;

}}

#endif