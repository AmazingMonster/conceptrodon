<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsRoadful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-roadful">To Index</a></p>

## Description

`Omennivore::IsRoadful` accepts a type.
It returns true if the type is a packed `Road` and returns false if otherwise.

<pre><code>   Type
-> Type == Road&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsRoadful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsRoadful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsRoadful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<typename...> class...>
struct RoadLike;

/**** Items ****/
template<typename...>
struct MoldLike_0;

template<typename...>
struct MoldLike_1;

/**** Tests ****/
static_assert(IsRoadful<RoadLike<MoldLike_0, MoldLike_1>>::value);
static_assert(! IsRoadful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsRoadful
{ static constexpr bool value {false}; };

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
struct IsRoadful<Warehouse<Containers...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCAAzNIADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn4B1bWZDU0EJZExcYnSCo3Nrbkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLMn0bIJMdVf7J%2BeXR99HH2enZwImHuBiBJgSbgIAE9koxWJhwdgAaNiF4HLcFAAlVBMdBULy0AEmADsFiu00cyCuaAYo0wqmSxCu0VQniuADcxF5MFcSRYqGIlCSACLgskisVE85AkEvBHncFuAFXFVXGUPOWK9WghEQ6Gw5hsAB0JsR1IMCgUJqNZuQFoUVwA6k1MAgVkpSMrVdrNXqYXDjaaEthzUxLdaPM8wnEFETg8iCKj0TcsTi8QTFc7iK73bq3JHGtHiFag0j4wrSeTGpTqQI6QymSy2ZzvDy%2BYnuRKEuLiaLu1KLj9vn8vtsrthVKwHjz3gDR0PjgPR1cAGqYS01N6L6XAjVgvW7nVa/2GzDW2328/ls4otEEK7Y3GhADWuqsCs%2B%2B1uMods53sv3SET3hK8kXOW90QAWU8dAX0wAB9DRJQ/QFD19ICDRA0sEyTe9oNoWC8FfeCuGQ/5P2uAAVdcCF/bcb2rPBkHgsMlGaCAU0fdNCQhLi4MVfDCOIwIrkEuCSMRREQBAFtuQWMiKSYliN3YsAwAxLj8R4twwgIKSZK5TB5O7DglloTgAFZeD8DgtFIVBOCVSxrHJFY1jbMwEh4UgCE0UylmfEALMkI0NAADjMMwAE4oq4CzwrCrhiWJaRzI4SReBYCQNECGy7IcjheAUEBAl82zTNIOBYBgRAQBWAhki8AhyEoNB7joOIInhThVDCgA2ABaPrJCuYBkCpKQjTMXhMHwIhiDwdA9H4QQRDEdgpBkQRFBUdRytIXQuFIAB3YgmGSTgeDMyzrL8%2BzOAAeSaxr71QKgrl6wbhtG8arkmswrggDx2voJlzC8hZeDKrQlggJA2uSDqyAoCAEaRkBgCkMw%2BDoIFi0oaI7uiMImihS7eGJ5hiChB7om0TAHHJ0g2qeAgHoYWgyf2rBoi8YA3DEWhiu4XgsBYQxgHEbm8GzBw8HZdc7vpBmmo2bzdJqO7aDwaIzupjwsDuxM8CykXSAV4gWSUYVgQl7WjD8pYqAMYAFBXPBMGOh6DSZlbhFEcRNr9na1Duw79AllBrGsfQdeKyAllQZI6mFgbRnQcFhVMZzLDMfKLYWrB44gJY7AZuoXAYdxPDaPQQmjOYhiOgoMgECY/GbtJW4YWZBniI6y7lgQenGGvcgHmpy%2B6MY%2Bgbvu9GmUecg72wZ978om9Ltz1gka6OCs0g8t4AqPv6oaRrGiaQoBiBcEIEheU8rhIZ8x2lgQTBcSGEvSECyQEiNFFBIKUNCSDMJIPqOULJ9SivoTgGVSBZS8kaPqXA%2BphSiolPqwU4pAL6ofO6BUiolVfuVWGNU4Z1Wek1FqqNUAg06t1DgTQWDsmJANJgoYjB/SikaLgoUZpzRIItZasg1qB2kMHJQod9q6Gxqdc65M94HyPvdDgT0GpNSuG9U%2BX0Rp2gljwvhoVAbA0RqDR%2BCQzAv2hhVShaNQa0IcUMAxRguCxUCDQWgeNioQEJvtSmpMmaBOprTemjMzYs0YGzDmXM7I8z5gLWgQsmZizthseJMsp4K2FnZZWyBVZMw1mlOy2tdakwNhkqGC1TbeQtlbTANtxZGHtqAMhfAXZuw9l7H2Zs/biI2pI2QIc9p2TkRHB22crCWFjtEYuidk6ZFTunTOUzrB52PgXRaisE6dCns4CArh251yruveYndCiZGORc7uZym57KHvUGe1yHl1BHrPUo88B7PLHivReHyBgb37lvVYO9n5wP3rdfaJ9Prny4cAIx/CNCAzvvNSxz8oZv1IB/L%2B8Qf5pQQUg3hoDiQWSislJI4DhpHVUUQ2wJDbHkPgJQ%2BqL0nH0PMYwtgnAWHfRYAodkVJ2TuKNDqUYgj76F1EatAOgytryGkaMnQiQTpnQuiLZRUL8qPWoa9d6qg%2BUCqFSKsV94gYcqRpYhINjHaVXhhaxxKNnHxEFckZI8FhVRXgqa%2BCBrJG4xjATImJNqbBJDTTOm5cmZRMEOzTmd0En80FsLbyaSWlVNIPgWWjgclK1UCrIERTBCa32mUvWUJKlGxqUzepaRGm2xaWENpMMOlMFdu7T23tGC%2BzEbKiQQztqKrDiqgwkzo4zLKfM%2Byiy6ycE2OnKOOcLAbPslsou8BS6T0eZXauy8TmEU%2BUCvQLc6gvJPZkO5/dXnT16C8weby15zyPd829vyF6PsPeckF7ld4QpUYQzgH1DWCo5CauUowUVCLBk/G1ZD36fywHivehKQDRSNAkBIFl4qSC4DlDDxJ0EEOhZwYhpUsV/wsoApKxIcphUkLFLgEUzD4LSgkLVx8SOkJhnvaaRHtWFS4/5c2MZMj%2BCAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_roadful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_roadful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_roadful.test.hpp)
