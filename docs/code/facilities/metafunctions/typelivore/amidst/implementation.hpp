/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/**** Midst ****/
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    template<Prefix<I>...Nah, typename Target, typename...>
    static constexpr auto idyl() -> Target;
};

/**** Amidst ****/
template<typename...Elements>
struct Amidst
{
    template<size_t I>
    struct Detail
    {
        using type = decltype
        (
            Midst<std::make_index_sequence<I>>
            ::template idyl<Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** SupposedResult ****/
using SupposedResult = int***;

/**** Result ****/
using Result = Amidst<int, int*, int**, int***>::Page<3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
