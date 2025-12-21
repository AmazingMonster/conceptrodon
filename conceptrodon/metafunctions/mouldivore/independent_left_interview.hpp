// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_INDEPENDENT_LEFT_INTERVIEW_H
#define CONCEPTRODON_MOULDIVORE_INDEPENDENT_LEFT_INTERVIEW_H

#include "conceptrodon/metafunctions/microbiota/moldiae/independent_left_interview.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class...Predicates>
using IndependentLeftInterview = Moldiae::IndependentLeftInterview<Predicates...>;

}}

#endif