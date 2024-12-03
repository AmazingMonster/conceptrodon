// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIS_LEFT_INSPECT_H
#define CONCEPTRODON_PAGELIS_LEFT_INSPECT_H

#include "conceptrodon/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Pagelis {

template<typename>
struct LeftInspect {};

template<size_t...I>
struct LeftInspect<std::index_sequence<I...>> 
{
    template<template<auto...> class Predicate, Prefix<I>..., typename OnDuty, typename...RestVayVariables>
    static consteval auto idyl()
    -> std::bool_constant<(...&&Predicate<OnDuty::value, RestVayVariables::value>::value)>;
};

}}

#endif