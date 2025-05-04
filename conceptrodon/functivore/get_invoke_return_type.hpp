// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_GET_INVOKE_RETURN_TYPE_H
#define CONCEPTRODON_FUNCTIVORE_GET_INVOKE_RETURN_TYPE_H

#include "conceptrodon/functivore/get_variadic_type_signature.hpp"
#include <type_traits>

/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template<typename Fn>
struct GetInvokeReturnType
{
    template<typename...Args>
    using Mold = std::invoke_result_t<GetVariadicTypeSignature<Fn>, Args...>;
};

template<typename Fn>
requires std::is_class_v<Fn>
struct GetInvokeReturnType<Fn>
{
    template<typename...Args>
    using Mold = std::invoke_result_t<Fn, Args...>;
};

}}
/******************************************************************************************************/

#endif
