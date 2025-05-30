// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_MOLDIAE_TRIP_FUNCTION_NAME
#error "CONCEPTRODON_MOLDIAE_TRIP_FUNCTION_NAME has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_MOLDIAE_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_MOLDIAE_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_MOLDIAE_TRIP_CONTINUATION_PARAMETER_CATEGORY
#error "CONCEPTRODON_MOLDIAE_TRIP_CONTINUATION_PARAMETER_CATEGORY has not been defined"
#endif

#ifndef CONCEPTRODON_MOLDIAE_TRIP_CONTINUATION_PROTO_TEMPLATE
#error "CONCEPTRODON_MOLDIAE_TRIP_CONTINUATION_PROTO_TEMPLATE has not been defined"
#endif

#ifndef CONCEPTRODON_MOLDIAE_TRIP_CONTINUATION_SYNOPSIS_TEMPLATE
#error "CONCEPTRODON_MOLDIAE_TRIP_CONTINUATION_SYNOPSIS_TEMPLATE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
template
<
    CONCEPTRODON_MOLDIAE_TRIP_CONTINUATION_PARAMETER_CATEGORY
    ...Agreements
>
using CONCEPTRODON_MOLDIAE_TRIP_CONTINUATION_SYNOPSIS_TEMPLATE
= CONCEPTRODON_MOLDIAE_TRIP_FUNCTION_NAME
<
    CONCEPTRODON_NUCLEOLUS_COMMIT_SEPARATOR
    ::template CONCEPTRODON_MOLDIAE_TRIP_COMMITMENT_SYNOPSIS_TEMPLATE
>
::template CONCEPTRODON_MOLDIAE_TRIP_CONTINUATION_PROTO_TEMPLATE <Agreements...>;
/******************************************************************************************************/
