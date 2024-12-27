/************************/
/**** Implementation ****/
/************************/

template<auto Lower, auto Upper>
struct AreBoundedByLeftClosedRightOpenInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Lower) && Variables < Upper)) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(not (Variables < Lower) && Variables < Upper)) };
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
// Create a left-closed-right-open interval [1, 4).
template<auto...Args>
using Metafunction
= AreBoundedByLeftClosedRightOpenInterval<1, 4>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1, 2, 3, 3.5>::value);
static_assert(! Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4, 5>::value);