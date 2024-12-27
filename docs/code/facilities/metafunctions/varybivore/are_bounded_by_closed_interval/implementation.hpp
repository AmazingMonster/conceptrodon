/************************/
/**** Implementation ****/
/************************/

template<auto Lower, auto Upper>
struct AreBoundedByClosedInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Lower) && not (Upper < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < Lower) && not (Upper < Variables))) };
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
// Create a closed interval [1, 4].
template<auto...Args>
using Metafunction
= AreBoundedByClosedInterval<1, 4>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4, 5>::value);