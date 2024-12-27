/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Label ****/
template<typename Treasure, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Treasure;
};

/**** Vay ****/
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};

/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct Amid
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Vay<Variables>, std::integral_constant<size_t, I>>...
    {
        // We bring every `idyl` from its base class to the current scope.
        using Label<Vay<Variables>, std::integral_constant<size_t, I>>::idyl...;
    };

    template<size_t I>
    struct ProtoPage
    {
        // We ask the compiler to find an `idyl` that
        // declares a parameter of type `std::integral_constant<size_t, I>`.
        // If found, the value result of the return type
        // of such `idyl` is the variable of index I in the list.
        static constexpr auto value 
        {
            decltype
            (
                Detail<std::make_index_sequence<sizeof...(Variables)>>
                ::idyl(std::integral_constant<size_t, I>{})
            )::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

static_assert(Amid<0, 1, 2, 3>::Page<3>::value == 3);