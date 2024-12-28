<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pay`

<p style='text-align: right;'><a href="../utilities.md#pay">To Index</a></p>

## Description

`Pay` accepts a `Page` operation and returns the operation via member `Page`.

<pre><code>   Oper
-> struct { using Page = Oper; }</code></pre>

## Type Signature

```Haskell
Pay
 :: template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct Pay
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

This function injectively maps a sequence to a type.
In the following example, We will create an overload set of `fun` using sequences `Seq_0` and `Seq_1`.

```C++
/**** Operations ****/
template<auto...>
struct Seq_0 {};

template<auto...>
struct Seq_1 {};

/**** fun ****/
constexpr bool fun(Pay<Seq_0>) { return false; }

constexpr bool fun(Pay<Seq_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Pay<Seq_0>{}));
static_assert(fun(Pay<Seq_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Pay<Seq_0>) -> std::false_type;

constexpr auto gun(Pay<Seq_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Pay<Seq_0>>()))::value);
static_assert(decltype(gun(std::declval<Pay<Seq_1>>()))::value);
```

## Implementation

```C++
template<template<auto...> class Sequence>
struct Pay
{
    template<auto...Variables>
    using Page = Sequence<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwArKSuADJ4DJgAcj4ARpjEIJLBAA6oCoRODB7evgGp6ZkC4ZExLPGJybaY9o4CQgRMxAQ5Pn5B1bVZDU0EJdFxCUnBCo3NrXkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLCn0bIJMdQxX%2Byfnl0c/R59npzOBEw9wMwJMAGY3MDQS9MJC3EwvEQAHRoyHYK7IAwKBRXISYACOXkY6wxgNGxC8DiuyiYAE9ASYAOxWc5XDlXGEPOEIpGotEANSaeCYsXoCnJ7M5XgyRlpTGAmCukIAIviiSSGGSocLiKLxZgFGiUeSIWyAczVZCLYDvr8Hdt/vargAxPDEUZXbCqVgPZUfO2O4P/IPXADyKQSLyyeMD525YPhUP5qBNUrOlOpBA1hIA%2BhoVayWdbzUyEyCeeCU8i0%2BiIdgKQQqTSCfmuEWrFabeWLvsrlQvG942c0AxRphVCliFdYqhPAOhxA6YyoW2CxiFp2rsRMARVm8qGIlDai9bzoCxxOpzO5wvBwxlwyEeuuJvt7v98Q3s2SaeS72LoACpGgQcbHE2MbIHmTC4gkBAQAwqA5g%2BT6rm464aOSxZWgsCw9uc0yONBsFKM01BLiuL5Enmb4NiyXaqnhBEAl8wYhmGuwamO6Der6oIBhBbHsQ6oYXmYEIRNiXhYCqUIEPSUZ5s2TCEJK9EXsJXHAEO7xCaOAjXtOVyplcOmPlRa40VhDZbgAtBiVyjOgIAgEetBKMpinJra5xXsCN4mbWZmUc%2BVntu%2BDkNk5BAuSAv6YF5UYsZx2xXCBozgbs/xEXgJFweRSE5lg2IKVG0BLs5rklbQABuYgIpZGHWWa2AQHhCyufV3iYPhZaEY0xEwQVCE1WVmAVY%2BVUgDV3WNWFzURfRDbtXhXViCSfUWBwSy0JwgS8H4HBaKQqCcG41jWE5KxrMq5gQjwpAEJoO1LAA1iAgSSCiGgABxmGYACcgNcIEf2/VwzLMtIe0cJIvAsBIGgaKQR0nWdHC8AoIAo89x07aQcCwDAiAgCsBApMi5CUGg9x0AkUSsBsqi/f4dn%2BJIZnIMgVxSCiZi8Jg%2BBEPqLlcDIggiGI7BSBL8hKGoL2kLo4sAO7EEwKScDwu37YdSsY%2BGyKUzmqBUFcLNsxzXM83zZhXBAHh0/QM73VwCy8HjWhLBASC0yk9NkBQED%2B4HIDAFIZh8HQwKepQsRK7EERNPS2u8EnzDEPS4axNomAOGnpC008BDhgwtCp/jpBYLEXjAIitAeYXWAsIYwDiFX%2BC7g4eC1UaSuTvnyIbI9ETArDJ20HgsQa1nHhYErzZ4Ij3C8H3xBzkoqogm3U9GC9SxUAYwAKIKeCYKrkaMIX/CS6I4iy7f8sqOoVcq/obcoJdlj6NP2OQEsVAKRXjYw4HZZyapTCWGsGYdG69Rb9wAZ0fOrwXAMHcJ4NoegwgRAGOUIY4s0gZFeBMPwhDCivFmIMRI4s7AoO6GMFomC8i0JqPQ%2BojCqH4JobYRhpC9DTGaFw%2BY7tlirHWBIXWHADqowNpwC2rN2ac2ANzXm317YQFwIQEgKoJLu09gfJYCBMBMCwIkdqpAPqSAhCiQGEJoYaEkGYSQ/hkaBH8IDfQnB4akERg9FE/guD%2BF%2BoDCGQRJCgzsf4WRVcMZYxxk9A%2BhMSa%2BzJsbKmwdQ4u0ZmwTgTQWC1WZHZJgWIDDyi4IDFEXAfqC2FiQPAYs5ZSwftIJ%2BigX5K10FHdWms05SJkWjXght0mm3NpbJRpS2680qdUwsjtUDOwSLoiEZgPaJPxj7P2CyA4u2piHbZYdsRtwqVwFGNBaCx2xhABOVcM4p0LncrOOc84F1XkXBZJcy4VyVjXOuDcm5vJbrvDYJ0u70L7qAk6g9kDD0LmPGoSsp4zxTvPEFnt9Qr0euvTemBt6tyMHvUAGy%2BDH1PufS%2BUYjqPSfs0mWrTZDtMVm/EAUcynGG/jYJF/8LFAJAZwcBsVIEctgUM%2BBDTEEWLoT3ZwEBXD8PFjg0o1C9BEKKNkZhZDSCqsobguYBDkHSoYD0cYGqBFsMNcavourlW0L4aa21MxrXcMkWI26LrYYDLkRwBRVtOZHPKTMn6DstEi2Wfo9Z3sjEmLMZQKRPi/GVMccyQIgMoYQicS4iJMT0acHibjJJRNSbkxNnsrJDMmZ5OICwa2LAFC1R5rVCpKIkyjFqdo0WegaX3zpXLRlr8Tq6AhKQHpWtV79P1rEzgRsKbIiuGbC2Na60NqbS2nM8zFmuwkhCNZXsCapLLUHGmByXYgHrSkFIeZG2AzzKuvMqgObRwuQkK5NyTqPMro9d9zyUGF2LowUu5dK6gswLXeuYgAWPSBQStF1cPTgv7lXaFsK3nwonrwJFs96SosXhiwu2L0i4p3gSiIRLvYksVGSi%2BV8qW8C7dLCQ9LBB9s6SAIdbKv7QJ/ly%2BAgDgGxk4JsKqUCrCWBFadMVWBuVLClag2V6D5UhHQcI/V2qsgKdU8UJ1IiDWvEtQpmTDDHVKudQ6k1uRNWCKtcZkR0mboSNER6idObvX3s5rW%2BtVwr3NrhF6TRdTN0PR3YY0gxjTFDAsbDeNLLKkQghIEMGETkaxeZME7NQzc22ASbuvCljhi2MhsyZGv1JAgy4P9Mw0TYYQic%2BlzGEbXpeI4ALNLp0MvZaWOvDIzhJBAA%3D%3D)$Done$

## Links

- [Example](../../code/facilities/utilities/pay/implementation.hpp)
- [Source code](../../../conceptrodon/pay.hpp)
