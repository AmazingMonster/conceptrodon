<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SetContains`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-set-contains">To Index</a></p>

## Description

`Varybivore::SetContains` accepts a set of nonrepetitive variables and returns a predicate.
When invoked by an argument, the function returns true if the argument is in the previously provided set and returns false if otherwise.

<pre><code>   Vs...
-> Arg
-> Arg &in; Vs... ?
   true : false</code></pre>

## Type Signature

```Haskell
SetContains
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct SetContains
{
    template<auto>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };

    template<auto>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

We will check whether `1` or `-1`  is inside `0, 1, 2`.

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction = SetContains<0, 1, 2>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1>::value);
static_assert(! Metafunction<-1>::value);
```

## Implementation

We will implement `SetContains` using the method presented in `boost::mp_set_contains`.

We will create a class that inherits every 'variable' we want to check against.
Then, when provided with an argument, we inspect whether it is a base of our class using `std::is_base_of`, subsequently determining whether the argument is one of the variables our class inherited early on.

To 'inherit' variables, we need a helper class that transforms variables into types.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Since inheriting the same type multiple times is illegal in C++, the initial list of arguments for `SetContains` must be nonrepetitive (hence the word `Set` in the name).

```C++
template<auto...Variables>
struct SetContains
: public Vay<Variables>...
{
    template<auto Inspecting>
    struct ProtoPage
    {   
        static constexpr bool value 
        {
            std::is_base_of
            <
                Vay<Inspecting>,
                SetContains
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxP4AHKQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxkkl2mA6ZQgRMxATZPn4Btpj2RQwNTQQlkTFxibaNza25HQrjA2FD5SNVAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimMmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGYwshvFhbiYwW4CABPZ4AfQIxCYhAUcOwIJBfz2twAakxEV9DkCCJgWMkDFS4W4mF4iMSmngmNF6DiQTNiF4HKzEXiAOwWW4zJiOZC3NAMGaYVTJYi3JksgBuYi8mFhopJxHZnMwJmF9zhYuNprBViu%2BIBdsBtruAEkafQ2IJJZlyQcgQT7QCgSCqa7JUb4arUAA6aN6g30bFg3FXXn8gi3ISYFqyTFykEgW7JLycvDSklC%2BGxjnxnHRyMi62XW5N27B2mhhkR25OuXPOpGblXZvi9Gp27KYioIjKJjAI2D5vGsVNkFDocSqUygTyxXK6KoTy3DXebUr1fL0Wns9rgjoEAgPAKFHRJhKFGoKiXq/L%2BGfr9DssMt2Ci9o4/aJqQv5/k2GZZh6YTYvOUE4neR5apB56Wg2Q4WmaeKIS21JtvS4bMlG0aXMAxCYNSjAEAmSaNs2XjpEYY4zieYL3GOE5TuxDIUVRNGCAotbclaIqYXh1z%2Bg6vxHLc2CqKwtLat8joyT6UkErcACymZMFQXgMHUAjemcQaEXSYaMqRtaXMQwD0SCzFhMAun6YZxk9LCnHppmHhwbm8IaKQtxcKFZgDpcd7TrO/EOSJ0ZiQ26mEgAKh8dFmUC64liiL5KM0EB6Y0nkmQwDJcMhICoZgyy4cmjRSvlCiFQQEBgGA7mlUZ5UMgAtFViYoZqdVmhwqy0JwACsvB%2BBwWikKgnBuNY1jiusmwnuCPCkAQmgTasADWIDTZIkYaAkZhmAAnDdXDTZdCRcMKwrSFNHCSLwLASBoIXzYty0cLwCggCF%2B0LRNpBwLAMCICA6wEIWBDkJQaA0nQcQRKw2yqAkABs/X45ItzAMg0pSJGZi8Jg%2BBEPqt7hfwggiGI7BSDIgiKCo6iQ6QujhQA7hiyScDwk0zXNB1LZwADyzLI7c763HjhPE6T5NhedZi3BAHgY/QyrmGCXDLLwENaKsEBIOjySY2QFAQLb9sgMAUiBDQtBUsQoMQNE0vRGETSImLvCB8wxCIrL0TaLUEO7ej7oELLDC0CHfNYNEXjAIytC0KD3C8FgLCGMA4gZ3gVF1GqHzSwqtTMtsu1hFSH2LbQeDRBikceFg0vongP2F6QNfEHuSiPCXRgd0YB2rFQBiOUS7yC7LzzzbtzPCKI4gc1v3NqNLAv6KXKBrZY%2Bid6DkCrKgyQ9AX/UzOgcL3KYljWGYgOjwztc3503RMguAYO4TwbQ9AhHmGUCoegCgZAEJMPw4U4E9EGNAkY4UajlT6BMMBuRMFdDjvUWYaDhjxEwbMRBegJTNFIYschqwFCbS2BICWHBZqkABrwIGKsCZExJmTCm2tda4EICQWEO0zZ7TnqsBAmAmBYHiBAY6/gwSRhumCN6GgAiSHxn9aa%2BMbr6E4F9UgP0TaRnxlwfGCQbrPXxmdB6Gj8acOlkDEGYNpGQytnDa2CMFbMlRk7VABssY404E0FgaphT9SYDKAwrEuA3UjFwC6NM6YkDwIzTm282YSGkPvJQh8%2Ba6ECMLJgotC5sI4VwmWHB5ZI2ZErKgvC1YkyhKXMKyTUkaF1vrO2hsJFgjMFIi2UM/HO0NkEyZIwOlGCSVwEKntva%2B39nzcOwdQ6kA2ZHaOscHBbMTrRFOadpaZ2zrnfOWzi6l3LotfAVdHA1wLoteuyBG5bJbl0aWHcu7B17tsRaA8h67VHuPTAk9bmuTnnwReChl6YFXuvLZW9Wa7wKbIA%2BvNFqlJPrPd%2BVgL6/Ovsopa99MiP2fq/Aln9v5xF/iSxhhDyrANATkJBQQQF0JgcgtI8Csh4I5SgzI3KMEAKIQIHBWZ2XUOZT0KVoryFjH6FQih/RFWsLWBsFhptjHsKlnzHhqt%2BHxM6UklJF0REZKNpI82MjSByIUSMUlH1THmOSdo4U00bqvTBDo4m4VanuNsJ4sZPj4B%2BMRsjaZISBlhLYBE4gLB1YsAUGqaUapzVWRmOksRDM9Cop3uzDFXMinYp0CAMEpBymVPFnqmpbi5YBLTMrVQKa00ZqzaGGYfTY32yGWCUZMKJl9qmY7GZ8R03JGSCiTNN0UTZoICiNtBS6ArMoGsxaOz067W3XsuOhyQlJxOene5mAs45zEFc4eNzp6AqLpXIhzy66qAblST5ghvl81%2Bd3REAL%2B76hBbwMFaQIXUihbPbxsKZzwpXmvRgKLZBouLTkrFR9K14uMOfGwxL4C33JVuTgOxn5nw/pYL%2B3Cf5ZL/qSrBPRWWqs5egDVvLCiZEY8K4oUCyGysAZKyhgreMSt6CQ7j9DqECZlWq2hYmeWMOYezapBrAacBVu29Nh4u1Uh7RAUR9Mhmmztd42R8jFGUDYW6kAt1IxgjBNNR6khFkaFs8KGxrjDWcA8eDe1J1JDTXUS9YUf0EiSHulwK6ZgXEfTBMp7hnmvGWzYdTdzKngYJcOiPOI6RnCSCAA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/set_contains/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/set_contains.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/set_contains.test.hpp)
