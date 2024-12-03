<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Deceive`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-1">To Index</a></p>

## Description

`Pagelivore::Deceive` accepts a class template predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns false and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> not Predicate&lt;Elements::value...&gt;::value</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept Deceive = REQUIREMENT;
```

## Examples

`Deceive` turns a class template predicate into a concept so that it can be used for subsumption.

The following code will fail since `not Pred_0<*>::value` and `(not Pred_0<*>::value) && (not Pred_1<*>::value)` are both atomic:

```C++
template<auto...>
struct Pred_0
{
    static constexpr bool value {false};
};

template<auto...>
struct Pred_1
{
    static constexpr bool value {false};
};

template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (not Pred_0<Args::value...>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (not Pred_0<Args::value...>::value) && (not Pred_1<Args::value...>::value)
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEIGYA7KQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7Jv5uTF5EAHRXx9gmGgCCE8ReDgDUysSY6AD6Gnf3JmSVger1BrzmjmQrzQDAmmFUaWIr1iqE8rwAbmIvJhXoCLFQxEpAQARY7AgHJUn%2Bcn/Xb7Q6YY6nc6oK4XG7/J4vAjvT4/Lj/PH/MHglqQ6ECOEIpEotGY7w4vEE2hEylkwVq6mCh50g5MI4nM5EV4ASQ5Dy5bwAsgJUEQGABPDXkkUQvBQmFSxGvI2oDFYxVAs2amkh7X3XUMpkEB1pRisTBs%2B7EYAKc3JzAARy8eE%2BCleEAYdt5X1%2BTOTqZAIHl2LZNyrNcwy3%2Bnt20uRqNoryoXgYEGbQM%2BBA2DG7hMZWrVD1pez1BrcMbjzDYSZTaf8twen2zucw%2BcLxY%2Bpb%2BJwrCgbAbrG4vCuWuLMADZzA%2BC0WeUf%2BeW1zfa9dr9WA2bB5W3hb1ZS7Hs%2BwHCwhxHV4CGeCcrCnAELTFd1viYBQlDaaheyZG03wEJ0TgFDcbn7ZtqQ4VZaE4QJeD8DgtFIVBODcaxrHBdZNkVMx/B4UgCE0GjVgAaxAQIHwuAAOB8pECZIH0kABOfwlP4/ROEkXgWAkDQNFIJiWLYjheHPQzhOYmjSDgWAYEQEB1gINJznISg0H2OgEiiBNOFUOSAFplNeYBkChKQLjMXgvkIEg8HQPR%2BEEEQxHYKQZEERQVHUazSF0LhSAAd2IJg0k4HhaPoxiRNYzgAHlzlcnlUCoV4AofYLJFC8LXkiswCw8Lz6CRcwBOWXgrK0VYICQTy0m8sgKAgebFpAYApDMPg6F2YhzwgWJatiCJWgdCreGO5hiAderYm0TAHHO0hPLYQR6oYWgzryrBYi8YBTloFUnqwFhDGAcRvt3Bw8HRPdavhB7zm2QSIl2Oi8toPBYlK66PCwWqELwPTuF4WHiBRJRiT2MHMaMETVioAxUwANTwTAivqpcnuS4RRHEDKeeytRaoK/QwZQTjLH0LHz0gVZUDSRpzw4QKJnQY5iVMSxrDMEyyeIBK4blnoHsaFwGHcTxOj0MIImGKpRkK4psgEaY/CdzIXYYBYRkSQq7FNvpJnaK2Cn9%2BpA4Efo2h9h2/dsYO3b0OYY7txZHdWBQeK2CQqo4BijNq0z2qCkKwoiyQooLXA4tG/iuAmoT6dWBBMCYLBEn7UgJMkfwLjU5JJA0SQzEkB8DKklStI4HTSD0gSLnkh8ZJUmSuAfQJJC4QI1IfQu8tM8yQEs%2BnbIc2anKatzltWkbfLYThWhYdFkkCphoQMIw%2BpUi4uAuFjYpEANolQqPNUr82kILJQws8q6C2iVMq5084F2MrwUyjUXLnFeK1H0xBn6v3fsgT%2BwBv6/3/oNVAw0Ej3n8GYRuU0bIX1vgkdyK1KELRGiAJ%2BL9ApELBlwFSXBDI0FoLtfah08qXVOk9KR11br3UeiTZ6lDXoEHep9WqP0/oAyBkokGNNtgsXwJ8aGsNlYANUIjXYT1Ub1FqpjbGp08aGMmgbYmgkyYU0wFTUGRhaagGsgzJmChWbs05owbmshwHpUgbIIWuUWJwLFnTLWVgpYONll3BWStOCqwIOrfwmtJYWF1mg/WhtMmZwjtDZwEBXBJ0KrbCovs9DO0aA09IntGixyWOHXoUdE6h3dibGpTRg49MdgnAYHSU6DDTi0huawNg50WejFBRdOC4PwW/D%2BYNSF/w0NXfAQCaEN0ms3Ugrd26jC7ujWe88f7D2SDvZIyR/AjzHlvfeJlOBHxPoEs%2B8AL7OWaqw5hxB77bCfiFFgCh0RQnRAIi4DIJgxWOfFEBmVeZpQkLErK0CEk6ACMVUq5USbIJqgfBqV8WptWhd1WF8KMRIpRTyCAQ0OHULGv4ehp8mHsMWmCgVnD4VpDSN8RFKlvisswng5S21REJHEUdE610ZGqpundU2T0XqMDUR9L6RjMC/X%2BmIXRgl9F%2BJcaQYxgczHw0scgJGNjBB2IxljHGDpnEEzcU9TxmRvHUz8REAJ00%2BDBNCRzLmSiwF8xiVi%2BJItiXEIltrdJMt4Dy0VjkZWAB6NWqa0klL1gkYBRsu4B1GebS2%2BRhlNPtr0zpJQcgdLaTkCZ8dK2NGjiHWtydqndvGfMuOydBl9v9kO5pI7FlZ2WelCl3y0GbPpa8RlCKWX6j3GymuJyxpnKboElubcO6UDzvcpIP9/BBECMPIRGgr1KRkouuqZlbDHwPdNcSIBe6/38DJTe/Eb0Pn4kpae/hKU/NfQw5YedorPsPh%2B0SpAyZZGcJIIAA)

By turning `(not Pred_0<*>::value)` and `(not Pred_1<*>::valu)e` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires Deceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Deceive<Pred_0, Args...> && Deceive<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept Deceive = not Predicate<Elements::value...>::value;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEAdIADqgKhE4MHt6%2BAcGp6Y4C4ZExLPGJ/tJ2mA6ZQgRMxATZPn5Btpj2RQwNTQQl0XEJSbaNza25HQrjAxFD5SNVAJS2qF7EyOwcBJgsyQa7Jv5uu/uHmMduTF5EAHQPx9gA1MgGCgrPysSY%2BKK7pGeBAAnslGKxMA87th6GxBAoniYNABBNAMLbJAjPAAitUweAAbphnsdsc8GKgsd9fnh/pcTjC9owCAoQCACWIvJDHv5sGyOd56VYUUjkQB6ABUUulMtlYtFkulzwAKpgZp8ZfKUYrZbqpVrkaKzgcmEcTjd7jzsKKZsQvA4vj90AB9DSikwAdmFyOevueM1NtNeAhmmFUyWIz1iqE8zwFXJJXqoYiUnuxx29aYz7pRxouVwtqChiJRtvtVKdzq47q9or9/sajmQwYYofDkejsfjxM9FmTtFTHvT/kzQ%2BzItzexNZuut1QzwAkiXkWWHQBZASUgTAmve%2BsBpsttsR56FuOcntepdjkc14eZyfnU3006g8FsKHI4jABG80U/ABHLw8B%2BT5cS2QkX2pF0NEBL8f2LP8UTRY8OxjWhnioLwGAgZZex%2BAgNgYTCUyFLMJ2RPNnyuEEwWYD8Hng39rRRQDgNAnE8Ugq5oNdODvwURCXnMAA2UTOIgokeMrLh%2BIQq1RRQ3Z2yjdDMOw3D8MwQjiGIgg7TIscKIPWlnSYD4EgIahsKuDcKSIBgdxOas/15XC8JHDhVloThAl4PwOC0UhUE4NxrGsf11k2HszH8HhSAITQvNWABrEBAkkO4NEkLgPX8DRAg0MwRJEswAA4yv0ThJF4FgJA0WCAqCkKOF4VlYMSwKvNIOBYBgRAQHWAhkluchKDQfY6ASKIIU4VQypEgBaETJGeYBkGbKQ7jMXgaSIYg8HQPR%2BEEEQxHYKQZEERQVHULrSF0WSAHdiCYZJOB4bzfP8pLgs4AB5W4RqxVAqGeealpWtaNueLazGeCAPEm%2BhI3MOLll4TqtFWCAkAm5IprICgIHxwmQGAKQzD4OhdmIVkIFiX7YgiJpgQ%2B3hmeYYhgX%2B2JtFqTr4omuECH%2BhhaDZ%2B6sFiLxgGuWgB3Z0gsBYQxgHEKWQIFyDWXusNalubZ4oiXYfPu2g8FiV7uY8LBfv0vA6u4XgiWIaMlFxVWjAtowktWKgDB/AA1PBMCe/66KVk7hFEcRLujm61F%2Bx79DVlBwssfRLdZSBVlQTFMl1xaZnQUlTEsawzGa12DqwHPcM6bpMhcBh3E8No9DCeYygqPQCgyARJj8WT%2B56QYe5GWSajqAQ%2Bgmdvcinrptdn2Zx%2BGRIp9mIe9ADZp18WTfVgUKKtgkL6OD80gmt4FrwYW5bVvWzbMvhiBcEIEgSVirgMYSv3VgIEwEwLAiQG5pUkP4O4ABOfwHpJDZTMJIESDVAgiWgVVDgNVSB1TincESXARJlWgWVQhGUuCBFgSJa%2Bv0WptRAB1P2PV%2Bq40GkDUaxNSYoxmmwTgTQWAEg9ItJgrwDBGFhtAu4XAsq7XwPtQ6x1ZBnTjtIBOSgk73V0FTF6b12YXyvjfP6HBAbDVuM8UGp5iACKESIt4asJFSKygjJGBMUbf38GYP%2BWNuqsK4QkMaJNUDIxGPwwRi07FGC4NArgsEaC0FpvTRm91OasyVik7mvN%2BYOCVsLZkYsJa/WlrLeWitnbKz2GrDWQV8A/DqESXWQV9bIENkrE2XRfoWytqzW22wgoOydvFV27tMCe0qREUAXV/aBwUCHMOEdGBRyUbHC6qjZCJzukFLRqdfblysJnTp9c84FxDJwYuBBS7%2BGxLsyu1cEi1zVPAY%2By8Z5%2BAgK4Hesku6lA3n3NIA8sgL2HqQUemQD69yXk3Ve/QPmNxXr0Ne3cflb2hYC3eCLvmH3PmsDYZ9f6YIMbQzgljrHCNEfYqJjiNAIw/vtdxv9MYANIEAkBIwG5m2wbgyR2UPSUI9HlSQSCVqyUMXQ2wDD/6TOYfAVhQ1gYBL8cQHh2x%2BFQxYAoAkzYCQUouDMWRn9a6KNOssiQqzrrqI2ToAIpAdHvWdvon690WomOBuYsGKrVpqo1XGbVz4ZjOKCa4hI7j/BeKYb4gNhN5URpRuyZAyRkjOi1dA50OqCBmSsStam8SEiJKZizbmaT808z5gLHJQSRb5MltUzAMs5ZiFKfFFWlTem8Bqdrepv0mktLKW0s2QVOnW2BD0%2B2B0BkuwSMM0Z3txlMIDkwYOodw6RzKdHZRKyrryHNcnK1YjjAZxsAcx5wVjmtk4GKEu6cK6WCrrfGuh0Hm51hS8lubcchAq%2BQscFwK/k9BhSC4oiLMUQrhXPFoqLgMvNA2CyeYwUVvrRf0aDR9sXRSxWbAljqiXuueJ6zVPrdh%2BvfnIr%2BaN6USuxoA4BoDKAXw5SAMwkj/BBEKjlBqTGPREJoZh1qYrGGTNSiASQgQYGBDKsVaBkhoF5TgVwfwmD/AOuapwBl/HME7S40pnj3jlirFdukZwkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/concepts/deceive.hpp)
- [unit test](../../../../tests/unit/concepts/pagelivore/deceive.test.hpp)
