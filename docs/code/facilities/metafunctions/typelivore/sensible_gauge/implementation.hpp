/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct SensibleGauge
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        // Multiple Elements
        // Multiple Containers
        template<template<typename...> class...Devices>
        struct Detail
        {
            using type = Operation
            <Devices<Elements>::value...>;
        };
        
        // Multiple Elements
        // One Container
        template<template<typename...> class Device>
        struct Detail<Device>
        {
            using type = Operation
            <Device<Elements>::value...>;
        };

        template<template<typename...> class...Devices>
        using Road = Detail<Devices...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<typename Element>
struct SensibleGauge<Element>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        // One Element
        // Multiple Containers
        template<template<typename...> class...Devices>
        using Road = Operation
        <Devices<Element>::value...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Transformations ****/
template<typename Element>
struct AddZero 
{ 
    static constexpr auto value
    {Element::value}; 
};

template<typename Element>
struct AddOne
{ 
    static constexpr auto value
    {Element::value + 1}; 
};

template<typename Element>
struct AddTwo
{ 
    static constexpr auto value
    {Element::value + 2}; 
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result 
= SensibleGauge<std::integral_constant<int, 0>>
::Rail<Operation>
::Road<AddZero, AddOne, AddTwo>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = SensibleGauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>
::Rail<Operation>
::Road<AddOne>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = SensibleGauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>
::Rail<Operation>
::Road<AddZero, AddOne, AddTwo>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);