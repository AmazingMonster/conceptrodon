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

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct Amid
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Elements, std::integral_constant<size_t, I>>...
    {
        // We bring every `idyl` from its base class to the current scope.
        using Label<Elements, std::integral_constant<size_t, I>>::idyl...;
    };

    template<size_t I>
    struct Hidden
    {
        // We ask the compiler to find an `idyl` that
        // declares a parameter of type `std::integral_constant<size_t, I>`.
        // If found, the return type of such `idyl` is the element
        // of index I in the list.
        using type = decltype
        (
            Detail<std::make_index_sequence<sizeof...(Elements)>>
            ::idyl(std::integral_constant<size_t, I>{})
        );
    };

    template<auto...Agreements>
    using Page = Hidden<Agreements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** SupposedResult ****/
using SupposedResult = int***;

/**** Result ****/
using Result = Amid<int, int*, int**, int***>::Page<3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
