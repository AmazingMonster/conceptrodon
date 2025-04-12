// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifdef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_STATE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_STATE has already been defined"
#endif

#ifdef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_FLAG_VALUE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_FLAG_VALUE has already been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#define CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_STATE
#define CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_FLAG_VALUE  \
    0
#include "conceptrodon/microbiota/functilis/analyzer_prototype/ascend/analyzer_prototype.hpp"
#undef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_FLAG_VALUE
#undef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_STATE
/******************************************************************************************************/




/******************************************************************************************************/
#define CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_STATE   \
    ...
#define CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_FLAG_VALUE  \
    CONCEPTRODON_NUCLEOLUS_VARIADIC_FLAG
#include "conceptrodon/microbiota/functilis/analyzer_prototype/ascend/analyzer_prototype.hpp"
#undef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_FLAG_VALUE
#undef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_STATE
/******************************************************************************************************/
