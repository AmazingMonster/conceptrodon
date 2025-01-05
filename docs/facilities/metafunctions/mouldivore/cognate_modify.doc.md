<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateModify`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-modify">To Index</a></p>

## Description

`Mouldivore::CognateModify` accepts an operation.
Its first layer accepts a transformation.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function transforms its arguments at positions indicated by the index list using the transformation. Then, The function instantiates the operation with the modified argument list.

<pre><code>   Oper
-> Transf
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Oper
   <
                    Arg<sub>0</sub>,
                    Arg<sub>1</sub>,
                     &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>0</sub></sub>&gt;, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>1</sub></sub>&gt;, Arg<sub>I<sub>1</sub>+1</sub>,
                     &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>n</sub></sub>&gt;, Arg<sub>I<sub>n</sub>+1</sub>,
                     &vellip;
                    Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateRemove
 :: template<typename...> class...
 -> template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateRemove
{
    template<template<typename...> class>
    alias Road
    {
        template<auto...>
        alias Page
        {
            template<typename...>
            alias Mold = RESULT;
        };
    };
};
```

## Examples

We will apply `UnaryMinus` to elements of indices `1, 3, 5` from `Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>` and invoke `Operation` with the result.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** UnaryMinus ****/
template<typename Val>
struct UnaryMinusHelper
{
    using type = Vay<-Val::value>;
};

