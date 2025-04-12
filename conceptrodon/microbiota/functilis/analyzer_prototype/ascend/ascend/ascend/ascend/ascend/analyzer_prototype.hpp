// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/******************************************************************************************************/
#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_DEFAULT_VESSEL_IDENTIFIER
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_DEFAULT_VESSEL_IDENTIFIER has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_TYPE_SIGNATURE_IDENTIFIER
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_TYPE_SIGNATURE_IDENTIFIER has already been defined"
#endif

#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_TYPE_SIGNATURE_IDENTIFIER
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_TYPE_SIGNATURE_IDENTIFIER has already been defined"
#endif

#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_PARAMETER_TYPES_IDENTIFIER
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_PARAMETER_TYPES_IDENTIFIER has not been defined"
#endif

#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_RESULT_TYPE_IDENTIFIER
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_RESULT_TYPE_IDENTIFIER has not been defined"
#endif

#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VALUE_IDENTIFIER
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VALUE_IDENTIFIER has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_FUNCTION_NAME
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_FUNCTION_NAME has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_STATE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_STATE has not been defined"
#endif

#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_FLAG_VALUE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_FLAG_VALUE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_CONST_STATE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_CONST_STATE has not been defined"
#endif

#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_CONST_FLAG_VALUE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_CONST_FLAG_VALUE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_STATE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_STATE has not been defined"
#endif

#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_FLAG_VALUE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_FLAG_VALUE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_REFERENCE_STATE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_REFERENCE_STATE has not been defined"
#endif

#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_REFERENCE_FLAG_VALUE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_REFERENCE_FLAG_VALUE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_NOEXCEPT_STATE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_NOEXCEPT_STATE has not been defined"
#endif

#ifndef CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_NOEXCEPT_FLAG_VALUE
#error "CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_NOEXCEPT_FLAG_VALUE has not been defined"
#endif
/******************************************************************************************************/




/******************************************************************************************************/
template<typename Ret, typename...Args>
struct CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_FUNCTION_NAME
<
    Ret
    (
        Args...

        CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_STATE
    )

    CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_CONST_STATE
    CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_STATE
    CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_REFERENCE_STATE
    CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_NOEXCEPT_STATE
>
{
    using CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_TYPE_SIGNATURE_IDENTIFIER
    = Ret
    (
        Args...

        CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_STATE
    );

    using CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_TYPE_SIGNATURE_IDENTIFIER
    = Ret(Args...);

    template<template<typename...> class Container = CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_DEFAULT_VESSEL_IDENTIFIER>
    struct CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_PARAMETER_TYPES_IDENTIFIER_DETAIL
    {
        using type = Container <Args...>;
    };

    template<template<typename...> class...Agreements>
    using CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_PARAMETER_TYPES_IDENTIFIER
    = CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_PARAMETER_TYPES_IDENTIFIER_DETAIL <Agreements...> :: type;

    using CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_RESULT_TYPE_IDENTIFIER = Ret;

    static constexpr CONCEPTRODON_NUCLEOLUS_FLAG_TYPE CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VALUE_IDENTIFIER
    =   CONCEPTRODON_NUCLEOLUS_FUNCTION_FLAG
    |   CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VARIADIC_FLAG_VALUE
    |   CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_CONST_FLAG_VALUE
    |   CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_VOLATILE_FLAG_VALUE
    |   CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_REFERENCE_FLAG_VALUE
    |   CONCEPTRODON_FUNCTILIS_ANALYZER_PROTOTYPE_NOEXCEPT_FLAG_VALUE
    ;
};
