<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Arcadia`

<p style='text-align: right;'><a href="../utilities.md#arcadia">To Index</a></p>

## Description

`Arcadia` is a vessel for `Glow`.

It also contains a regular function, `size`, which returns the number of items it holds.

## Type Signature

```Haskell
Arcadia
 :: template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...>
struct Arcadia
{
    static constexpr auto size() -> size_t;
};
```

## Examples

We glow create a `Arcadia` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we query its size.

```C++
/**** Items ****/
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_3;

/**** Packed Vessel ****/
using PackedArcadia = Arcadia
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Test ****/
static_assert(PackedArcadia::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...Items>
struct Arcadia
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMT%2BAKykAA6oCoRODB7evv5BaRmOAmER0SxxCZLJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpgprozIeJgKd8cX17dnAJOvyulxBZgC4WQ3iwdxMATcyFm6CwVDh2FBoP%2BgOxh2BWLuAEkWCl6GxBExet8jnicbTzhjrgRMMSDEy4W4mSyKZh2ZySdzecz%2BWz4XzWTzRULxYKuSKOVKBaKAJ4vZhsAB0mrRdyhTAUCk16u1uv1huNBlNWoC2B1FoNVptJvtRuttr1zvN7sNBM5CjRoNmxC8DjuVy2THwTAxAHYrNc7gm7rMKXhkDqBLNMKoUsQk3gAF6YAD6BDzhYgK1BidhsbuxEwBE2DDLmFQVENEB9zIUlYCFhrDxjg77DJudJ%2BmOOd2wqlYJMwVNxk/HS%2Buy8OhN9i/pjIVcrFivlsolR%2BFJ4P%2B7356vvJVjFYmDNrqdT8ddtfbstLrfXodn49z7vg6AYEEGIZdiwRYaHCcYgrux4ymeiHSpKCGoUh6EoaeWEEHeaqPn%2BL6EUB37/h%2BRGkRRnpfv61yBsGpYQUWXAwaOF7Xmh2GHuxyHcTemHcXhD7kSR1EAT%2BNGAb%2BlGiVJknonRoEMZuzJFmYrFrvBGFcZenE8QJunafpHJCRqxHSWJIkWXJ4lkeZ8kgWBjGckWAQaXBY73MoTDIAA1pg6B3AAap8djbsCXgZEYdzeX5AVhqIkawgEDyhuGkYYvCVaJkxGikLC8Y5S5XD5dlCZMWYpWFeVLluWu1rueu%2Bx3AAKp8pYTopKbIEW7rxAQECxf56AJRGeBMCAIAZOWKzJcOqWSL2FgcGstCcIkvB%2BBwWikKgnBuNY1hJhsWwLuYAQ8KQBCaCtay%2BSAiSSOqGgABxmGYACcH1cIkr0vVw0bRtIa0cJIvAsBIGh5VtO17RwvAKCAeXXdtK2kHAsAwIgIAbAQKReAQ5CUGgxJ0PEkQPpwqgvQAbAAtDTkh3MAyBplI6pmLwAWECQeDoHo/CCCIYjsFIMiCIoKjqKjpC6CVADuxBMCknA8Kt62bTdu2cAA8gT%2BOlm2dzU/TjPM6zdzs2YdwQB4pP0Lm51cCsvAo1oawQEgJMpGTZAUBA3u%2ByAwBSJVNC0EyxCIxAMRazE4TNEqqu8PHzDEEqOsxNodQo5dJNkgQOsMLQScy1gMReMAbhiLQiPcLwWAsIYwDiGXeD1vUABunxa1mdQEzsl3hEyIM7bQeAxEr6ceFgWugXgEP16Q3fEDE6SYE8TdGOPRg3WsVAGMAChBR88s66qyfi8IojiGLgvyEoaha3L%2BjNygh2WPoE%2BI5AayoCkvQ650yRHCB4phLDWDMLDFexA%2BY91/l0HoWQXAMHcJ4doehQgLHKJUPQhRMgCCmH4Eq%2BDehDBwaMEqtR6gCH6JMdBeQqHdBzg0OY5CRgJCoXMIhehkwtHYUsThawFAnW2BIdWHANqkBhrwOGxtaYMyZizNmT1rYQFwDzR24Jnauz3msBAmAIyjArKQe6gR1QfQCEDDQkgzCSBplDRINMPr6E4GDUgEMLrqhplwGmL0Pr/Rpo9H6liabSK1nDBGSMrp73RljT2ON9YEyJgHVA9tyaUw4M0Fgndox0yYG6aKXAPrqi4M9Lm%2BAiCwP5iVe%2Bwtb7SHvpLJ%2BMtdCVUVsrZOEipEyO1hwPWeMCZ3CNibRRhTgCWxKWUjQNs7Y%2BwdrCcEZgXYxNRh7L2aT5nxBSYHB2KADBGGKVwPK4dI7R1jjLVOidL5XPTpnbODhL750YIXYupcdrl0rtXWgtdL6N2bq3D57cWHdzrjtPuyAB6X2Ht0LW49J6JxnjsHa89F6XRXmvJQm8AXhFAGsvgh9j6n3PowS%2BdSb6i0abIZp0sdptNfrvcBVhP7wp/iY/%2BgDODAIIOgUBTLIHQPiNU%2BBJjqG9BQWg3IxDgioIEbgkh6QCHZAYdK0hWQ5WUMQSw2h3CVW8OYTQvobDsEcN4bqqVZqBgaqEesTYYjnauMkZrGWcjRlm11EUqZz0bYaKqYsi6Ky3a3VIAYoxCQTEg3cZ4kpNjoyJA%2BoDAItj7GSBKr0yJtholBo9vEpAuMDY7M2b7CmbBODZLNiwBQnc0yd2KeqcUswKmaL5gLWQ9TKVXxpc/EAQQOkq3rt051sNdZJMNlQY2Faq01rrQ20stsi0LPOgEQNsSEm7O2f7ddCRq0pBSEWWtH0iyzqLKoRmfA6BnMoBcnatzS6XVvfcnOTy0kFyLiXLWnyq41zrpdf529kUN2BV3HuMsIVQqXjC0evB4VTyVEiuesC0W8AxevbF29cWxIPkwI%2BJ9MBnwvkvclIsJBUolo/WlOge0MuMB/GwrL4B/wAVkOuuwkTvwgZYKBsiYFwLZcIg14qICuB4SVLBZRTUKqKFkETqRFVkJNYI/VSCdUDBk2K1hVqFPyvGKpvVXDNPicUw6kRdrRaDvCS6zgE6maVurXcA99buSzB9ZUkg/qdGrPdvowxWBw0SKjSAT66oAgBESL9VNUMQvRj8RZ4d8NM3Iz0aYpIFiAbRihi9SQ30uBvTMGEkGAQh2yM4LotZEjOaxeK/F7NawV4ZGcJIIAA%3D%3D)

## Links

- [Example](../../code/facilities/utilities/arcadia/implementation.hpp)
- [Source code](../../../conceptrodon/arcadia.hpp)
