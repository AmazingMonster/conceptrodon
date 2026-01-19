/************************/
/**** Implementation ****/
/************************/

template<typename...Crops>
struct BiHarvest
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<typename Crops::type...>; 
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    
    template<template<auto...> class Operation>
    struct Hidden
    {
        using type = Operation<Crops::value...>; 
    };

    template<template<auto...> class...Agreements>
    using Rail = Hidden<Agreements...>::type;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Crop ****/
template<int I>
struct Crop
{
    using type = std::integral_constant<int, I>;
    static constexpr int value {I};
};

/**** Operation ****/
template<typename...>
struct Oper_0;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction_0 = BiHarvest
<
    Crop<0>,
    Crop<1>
>
::Road<Args...>;

/**** SupposedResult ****/
using SupposedResult_0 = Oper_0
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>
>;

/**** Result ****/
using Result_0 = Metafunction_0<Oper_0>;

/**** Test ****/
static_assert(std::same_as<Result_0, SupposedResult_0>);

/************************/
/**** Second Example ****/
/************************/

/**** Operation ****/
template<auto...>
struct Oper_1;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction_1 = BiHarvest
<
    Crop<0>,
    Crop<1>
>
::Rail<Args...>;

/**** SupposedResult ****/
using SupposedResult_1 = Oper_1<0, 1>;

/**** Result ****/
using Result_1 = Metafunction_1<Oper_1>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** Tyy ****/
template<typename Element>
struct Tyy
{
    using type = Element;
};

/**** Operation ****/
template<typename...>
struct Oper_2;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction_2 = BiHarvest
<
    Tyy<int>,
    Tyy<int*>
>
::Road<Args...>;

/**** SupposedResult ****/
using SupposedResult_2 = Oper_2<int, int*>;

/**** Result ****/
using Result_2 = Metafunction_2<Oper_2>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
