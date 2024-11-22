<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::IndependentCognateLeftInterview`

## Description

`Pagelivore::IndependentCognateLeftInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> LeftSides...
-> Arguments...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
IndependentCognateLeftInterview ::   template<auto...> class...
                                  -> auto...
                                  -> auto...
                                  -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct IndependentCognateLeftInterview
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Page_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

template<auto...Args>
using Metafunction = IndependentCognateLeftInterview<Equal>
::Page<Args...>;

static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

We will implement `IndependentCognateLeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct IndependentCognateLeftInterview
{
    template<auto...LeftSides>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...>
            struct ProtoPage
            { static constexpr auto value {-1}; };

            template<auto First>
            struct ProtoPage<First>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else
                        { return -1; }
                    }()
                };
            };

            template<auto First, auto Second, auto...Others>
            struct ProtoPage<First, Second, Others...>
            {   
                static constexpr auto value 
                {
                    []() -> std::make_signed_t<size_t>
                    {
                        if constexpr 
                        ((...&&Predicates<LeftSides..., First>::value))
                        { return 0; }

                        else if constexpr 
                        ((...&&Predicates<LeftSides..., Second>::value))
                        { return 1; }

                        else if constexpr
                        (
                            ProtoPage<Others...>
                            ::value != -1
                        )
                        { 
                            return 2 + ProtoPage<Others...>
                            ::value; 
                        }

                        else
                        { return -1; }
                    }()
                };
            };
        };
        
        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCAArNIADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn4B1bWZDU0EJZExcYnSCo3Nrbkdo739ZRXDAJS2qF7EyOwc5gDMYcjeWADUJltuBACeyZgA%2BgTETIQKx9gmGgCC27v7mEcnyKPoWCoTxe7zeBEwLGSBnBx1OEKhTBhJyYXiIADoMU8DnsmAoFBi0cpiJh8KJwY8ts83qNiF4HAcAJIMLCXZmMFqoYDMcHBTBUAhM8HEABueEwAHcQSYAOxWN4HBUHcGQ6GYWEo9EY3n8oR4LAUqmvRUHGl0ggHImoIjKJjANXyxUyuVG42K030oQGBQIEGux2y31%2B13KhFItwa1AE4EOoNu25mi3EK2oG12wOxhVOk2NRzIbECUaYVTJYgHCMHYViLzfJ0AWi4MoAIscLEdpc2ts70xmQ6r1ajUAcAGJ4YijaMujPZ2n0y3W21qk4jscECdTzOyx0x9cK6a5/MMQvF0vlyveGvbndO7s740mBJWBKNiALA61rH/EAgFhMADW13SLkSRuWF0gAL2uVdKRvW8N2dWCpzwKgDyPEsjkvBDjSgKMzAANnMXCiRJPAyUwCk3G1YQ9TIglSGHUdx0pL8z2rBYFhgzC4IOYkCFWBgDg0Fs22bN4OM4molDEzCsx4vi3wbTthKk9cmxfZS/SbFt1KUzspQwv1e0RRdwwHeiVzo8shEwNBmQsgcCQAeQIBA4gNbT3XNOcUwXWFl1GOirJs9A6KclyxyjaD9NdLNMyi2M9xIlDwWPMtTJYi9J1va84pUh972fV930pbN0C/H9/yuQDwnQECTnAyC104uDtJ3JCkqLNCWvXbDMTwgiiNJIzyMo3V9VoszGOwZiq0wNiuqnGTMF44h%2BMExTNNEnLYIk742ps1DS3mjMerRAj%2BuJQbyVhEbqPxDEAusgR0Ceabzzmrass3WSVoOBTWw20FMqahUdoOPaC2SksjtjCBofXLzU2M0LXIiw1gYzV7qwOMAwGORt5Lhv12I%2Bq9N0JjNvv4swjksRNk0R2FkfCzFIqB9HFUxxd/pJlT2z0tmmp28m7y%2Bpa5PrISAfR1TiYFjNNN0j6FfgoNlbEsTDLDCMCVeYBiQhdk3Kirx0iMC0Fx%2BfHPVxJAQE174EZ8k5df1thBDu07oMVzK1c2zL7f7TU0RdzADfdxqFRNsJgHNu1Lbp%2Bc02dvXQ7dggPeBb3fcBgB6AAqAvC6L4uc5BfPC4OAAVMj04OIvS7ecvi%2BbguG8Bj4GD2LxDlhGz1mSdOJxBAPkVMhk7KIA4ACkJw8g5sAARy8MQpQDbcErzfbIdLaJUE8CsZu7J0GUtvHp%2Bzi%2BwXhPtR6D15iGAI3Xijs2AFklqYKgvE7up46ZFlXDsg8FyIylFBRxFFBKWEi9l60AnF%2BBmzsH4Zy9l2akOYSJXFxEoZoIIIDv0aF/H%2BmRYRmBeiARBbhAi/TomYWh5D0qny2PjMw7FvYbywXiOIq43j4I/kQhwJCTgSyYhQp2VC6JcFofQ0RjC8Zn3rGwiwHAli0E4AkXgfgOBaFIKgTgbhrDWBNCsNYNYzBbB4KQAgmgVFLF/MMNEGhJBcGlFsDQCQNB4VwmYAAHD4/QnBJC8BYBIDQgQtE6L0RwXgCgQCBGsdolRpA4CwBgIgEAKwCDJFROQSgaBIR0DiBEVgGxVA%2BNwrWXCkgDjAGQHmKQaIzC8GIkQYgeo9D8EECIMQ7ApAyEEIoFQ6hEmkF0FI8UdxkicB4Ko9RmibG6M4A5VE2TzSoGQmUipVSal1N%2BpIRpBwIAeAKfQQ65iuALF4AkrQSwIBIHyckQpZAKAQAeU8kAwApB0JoLQIUsSIDRAWdEMITQzjTN4MC5gxAzgOWiNoayCTLH5LTg5BgtAwUjKwNELwwBwy0FoLE7gvAsA/iMOITFo4EV4GFGRBZRZrKog2JYsI4I1EjNoHgaIdxoUeCwAs24eAQlEtIDS4gu8lCNghIYYAHKjA2KWFQAwj8ABqYpxQOVZOC/pwhRDiD6Z0%2BQSg1ALLGfoaVKBDGWH0Jy2JkAlioAHpkQltZ/h41MJYawZhImirafqeASw7BUucBAVwEw/BSJCGEAY5QhhSIKBkAQYa9DxrqLMQY8QpGBsEQIHo4xPBtD0Fmuoua%2BhRrmLG2wYwOQ5HDZWmYZb00SADSY9YTaAkcA0aQCJvAokHE2ZU6ptT6n7OphAXAhASA0wsZcqx8qlguSYFgeIL5SD2MkFsNEABOLY0oAiSDMJIXCYSEi4U3e2oJpAQkWLRLhLguEfGbp8XepIXAEjbtwl2hZUSYlxNnYk25aS7kZJWTkl5bzTnFLYJwJoLBhTSlrEwbEBgzZcE3WiLgjjmn4Fae0qRBrul6ukAawZxqRm6DoRMpgUyiWzI7fMkZUTllZNRAcdZZZiCwfg4hnEKG0MYY0Ic45jzTlTtYVc%2BVyT7moBOXEXJrzpPCaGDBuDtYeOfM3VwQIPy/mUEBSMyFoKtUGehbC%2BFDgtXIvZKi9FCysU4rxQSrVJLpXkp0fgYkgiaWEp0fS5AjKtUspqAsjlXLQW8o2DogVQrLGivFZgSVpKZXRwk4q20ChVUSg1YwLV%2BHdW9KI7IEjwydHkbNXK91VgrUhdtSuh1dRnWuuYRVz13q4i%2BtpXazoQa/AhuZEmiNzI00xozaQFNmR%2BujbSAmhgQ35iZpqN1ktE2i3dCrbNit0w801sLWthtw220KBbb02jnbu2LI4OxzjCGkPSt%2Bnxxxhzx2tKnRc8T/752YEXUMFdbKL1XrQ046Ub7pSuP3Ye5xn6GOcB/fEiTKT0mZNWXJ8DRSSnQY49slgChhR5mFKhtEqpRhYYnb6jpsgCP5e1UVk1IAtikEo9RmZ7bTtfqWSBtZyEYOY%2Bx7j/HhPzRHIU08qdWwZ3XKSUBlHzy8lC9OSAHHyRkhXDx5uq4/OsEY6I3QHTAKgUguhUZ/XMK4UIos9JlFaKMVucwNi3FYhHPCuc2SiLxLKWedpSM3z/nhWBbZTokL3Kzjhf5W06LvBYtpHi1KslyX/18CVeltVWWtGWNyz0iQBWBlGuKzoWnZXjCWpsNV/1ujHUFk4DnT8zXLBep7T626JeVvBtDfm3IA30DrZG2NxNrfa3d5m3tubXXs31CrcthbI%2BS2d5270Zbu3SiNoucsVYral9spZ1Di7XPqlY5xxWPnQ0BdPcndsV7f6bkfa%2B8u2jf2QBmDQ1sLYCQPHOLCY/6U97IeROh7YX94u2Krr%2BAJBboJA%2BJ4SbqSCbquI7pcB05spbD0bf7RLn62LtpNJf49o/7/5LCirpDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/independent_cognate_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/independent_cognate_left_interview.test.hpp)
