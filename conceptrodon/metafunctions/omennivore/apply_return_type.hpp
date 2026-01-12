// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_APPLY_RETURN_TYPE_H
#define CONCEPTRODON_OMENNIVORE_APPLY_RETURN_TYPE_H

/******************************************************************************************************/
namespace Conceptrodon {
namespace Omennivore {

template <typename Ret>
struct ApplyReturnType
{
    template<typename...Args>
    using Mold = Ret(Args...);
};

}}
/******************************************************************************************************/

#endif
