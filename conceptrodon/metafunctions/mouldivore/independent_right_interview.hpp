// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_INDEPENDENT_RIGHT_INTERVIEW_H
#define CONCEPTRODON_MOULDIVORE_INDEPENDENT_RIGHT_INTERVIEW_H

#include "conceptrodon/metafunctions/microbiota/moldiae/independent_right_interview.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class...Predicates>
using IndependentRightInterview = Moldiae::IndependentRightInterview<Predicates...>;

}}

#endif