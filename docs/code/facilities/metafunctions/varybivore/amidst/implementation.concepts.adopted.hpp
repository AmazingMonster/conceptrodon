/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Vay ****/
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};

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
template<auto...Variables>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value
        {
            decltype
            (
                Midst<std::make_index_sequence<I>>
                ::template idyl<Vay<Variables>...>()
            )::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Args>
using At = Amidst<0, 1, 2, 3>::Page<Args...>;

/**** Test ****/
static_assert(At<3>::value == 3);