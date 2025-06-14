// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ANALYZER_H
#define CONCEPTRODON_FUNCTIVORE_ANALYZER_H

#include "conceptrodon/microbiota/functilis/analyzer_intermediate.hpp"
#include <type_traits>

/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template<typename...Args>
using Analyzer = Functilis::AnalyzerIntermediate<std::remove_cvref_t<Args>...>;

}}
/******************************************************************************************************/

#endif
