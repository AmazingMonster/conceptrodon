/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct Among {};

template<auto First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { static constexpr auto value {First}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    { 
        static constexpr auto value 
        {Among<Others...>::template ProtoPage<I - 2>::value};
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    { static constexpr auto value {First}; };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    { static constexpr auto value {Second}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

static_assert(Among<0, 1, 2, 3>::Page<3>::value == 3);