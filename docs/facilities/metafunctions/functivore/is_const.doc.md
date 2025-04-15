<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsConst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_const">To Index</a></p>

## Description

`Functivore::IsConst` accepts a function-like type. It returns true if the type is `const` qualified and returns false if otherwise.

## Type Signature

```Haskell
IsConst
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsConst
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

/**** Tests ****/
static_assert(! IsConst<decltype(fun)>::value);
static_assert(IsConst<AbominableFun>::value);
static_assert(! IsConst<decltype(FunAddr)>::value);
static_assert(IsConst<decltype(&Tester::fun)>::value);
static_assert(IsConst<FO>::value);
```

## Implementation

The implementation of `IsConst` relies on extracting the qualifiers and specifiers of the function-like type using the metafunction `Analyzer`.

```C++
template <typename F>
struct IsConst
{
    static constexpr bool value
    { static_cast<bool>((1 << 6) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsConst_v
{ static_cast<bool>((1 << 6) & Analyzer<F>::value) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcAJykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3MhhvhBJDsP9/p9NhcTsxaABPABe0VeO1%2BBEwLESBiJEKhBExd2YbAR/2GxC8DjRGJx0WUxFQRCpdwhAHYrPyrpCrKd/kSSWTMBS3LzGKwZQAlTAEUgXeW0zAAOl1J2IwAU9NOjOZBFZYnZxE53O51MwkLcKoIEH1ht12rmxr%2Bgv%2BF39F0mjmQFzQDGGmFUiWIgYI6BAIC8wQIgLMAH1zQA3MReGUmQVcWWOi6A/MiwFin3lysS4mkpjkx2axUXZ3q5tsD1uo2AxEmghMlnoy2461cnn2x3O10GhQeuahgTDb35ysB2MNvAhsMRqMx2EJpOCVMZi7Z7x5gtFqEXABsArcF0LjuLpeFoqR74rSNOkvrRKbe0tQuAAxBhvVNIc2VHEALkSLwIloLcLSxUcbQnO5HTAhEBSFasfxOP9pUAmkW2w3sGQHM0UKtLCGE2b1YPgxDkOHVCOXHO1MKhci%2Bx9NcAyDZCdyJPdY3jRNkxPLMcwdU511XP11wDZ8oWLMwHyU5SLggLTtJU69H0BCEAFY%2BP05S2KtdCuIdHjwN7BNz1zPT1y9eSAzLD9xS/GtfzrYjKSAlsAFliTA9tgrYC46kHAhljsvjIPNKzR0dMKWDAmKqIcBKEwYijTiYhCkJDVKONteV0vChy%2BMUjz/SE7cl1E6NxMPKT0xki89Pqk4LNUtxi2ffkhoa5TdPGgbDJLUzzIsgNyrHSrJyhDLeKc2TXIDdz%2Bs83yCPXLxUiMUMDAUBQM3tCkrmyuKEu8qtHtrKUGzsuUoplECAHlvWITAAEck3%2Bl5/qBvAQdw8xbx%2BhNUDuYgGxICAvW/d9%2Bzimi0p437CpOYqWLK6DokdLBQXlXSzBh764YRpHiBR1G6t9camsXcNWv3OMOuPLqzy28a%2Bum/Mxr27TJrFhbBuGubtu0pbScwcn7Up6naeienGYRTaeqmnbeoO8VxuO4JgDOpgLquvlIVun7nsNv4Pm%2BZ2fmRXYLgASSlYlGHqGp8W2X4URd75fhe/88yC0jopAiCcvND2FA8DnPwExq/eElrIzaiJUE8fndcl1cN2DNNRGXKFc88BEoGlm9bwXaGsZJnjtZAZzMEbh2vO/I3CICt7ZQ7L7vRE7OYyr2hPaTlq00zVOS63MuLYIR1J5riA68fBuISp5viCwtuO67/C%2B%2BDkOg/d7BVFYUkZTeN2Q4fs/3aoLwGAcdIXmfk5giQkILjJguG/BgEBkzqmTJsL0goLj/XisQBgFwNCigFCKF%2BlwmC5xYMETB9BgHv0/kuAOhx/gm1OicLBODEKYBAu/G6gDBBgMEBAwQUD2YVz8mcV%2BBD/bJGTNEb%2BBJ/h/2CDKJgXgiCgXficdA6AYzF2hiA1Bz0naXD4YIPEki2AlDxCAwh4ZiG/GShcAAKs8IkB8fJpwYf/GUQCQFMLVAwggbCRK4VgaqZYiDkEVmUT5U%2BjsuGXD0f7VAERtBKwIIIwOlFMZ2ysXpIB8MNZEAZnMRxLCXELjccXOBXikEoK8v4lRQTtimPMdEkh/ZNzIDTBbJQjQIBgDANPZOFc3Bk1oBTEBTMda5lRpWJqdSLrRBdInNpq8oQUNQNg5g1DaG1T6Z3R6Qz6mjKaS08ZLVFbKzuBABZMi5G9PbrJAZlEanDIaWMmeKcoSdIptDMxEYYggB6UfU5KyM61LWY0rZty3B20cici8ZzTgcAWLQTgJleB%2BA4FoUgqBOBDUsNYQMSwVh5iBDwUgBBNDgoWAAaxACZQE2p%2BQmRMvyLgJkzBcAABx0vKGYaQkKOCSF4CwCQGgNCkFhfCxFHBeAKBADy3FcLwWkDgLAGAiAQBLAIPBNUFAIBoBJHQaIoRFScFUHS28ABaW8kgLjAGQCGKQ2ozC8EwPgVJeB4xtH4IIEQYh2BSBkIIRQKh1DitILoNoAB3RGiROA8AhVCmFeKEWcG%2BhIxVFxUBUAuDq/VhrjWmqfJIC1OkPBqvoPIrFcxeBiq0AsCASBVWJHVWQZVFaq0gGAFIMwfA6AWOFRACIkaIg4OIJiENvAu3MB7d9cJkS%2B2kFVWwQQ30GBYkjVgCIXhgBuDELQYV3BeBYBYIYYA4gfX4H%2Bp/TMzxI2RiVhItY2L%2BGsvhUhCIiMe0eCwJGgceBOXrtIEe4guclA3C3UYf%2BoBxULCoAYQ0AA1J4/rvo0jHY64QohxBurg56tQka/X6G3Sgaw1h9B4AiMKyACx4Y1DXXq2ENtTAossGYfln7iB2uPYR9okT0guAYO4TwLR/DsemP0MoSQUhpAEGMVoAm8jpF4zo/jdgWMCC6KMTj4xmP6Pkz0URMwBgTBGE0RTonJiNEk7MLgCwFDotWBIMNHBoW8sjQKpNuqDVGpNWazNGkIC4EICQXegJjNFrxXMBYCBMBMCwDEFGpAiWSFJXEQE/JJAaEkMy283KTK3gSKy9lpBOU%2Be1LeLgt46VxEZbeEykhqUxdvDZn1AqhUipxf5yVMqy1ytjRI8glBa15s1WwTgDQWCZn5Hqpg5tTrxG1FwbU8LrWefo/a918GXUSGkMhpQqGfW6CbYGpgwb12Wes3y3gAqY0KokfGxNybHMjbNmNibGhs0zMrXm7zZhC31aA5K8tD2q3tZVV9vNKADBGHiFwHlNAukCMoB2n1A6Gi9vfTDodI6HBjonb7ads692YAXUulda7sWbu3bu%2BF%2B6WNHrXVN1QZ6iRjqvZG2997MSPrWPCl9b7sWfu/ZgX9hPTYNZA0wcDkHoOMFg7IZ1iHluyBQ96%2BFG2MNGCw1Rmwt6CPheI1/TgZG4wUew9R2j0RZuMfCzJ/RbGONZFE4EdTfGciCZqCJ234mCjW6k3oE3NRVMO4mFUWTtRtOGc07YbTXug9TBd0ZkzZnXV7YjdVzg9mU1GtBNup8cRxuTZ0h51J3nfNvZLYF4LoXKCWcy9ltPCXyVxH5PyQEiXJCGraAdqNgrbB1eLRKqVsr5WKp%2B51jVWqOB9dTSwBQmYQyZjG9KYYVqbUkDtXoOD4vXWS49atmXOgQCAlIFtnbob9Dhqq/y6NrXzQJqTcP0f4/J9vWGPd3NeJzCAkBK99vpbPv3%2BrR1v7Awx%2BJESHPeINMKfAgNMVQQ1ZtcHYgNtKHeFBHOHbFOA4dCJZHd9VHKdGdOHYnLHRdZdWgVdMdAnf9ZnDdCGUnY9H1U9ZAc9GnDRa9XgenWHJnZ9ejNnXgDnFILnYkHnBXd7fnQXTAKDGDd9RfBDZfebaXNDTfeXYwXXZXPDVXIjRIEjTgdYA8SjKwPXQ7OjBjBQ5TGoM3EPK3IoG3NoXIITDIXTR3cwgPaTH3FTYPSw73DoOTf3cPQPfTHTC3N3Vw4w13YzRYZYczfw1lfbWzePMAo1EfMfM8a/IkW/dzWffNHzF/fzAvELAYcLDLDlEAMwNPJ/ClBLEHDQJ/fkArQ/Q7TgWrUVVIiLEAevC1SQRLOlSQfkRlelOlUo/fDgQEWPI/FvV/SzS1co5vPzIDBYT9VIZwSQIAA)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_const/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/is_const.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_const.test.hpp)
