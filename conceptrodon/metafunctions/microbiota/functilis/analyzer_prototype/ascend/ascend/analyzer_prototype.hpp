// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifdef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_STATE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_STATE has already been defined"
#endif

#ifdef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_FLAG_VALUE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_FLAG_VALUE has already been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#define CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_STATE
#define CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_FLAG_VALUE  \
    0
#include "conceptrodon/metafunctions/microbiota/functilis/analyzer_prototype/ascend/ascend/ascend/analyzer_prototype.hpp"
#undef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_STATE
#undef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_FLAG_VALUE
/******************************************************************************************************/




/******************************************************************************************************/
#define CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_STATE   \
    volatile
#define CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_FLAG_VALUE  \
    CONCEPTRODON_NUCLEOLUS_VOLATILE_FLAG
#include "conceptrodon/metafunctions/microbiota/functilis/analyzer_prototype/ascend/ascend/ascend/analyzer_prototype.hpp"
#undef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_STATE
#undef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_FLAG_VALUE
/******************************************************************************************************/
