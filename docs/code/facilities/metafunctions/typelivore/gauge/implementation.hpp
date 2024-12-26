/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct Gauge
{
    // Multiple Elements
    // Multiple Containers
    template<template<typename...> class...Devices>
    struct ProtoRoad
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Elements>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    // Multiple Elements
    // one Container
    template<template<typename...> class Device>
    struct ProtoRoad<Device>
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Device<Elements>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Devices>
    using Road = ProtoRoad<Devices...>;
};

template<typename Element>
struct Gauge<Element>
{
    // One Element
    // Multiple Containers
    template<template<typename...> class...Devices>
    struct ProtoRoad
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Element>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Devices>
    using Road = ProtoRoad<Devices...>;
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
= Gauge<std::integral_constant<int, 0>>
::Road<AddZero, AddOne, AddTwo>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = Gauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>::Road<AddOne>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = Gauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>::Road<AddZero, AddOne, AddTwo>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);