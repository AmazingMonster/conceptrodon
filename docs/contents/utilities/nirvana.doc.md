<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Nirvana`

## Description

`Nirvana` is a vessel for `Dawn`.

It also contains a regular function, `size`, which returns the number of items it holds.

## Type Signature

```Haskell
Nirvana ::   template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...>
struct Nirvana
{
    static constexpr auto size() -> size_t;
};
```

## Examples

We dawn create a `Nirvana` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we query its size.

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_3;

using PackedNirvana = Nirvana
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

static_assert(PackedNirvana::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...Items>
struct Nirvana
{
    static constexpr size_t size()
    { return sizeof...(Items); }
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAQBspAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfP3eTE%2Bp0BfwBryBIO%2BkPBoNhwP%2B8N%2BiK%2BTC8RAAdNibod9kwFApsZjcfjCcTSQZyTiAtg8VSiTS6WTGSTafSCazKZziQBJH4KG5PcbELwOQ6RPDEABuhiYTxMAHYrA9DmrDrNHMg8QJxphVKliBq8AAvTAAfQIxrNECWT3Vx2Vh2ImAI6wY1swqCoxIg/NeCjtAQsjoAIgrFeHgwqHgB6ABUiaTyZTsaeCaThwAKtghFmhIdk2m4ynS0WY48zLsGPsvEcvmga5hUgRBbSK2DUcioUiYSjoZ2Bwih/3e4Pe%2BisUyOdS2cyGRT2SzF/OedPl%2BuF0zhQRReL/SxzRoTirHg9xxDR5ee9e4X2b927xfTpPUCuZ1yl1u5x/3xuf/%2B3KzkKDwimKVoHuaXAnh2w5jnBt5dveT4IY%2BSHPm4r5/t%2BQGfquwFfmuAE4YRBG3KBu7gYckFmDBDxPBhjGoch6HMUxV4vhib6bkRuHYbxpF4b%2BPFkTue4QT85oBHRZ73F4mRGIcyhMMgADWmDoJKMpyscAShhKUqyswCqnPa6qQRopDHKq5mSVwVlmWqNEOTZTmSdJ9HttG9EUcCeDIOanLxAQEDKWpGlaUZTAgCAmQ2ksulRvpkhBqeHArLQnAAKy8H4HBaKQqCcG41jWBqawbJgxxVjwpAEJo6UrKpIBZRomJmGYACcAAcGidVl3VJAEkhmIqkgpJlHCSLwLASBoll5QVRUcLwCggJZ9X5elpBwLAMCICAawEKkGLkJQaBvHQ8SRKwWyqINAC0SSSIcwDINqUjtbwGmECQeDoHo/CCCIYjsFIMiCIoKjqFtpC6PZADuxBMKknA8Bl2W5Q1hWcAA8hiJ1Wt6hz3UkT0vW9H2SO1hwQB4l30EaOxcEsvCbVoKwQEgF2pFdZAUBAPN8yAwBSGYfB0C8xBrRAMTYzE4QtAAnmjvAK8wxBK7jMTaJgDiq6QF1sIIuMMLQKuw1gMReMAmG0LQa3cLwWAsIYwDiJbUp6440qYI7BX6nrGJbLV4QvJNBW0HgMTI5rHhYNju54LNTukL7xAxBkmChq8btR0YDUrFQBjAAoABqeCYAjuOpIwBtA8IojiODDdQ2o2Pw/obsoKVlj6NHa2QCsqAttkjsPRcJyhqYljWGYS3p8Q/1%2B/AKx2N72QuAw7ieB0eihOEQyVCM9lFFkAhTH4p8ZOfDDzMMCT2evDi9BMbS7/kT91BvAh9K09/H0frYN%2Bl89CzH/ofBYJ814VU2BIDGHAcqkEWrwZaJNHrPVeu9Q4n0zC01wL9JmNVWZ1ULisBAmAmBYASLaUgzVAiYk6gEMaGgRrjXmllJInV9CcGmqQWaAQuCYiSFwJI3UeqiKypILgWUmEpBQTjFath1qkK2pzfaXNDoE1OgLIWjMbpsE4C0Fg0pFQPSYByRSXBOqYiEQHfARAl4A3sg3EGzdpCtyUO3WGuhxZIxRqrBBSCFHLXxsdDEhxibGNMeYyxwAcE2LsbTemvNGbVQCGYEh7NtqaL0fEM6gtUAMxGNEsx%2BIjDWK4JZGgtApYyzlrDdWysDZNM1trXW%2BtU5G0YAQU25tsZWxtnbB2BsXZ5y2AVfALoX6%2B39t9VQQcXgGzDnUbGUcY7K3jhMtmS8U61XTpnJQOdXZGHzqANRfAS7l0rtXWueVaquKbmDDxsg24wwKr4ruBcZ5WD7uswetCR4NHHpPPSPy54L3iE4leQ9ug/z8BAVwoD7IH3KA/PQZ8GjIrSDfBoADFhfx6L/EBH8r5wpfsSuYkD0VPxJXkMl4CBjUsAfA1Y6w4Esx4YgrGsM0GlNieU%2BJ1jbGYg0PghxJB0kszZmQ0gFCqEjFoZNPhAibGsMVLIxUiphpmHGtI5B2NlqrRUdk9R8BNFHUJgUvJxADFbGMZglgChpTamlMKv44xvoSqcYDWQbjnkQ3kF495OhEikH8ajJ2QSeVLTxtoomVBDgOpek6l1hw3U2I9VaOmRTUnxHSQELJhcdrc1zXza1ZbGYgBdakVI5oM3mizYFYgLBnoS1qfEep8tFaaxaT2rWOtvYG26SbM2FtJmYGtrbMQIzU5jNOds0gUyN6zOxoHZAwdlmCFWbDdZsclZbMTrsg2Bys7HLzuEc5HNLlMFLhXKuNc66p0eaDCQLzIbBo7mGgw3ze42H%2BavQqo9dScFjBcHus9LDz1QYvZeAK17fwpQipFpL97b3xSfHFxRsjYsxdkDDQDn4ND/u/elYDEPEbfgRsBdK960qpWillnKFCwLBtGg1vLOBJpbY651rr3WInGOKwhUqi1qPIZQ6hlAEEqpAF1TEAQAhZVatI%2BainFRiI47GpRa0NqyvoTYrVGhrGsK4MkLKiozBSK5QEGNqDOAyvE1yswdnFGOY5isdOmRnCSCAA%3D%3D)

## Links

- [source code](../../../conceptrodon/nirvana.hpp)
