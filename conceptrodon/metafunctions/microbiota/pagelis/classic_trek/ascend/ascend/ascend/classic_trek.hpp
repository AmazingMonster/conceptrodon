// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_CLASSIC_TREK_FUNCTION_NAME
#error "CONCEPTRODON_PAGELIS_CLASSIC_TREK_FUNCTION_NAME has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_CLASSIC_TREK_COMMITMENT_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_PAGELIS_CLASSIC_TREK_COMMITMENT_SYNOPSIS_TEMPLATE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_PAGELIS_CLASSIC_TREK_CONTINUATION_PARAMETER_CATEGORY
#error "CONCEPTRODON_PAGELIS_CLASSIC_TREK_CONTINUATION_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_PAGELIS_CLASSIC_TREK_CONTINUATION_PROTO_TEMPLATE
#error "CONCEPTRODON_PAGELIS_CLASSIC_TREK_CONTINUATION_PROTO_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_PAGELIS_CLASSIC_TREK_CONTINUATION_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_PAGELIS_CLASSIC_TREK_CONTINUATION_SYNOPSIS_TEMPLATE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_PAGELIS_CLASSIC_TREK_CONTINUATION_PARAMETER_CATEGORY
    ...Agreements
>
using CONCEPTRODON_PAGELIS_CLASSIC_TREK_CONTINUATION_SYNOPSIS_TEMPLATE
= CONCEPTRODON_PAGELIS_CLASSIC_TREK_FUNCTION_NAME
<
    CONCEPTRODON_NUCLEOLUS_COMMIT_SEPARATOR
    ::template CONCEPTRODON_PAGELIS_CLASSIC_TREK_COMMITMENT_SYNOPSIS_TEMPLATE
>
::template CONCEPTRODON_PAGELIS_CLASSIC_TREK_CONTINUATION_PROTO_TEMPLATE <Agreements...>;
/******************************************************************************************************/