template<typename...Args>
using UnaryMinus = UnaryMinusHelper<Args...>::type;

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateModify<Operation>
::Road<UnaryMinus>
::Page<1, 3, 5>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateModify` by combining `Pagelivore::CognateSegment` and `Omennivore::ModifyTypes`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many elements we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>
-> Capsule
   <
       std::index_sequence&lt;0, 1, ..., I<sub>0</sub>&gt;,
       std::index_sequence&lt;0, 1, ..., I<sub>1</sub>-I<sub>0</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>i</sub>-I<sub>i-1</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;
   ></code></pre>

`Capsule` is a vessel holding the results. It can be declared as follows:

```C++
template<typename...>
struct Capsule;
```

Finally, we will transfer the `std::index_sequence`s and relevant arguments to `Pagelivore::CognateSegment`.

We will use `Send` to connect operations.

```C++
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct CognateModify
{
    template<template<typename...> class Hormone>
    struct ProtoRoad
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

        template<size_t...I>
        struct ProtoPage
        {
            template<typename...Elements>
            using Mold = Send
            <
                typename Send
                <
                    typename Pagelivore::CognateSegment<Detail_t>
                    ::template Page<I...>
                >::template Road<Omennivore::ModifyTypes>
                ::template Road<Hormone>
                ::template Mold<Elements...>
            >
            ::template Road<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIGSAJykAA6oCoRODB7evgHBmdmOAuGRMSzxiclpdpgOuUIETMQE%2BT5%2BQbaY9mUMLW0EFdFxCUmptq3tnYU9CjMjEWPVE3UAlLaoXsTI7BwA9ABUp2fnF5fHhyYaAIInZwDUACKY6a6MyHiYCk/nN3ujyuIIugLutwhZkCEWQ3iwTxMgTcXkctEIAE8kdhIeYYQw4V4EUi3MhFugsFRsbigecnspiJgaKp/mdwQRMCx0gYOSSCBiPsw2KQnkxUahqfc0AT3gR6YzmYjAi8ngRiF5MEirPdIcDjk83Ex0govPRWad2ZzuUxecj%2BYLWJgAHQuyV3RbqhwGo0m%2BhamkPOnYVQchjoABixFk5uukI5XJ5mrtAsYjrdHq8XuDoYjUcEiIA7FYCy9/Tr7vHrba3JXE3yU0Lna7AtgnnCmAo/h5BEwVmRVQ3HS6ndh6GxBAp02rM3Ls65I7ISd3Wn2SaPOYwCAph9SW7ii5CnkfVVa68mHWxhxZMMAIgwIsBJ3v7senl5skYngBZTzoJUq5de0iYgSWvW8GHvIxtxdEV13HLcdz3QJtQhEsywhCtTxtJMayw6sxSIRDW3bTsniETAAEcNRlEUCNQYcADU2jwJhYnoJ8cXuDMsxDec8wIElyKor4cKY4gWLY34iLdEwDxfY9a2wkk6KvG87wfDjD2Pd8H3pJhgEwf8yMo6j9lAtSII04cRTEiT2Ok5D91LRzy0DZ4AHlx3vAA3Eh2BANwDE7PBkB/fAqAxAAVFM/gBSFGwUdImH2J5PMYHy/MLFC4zwnD7VTS9m0491py9MK8Ai6KPj%2BWTi2c7LaWeCwO0Mw0lBjS0EyU5EVJdABJKdPTlcrKpiklyRAEAIiwVQAH0lGEmUST6hzitqrSj0U6strywdCqdbE2yCv53I%2BYgbVyN1X24uUGVQIgACVUCYdANqyt7Xx2j7jxJb7X02vbDMitoDIIUg/v%2B/LGyvZKAGs7mIR8Iau/6j0WC7kDbARFkwbyxFFcUnjwdAMVoCGIAh19DkOJ5gySsNEQANg0BkmTwVRluxHdmdVVAsa8fMQZ8Tc/nifhGVVBBDJmUGDvk1HX1Z5lOZbAnCJdKh%2BNmkGFHB%2BWFaPamnki86GAUcWWElwzIhDUVEeFwQ5buA3X2BxHMDBynjyN/J%2Bitp5GUWJ2XePZrkHhxHoODhWNghgBaQ7DWNU1NX119frThWocdJ4sDhfLqC1nWNkm/LrK9o9ToSC6BHrC8gZBj3S5TbE9edkOB3rp4w4jx9m4%2BHdM6PXcGvb1GvvPAqmydO5gEZDcJxR1GdM/H9aD/JEVTz2gC%2BJ0mIAmkB8tm4nN0xElZ/n%2BDNIPEthw2WOXLHwt6oDT7cr5D/J%2Bhoqjo7KPL6YAXluJeb4PzACeE9F6Rk7qPWeq9ZEgDgFRxHk5dCOUur4XFMOPqtFsEugAFKDRnN%2BDAFUopjWRIfaamA5oLVMjhFaRURTULDLQ%2BaJkRIkgIatfcKF36YLyl/GsgMiJ/1IlXc6AxQE3XlPdVAUDXr63WkPE8gjkbIgrp3KeTxwx4GIIsN2oM24d20Y2Yy0p0BGI9iYju2d9o9wRkjVRoDrqtEcJjaUOM8a0DVnzPeZNVEU1UVTGmdNDAb2ZkrdmKtsDcw0Lzfmgt7bXyeGLTKBApZPBoAYuUMsPbRxDtEjmyIBqq16k6TWshtaR1sSHI2JtDDmxIJbTJ1taFyiFvBQpLs9G5OsZ7EJ3swmqHppElmCoYnIiIS2eJiTgB82SlGUibTc54HRjKNJHsADuQCGCqm2XzfJCEtHFO4YdCpLBiboHoDUx8dSXYNNNs04grSsk206SkzcPSDbkUsQMh5BsfaeD9qswOBAfkK0cZHQez9Xyx1UQnVWSdfSpzhT9TRQyAZd23gXKpgg7kKBLkfFM5csWpTOjXBgdcdF9MMY3Ag/ckzYEBVnQGudGg7xTBAK5FJbnFyZWS9FqNJFUppeYv5AgrEMqZa3LR9jDLQr7iSgeroXFIVHgbCeIj67DiQdfVx2lwGkPXkZXF3KAkHwIOgJlJ8sCCHPogueQCDV7lvi8e%2Bj9%2BE/TQk/N62qA2iN/iRABzrkGgJXhAxRMCoxwJehfMN18HLZV9aPPUkDGi7GyN5VqLUOoYKrDhCpuC/HDgISKBVw53JtOIEJBhmkuKlWGmQ0a1VxrWsmjQuhnClqlKIiwjtU02HdsWmZaZ/bUo1rrSJFBz5ULes2sIwNurg3HQpdXaRc63FDTkXGpRz8VHCrUYWjRbh5XsrpQQAF56u6SrDNe8llaXRKsnOq4qBt0YeKxmbDkPi/FExJoEo9wSj2hNpqMiJTMJlsxKW4MpcTXQ8yIEkz5wAHZbi2eLaWWScmLFVAyyFqMzmlIufgypRdalaKeU0i2/sPl2zQ90rRl6H2geGeBsZUHiNuBmQhg6SG%2BYLNFMgZZfxVn4A2SleIBBdmMAOUchl25TmTNg7x0tLpeU3MwIS1lqNqNm1o6s%2BjXTvlaLvdK92gy2OGxpr7RoeSsngsI/9F9sKDYIqPUi1sc4wwLkEKerR5qPhaJA6Y18I0KFtuRNWqWtae37Fne%2BsLR5S65UgfAkkorN1JeS52wDEAX3rTvi6DzpjSsK0NSlo%2BaW177oNhnazZic5BcwIXapAqVXT10/9LLl1v45xYzKzrcrH3spazy65/LI7ErLjBLRvXa79bYBYqVAzZVboqxqt%2BWcl1BpnomkWlWwG6Vq2azlu98uH2PqfB1/IE1X0O26uqnr0Lp1Tdtxd6i7S7ZXQdVWIa9UHcXhto8kb0vQM3ruhRGWnUPYnMmtBfqdRoVcumoQCBUQEDNHFTCX3DRkeIV6dHmO/RI7cqcJ4YkMSxDwL5Rkk0qohTEMoVA6R833ASklFKVOad08MoegtZ58fqz%2B8VWRjPRC0BZ2zorr9XLaroro/RixCdygl8z1nJJL0yTks/MH%2BUjLE4IFjnCqDkdy4wncBXhNL14OQ%2BZ1XxsBRM6l5r5EtuVthh1wu47n4DeQ6NybrXyuBJbfN%2Bg3HJ6eo25D3bvm5m49VprQ2kqO71eu/SMH3JIoE%2BTti4lvhb19ct2UcqcDOY/Oh51To9P0vMvJ6IutnLTxUuCL0gZLPiwc%2BNClWb1CFu0Go7pORBmOOrc/antJRtO6R8b3dRH8fePrci8OiG4yo7MCJ5dLZVi7FHez8EvF0SzFd9SSKt7/1S7hEVNX2uhb1KQdPFkW8FcQG3s%2B9fMXj4Rl78kh35JAvJ%2BN7AffWANa/Anf7Y6QHOHEBR/MHB6XsXxSHF/RA%2B7F1EWRvYbP1d7eXK/JfPbW/f%2BA0WQICBICtPbOCR7MXJtYyL3ZEQCVcZESg%2BHc/OdQ9ARKPXCfA37QgiRSlbLN6Z/D2VA5RXXA2L/fnMvX/JgscDA1gn3WSEA5%2BMA7gyfVdf%2BaA9A4HZveA%2BBIyFAugNA5BTA/KdBHAy3dNZQfSPoWnPySaDwYAZgDkciYAeCdnO4TnZKQyKwgydEPnd6XApfcAlfSAog6Q6gndBwpwzAFw%2BCQvUA4RbIAAL20zlBLWSNSLLRkRoIMLfx9Q/wUkSLwBSNmghRdAAGkjtGQqJ9FfgngIAdwzBGZzBGYIByilQ3AngCEH4IYwcAAJa5RgUon/fgvrODEUAhOOcohHUQpQjgoXCpfVKgovY1HwyQlUA/JbQyHnWw%2BnEAWvN3NwJYlg0XJvN6VvQtSBVA5EXIowpNIqC4xMJ4AYikIY0PHEMnI2PqMMEKOo0QfZMQBQPmeIJ4JKTsTAP8MHEwZmVhGaDhDfaEjQHpZdKebIndF4%2B1d6cwy/PHDI4Y9I4ozIwhNEkhDExgdtG1IdOE%2BhLhUpCY3hUQgoz7TgvEsop0Sox/V8aorwWov4Bo10Jolotojorono1RMHXI4YyHaQ8YroqYmYy3cQ41f3MvTY6vcxHYvnBnZ3SXOvOkrokwluTk48R47CK4wwm44QugUovvYAhfeY7qdUocF0Y42AnQ41U7SHMkh/I4oHBCB4rAlNJQxQgMPUUEcM2MRqCnPqBMYBKldwsMiMkEcEQXR0lEn%2BUXcRE6UYxbCIkhKI7CCLeI5QvAzgp9TMtfPolpAQZlQQmg2BaHeNRkiGbVVkp4Akkotk3jXo41SUuUSHFFFOCkyaFgJgWGbTLteEhhWJAdSk0c8ck%2BYdKc2knjOOLgLmeQj7SGIozsnBI7WRBstY5GMQuxCfDM5gt0rRMHT01U1wLRBrZLbFHRA/cldOTFRrLVdlNYvwuwgKVARw7CWIzcEkPso7UxU0jkdvRhKfD8jFbACCwyRRTLLyXY/yCLKqX4MChWBC8HBBNwKs15GsrC1GHC2rNcWQk44ipUZvA2HCpC6LHMh/D4pkl%2Be0nbPHRYv0lPJU3SNYmNeRI82HLQ/00XV7H1OYwooI1QjM3g0NGA7io1XSaNSHBs%2Bi30%2BShUkMz4pMsEXUIMVQVgbkQyMfRMiMlMnUaEWEeESQ0kAQfYdIS8ofZ4JiDEdw5fPmeDSEWRFyvhJ/dxEKb9HGUZYgf9HxDULKAaVNVi7S54OQZgYgDEL8CId8Nys8nOJiMmOdWROKtoRK5KhQPovoM6Ysz/ZUlMIyHy5EOODKyaMK2s7ApQ9M50meSON0MHHKhKpKhgFKyHDqvK7qgqoqhIC%2BGFAM0wmKine/VK6S5qx3aQtNOkL8YQqgAWJoAQaassvbJxFPa85a1agYIyAsjkIshijdPrYqSaNSvqrq98N0SaQStwLgEUYIJ4fwO6kAMixBUa0Sia/UIQLwdIEoCEh6X4U0OUMfMHf6wGrIYG0GneEYs6xbNwSqtwDQVuSnJgLEKq9clsGyTGkkMwdGlGuOQIIm/G5ESQMmrGtwOON6pCZi0MukEG30cGtkSEeAuG/ssvJa1oFagkTdZG8m1GqmkkHGllDG6mwm3GiWkkUm6WlGym%2BWoWumj4hmpyinSKX4Vmi0Ly/y5AbWcE9oK1SkhQR0A2kkZmsGnPAGoG9AS2nebEL1DgLYWgTgfwXgPwDgLQUgVATgM9SwawJ/HYPYfnaEHgUgRlL252rYWGAISQJ0DQAADjMDMBSBSC4H8CTsTq4ALALGkFdo4EkF4BYAkA0A0FIE9u9t9o4F4AUBAHLsjq0C2DgFgBgEQBAB2AIHSFRHIEoDQC5DoASCiEdE4FUETsZjjkZkkCeGAGQExikCdDMF4AhMIBIGJj0H4EEBEDEHYCkBkEEEUBUHUCjtIF0Ceu2XOnSE4B4Bdrdo9s0F4GrvclRG7rlFQCoCeDHonqnpnrnqeAXrMHqI8AHvoBCrxC4A2F4EbudtIAgCQH7vSEHrIAoAgAQaQZAGACkDMD4DoA5AMUoFiAftIBp3ioxGvt4BIdyvcliG0Hs3IdIH7vgncgYFoDIZPqwFiC8GAENFoFoDru4F4CwFHKMHEHYdqKaBzX4e9toUzQ5HoYiA5ALu9vRFiHOgSo8CwCIbVDwBLoEdIBzWIFiBhreGEeAHRCMAfq2CoAMEfAYh%2BG2Srk9vDs3uEEl13ukBccPrUCIbPv0EMGMGsGsH0DwFiDrsgC2FZwGH4bjnJE3lMADssDMCroMfEiwDCYgC2AaDWr8AgFcDmD8CerCBWCqBqD0BKByAEHybKayAqYYFGBKYmCeqyYGCGFmE8C6D0GaeaCWHqfGESCaaWCqYGeGF6bWH6cyeDv2AkFvo4HdorqIers/vHsnuntnvnvjsAYgFwFXrAbDsgYjssa2ClhegmAydIFjskECCdBSECDzo0EkDMEkGZg0H8EZjSALqLtIBLsCC4CdEZi4EZkTpSGzsZn8EkAzpucZnmZPurtrvroOajubrbrgY7pfp7pQbQdAeHrYE4DaBYG8gLDjiYD/k/C4BSCdF%2BekfwCIFSY3tkG3vED3s8aUG8ZPt0GwYvqNHIZmbmcrsfs4Gfq7tRCeHfqWe/unvbFJfJcpaAdQBAYSERGhDMH2egebvgblcQdAd7tQY1fQclcwfTvLpoB3gSDrogEIZPsoYSvoatYxGodoYcHocYc3GYdYaIY4a4Z4b4foaEf8dEe9vwEZAkd%2BCIZkeQFRAOHDoUb6CIZUbUYxA0YOG9u0d0fDoMaMaUBMb9YfEsb4BsYUDscwAccFHoZcYZfcf3vkBZePu9vZb8YsfiasEsGCdCfgAiYctyGidieVEbesCScfpSdPnScyb6Hs1yBcDDCGZCDDFGdKaevKYGCnYXdyFncad6H6G6eGCna6YEFaeWEqD6c6cGfacKGGfaFXfGe2F2CmYgf0Dvuhars4DFZWZJYgTJYpYTvqO2ZpcVZ%2BZVcOdIGOawESDOY%2BeLqSHJfuYLH8BSFzuSEeanqer5Z9s4DhYbtzZbvbs7tfu1cxaHpHo4DxZ/pYAUG8kxm8nfcTEWGXupbXptSerLbcYkA8dkC8ZrZ0CSFIE5avoEZ5fvphYFbRbfo/tUGI9I/I8o%2BwjwwgGAc1YVbxECH/cRdgfVfleQb7t1dAZADI8Btmgo5SFmio4IFmlE48dwdNYIaIdtZtYiCoZobob0edcEFdbYYDcwE4e4bEG9b0d9ZEaTcEfEccEkdDdUFkcjd4GjaUd4DjdysTa0fElTd4HTeMc5GzYseU%2Bsf0gLfsccdLfpaY6ZdY%2BrZ8c44MAbcCebZUeHZ9o7exk4EOAml7cSeSYSFSZDfCfXbHecFycnZPYKenfQAveqdKFyCXZqYGCG6adHeyb3e3em5aZ6eKcPbPY6D66PZGaW7GemavZDu24Lt5YWafdM6eBI7I6eH06dCM6/do92b/agYA6A9OZmc%2BZLtTqdECECH8EzvBbLo%2B4LEBYff5ZrtsHhdVZjpAEkH8GuZzoLDLsTtSC4C4GTqaLvY4ECH48feB7B9R6XsB5Q6x4A4MeyGcEkCAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_modify/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/cognate_modify.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_modify.test.hpp)
