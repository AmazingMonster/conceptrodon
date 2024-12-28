<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::FoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-fold-left-first">To Index</a></p>

## Description

`Mouldivore::FoldLeftFirst` accepts an operation and returns a function.
When invoked, the function left-folds its argument list using the operation with the first argument as the initiator.

<pre><code>   Oper
-> Init, Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;
   Oper&lt;
      &vellip;
   Oper&lt;
   Oper&lt;
       Init, Arg<sub>0</sub>
   &gt;, Arg<sub>1</sub>
   &gt;, Arg<sub>2</sub>
      &vellip;
   &gt;, Arg<sub>n</sub>
   &gt;</code></pre>

## Type Signature

```Haskell
FoldLeftFirst
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct FoldLeftFirst
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
/**** Subtract ****/
template<typename A, typename B>
struct SubtractHelper
{
    using type = std::integral_constant
    <int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= FoldLeftFirst<Subtract>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

/**** Test ****/
static_assert(Result::value == -9);
```

## Implementation

We will implement `FoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct FoldLeftFirst
{
    template<typename...Elements>
    struct Detail {};

    // Base Case:

    // Fold once.
    template<typename Initiator, typename Element>
    struct Detail<Initiator, Element>
    {
        using type = Operation<Initiator, Element>;
    };

    // Fold twice.
    template<typename Initiator, typename First, typename Second>
    struct Detail<Initiator, First, Second>
    {
        using type
        =   Operation<
            Operation<
                Initiator, First
            >, Second
            >;
    };

    // Recursive Case:

    // Fold twice, handle the first three parameters,
    // and recurse using the rest.
    template<typename Initiator, typename First, typename Second, typename...Others>
    struct Detail<Initiator, First, Second, Others...>
    {
        using type
        = Detail<
            Operation<
            Operation<
                Initiator, First
            >, Second
            >, Others...
        >::type;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIAAcAKykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkizp9GyCTE13xxfXt2f/Zx%2BV0uVwImGeBjBJn8bjBEI%2BmGhsIAnulGKxMAA6bHQ7B3ZAGBQKO4AeTRxA%2BuVxIMmxC8DjuADFPOhQpgqARGXhiJMQSYAOxWa53EV3OEvBFIgio9FsbGY7CvRgEBTU4Wi2n0gh3AAimFadDuAqs/J10KFwPVIt2uzuFiYSjubgd7D5VruNqZLLuAm2mJBorF4IlUJh0rRzDYjwYOQ%2BJFIYplkcwd0V4OVaqugc1DL1BtoSIeMcccbIqaVgkzgeNAcDoq82SMibRRv8OtJ5MpAkLxbwpYTabeBGp/gt1dN5rdWdFnuZtHQYoA7ng/bWReLIYiw0mMdHY0Qy%2BHZSmuTyCAmj8m7kJMGgGOgqxqCHTc/qmHQe/v40zuZMEze7wffxsDXI1BVAwMGwiYBm0Rd1qzbUUyQSLsGCRCC6xFZCKSadD4Mwusiy/MtT15fDMNxf9bwEB9yLrEcx1FAUzVHKdA09AAlW9NmyAA3FNnSUEA2JnW05wXAhl22BMEEMdB6DFBAUxoM9FOITAU3SNoMTBHlSFAz05LudTkB4lMoKbAglOMzBJn9d0N0lbcI13IiSwPC8dyjUjz1gq8AJozyXLlbESSshJVWA0Cc21PN3wLGE3L7DyfzPKjAITMKlJ5eVHxFGs6IsmCjww/LELij8YVKutsNQvDpwIpDO1wqq6MapL%2B1SsiGsa1tsHSmjqoQ/rSXCnKcTo3EQBAErWPdZjJ2uUDHNDFFgqxbErmAdT00ESKQPdIq7gAWW9aF2wqhK3C2nahwUXLgOm2aLQWubLRuAF/iBP59lTVRWBeFNvhBH7PvOKdzH8CICS8LBWzWzAAH1n3fFVMxB45ry8WIUYZYHrhWrcEavK4guPO1MxirGcYpBwAAkGnJPlwMOxtiplVt20mdBpoiMFtrERG73mSt5phPmEyuabeLELwUwAWjtaXZa3EC3tel6CeDTcpS8jbMSuYhgH2kEjqEbHce1c7qcthnaCZmFDeNh7sCemVFven6TrfKgvAYBxci%2BcGtfhVbLwxeUnZN64juOn2/YDgQjSWxDxLZDkfKRc2aaYBwppAU75yRKOXY9jH7i4hQvFobV8auI7K%2Brq3ELj1pff93CU7caKCB5kA%2BcwAXaCFgQReHcXBATLhKJ7vuB6HkeGDHpEJbufwZ/dbnecEQeKWH4XWkrCffMkDeeq3/ud4Xg/DHHtxV/XqKU7VzWPvuAAVWza%2BDq55kcZBEYOiUO0CAjca7K28Cmc61t5YAE4Vjmg4GsWgnAUi8D8BwLQpBUCcG7pYawdwFAbC2FAsw/geCkAIJoJBawADWIAUiSExBoJIZgzCwNgVwFILCkhcH5PyaQKCOCSF4CwCQGgNCkAwVgnBHBeAKBAJIqhmCkGkDgLAGAiAQAbAIOkLw54KAQDQM8OgCQogYk4KoJIgR5aBEkHcYAyBkB3CkJiMwvBMD4APHgHmXAZCCBEGIdgUh/HyCUGoahpBdB%2BMXBSdInAeDINQegyJsiST6L0dqVAVA7hWJsXYhxTiXFMLMHcCAHgTH0GIEaMhXAVi8GUVoNYEAkDGPSKYsghi2kdJAMAKQZg%2BB0F0goiAsRImxAiG0ZECTeATOYMQZEJJYjaFvMoihxihwkgYLQaZKjSBYFiF4YAzpaC0AUdwXgWAWCGGAOIPZ%2BATKOH4ucrBmBVDcTBDM8gO8hFYNoHgWIFIFkeCwJE58eAxEXNIPxYgsQsiYD1Ncow/yjDULWFQAwxsABqeBMCLmQhgih/AAmiHECE4lYSVDqD2dE/QNyUDWGsPoAFCjIBrFQOkJo5z5bc3OqYfBlgzAyJhcQHxtl4BrDsKs3ILh7wzD8H4sIEQRjVDGH4koOQBDyr0BqpoixRiJD8VKxOzQpgdE8F0PQxqmgDHaPq1VhrbBmu1Uas19rlh1PWJsbYEgkkcDQVI1JnBcnWNsfYxxzjXGlIgLgQgJAankPqZQtFawlJMCwIkCAdCQCSH8JiWB/gBEaEkGYSQgQJEpECLA/QnARGkDEeQzEgQuCBCSLA3hgRGFcILcEaRvBZHyMUcmlRzTNEtO0Rk/R5BKDdKqeYtgnA2gsF4vyeWTB8QGCbFwWBmIuDMI8V4kgPi9AUsCWS6QFLFBUsiboAZsSmDxIuX6gNfbsGcHSbo/RPocl5LDRum5Lid17o0GUip7SqkJrMEmxpqjx2zoSNOoxqBKljAJDc7dXBJE0BrhFSgYy9lzKmV8wjCylkrIcF8jZyotk7MiQco5JyzlfKuTcu5WCHnSueZEt5HydgUIHr83g/zAVTJBTsLB4LIUUJhXCpQiLWPQTRXwTFCgcV4oJV809pLgkXtkFeiJNKQADM3cYRllhmWxFZVm7BnLcjct5W2flVhBXCoSKKrAVnJUNGlc4CArgXUhHvO6tVGQsiaryBawo6qwt6uVUsEL1r%2BjOsiwq3oPnTULDiwaq1yWCipfmHarLDrfVepISVoRL6g0cBDfk%2BxaGt1AeYWU2NB4E11IaSm0gaaM2UD9XWhtO7i38hSLA/h/gS1lskH419A7bBDpg6O%2BA46dGZMQ/B4g86dhLoKSwBQvFnG8W3ZiTckwD1xvcye2QZ6dOhP09SrBuh/CkHvY%2BxJNb/UpL2WkydWSf07b2wdo7J3tTlOQ%2BBhICb/DQaU3BsHHS1tw6qSAfb6R0iI0O7AxGwPEaqDsYMnDPI8PjMmQs4jJPFnLNWZR5Dmztm7PY5gQ5xyxBMahSx5F4nLnck4%2BKvZPHTKfKhQJyJwmgXIjE2C0VUneAyfhfJ5FimR3KaYNi3F%2BKIyaau9piQunBB3ZvQEOlqKnNMuE55mzXLOC7C3iblz/aRVivN4l3z/mUt6CVZUbL0XSi5AC7q3IwXHXO4y9MN3RrvMmttUMIrHqnWDACwV6PnviueqId64Jz7PsyODbj%2Bxu39t3Ax8dhEkxmuHuqZDdrw6mmpswOmsY1mhH9aMzu/w/gUjcKmxItv/JW2Bq%2B5wQdSjOv0MkCkfNfD%2BQSKSJIThXBWFmGCEI/wWf%2B2D%2BrzQ977j%2B/Z7kRvlYawYXZGcJIIAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/fold_left_first/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/fold_left_first.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/fold_left_first.test.hpp)
