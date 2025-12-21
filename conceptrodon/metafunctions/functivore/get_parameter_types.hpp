// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_GET_PARAMETER_TYPES_H
#define CONCEPTRODON_FUNCTIVORE_GET_PARAMETER_TYPES_H

#include "conceptrodon/metafunctions/functivore/analyzer.hpp"

/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template<template<typename...> class Container>
struct GetParameterTypes
{ 
    template<typename...Args>
    using Mold = Analyzer<Args...>::template parameter_types<Container>;
};

}}
/******************************************************************************************************/

#endif
