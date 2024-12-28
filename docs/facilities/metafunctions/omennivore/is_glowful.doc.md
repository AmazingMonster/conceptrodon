<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsGlowful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-glowful">To Index</a></p>

## Description

`Omennivore::IsGlowful` accepts a type.
It returns true if the type is a packed `Glow` and returns false if otherwise.

<pre><code>   Type
-> Type == Glow&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsGlowful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsGlowful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsGlowful_v {RESULT};
```

## Examples

```C++
/**** Vessel ****/
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct GlowLike;

/**** Items ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct GritLike_0;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct GritLike_1;

/**** Tests ****/
static_assert(IsGlowful<GlowLike<GritLike_0, GritLike_1>>::value);
static_assert(! IsGlowful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsGlowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines
>
struct IsGlowful<Sunlight<Sunshines...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzACspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJlibgIAE8koxWJhQdg/sNiF4HNcFABxWioADuVC8tD%2BJgA7BYLpNHMgLmgGMNMKoksQLhFUJ4LgA3MReTAXYkWKhiJTEgAioNJwtFhNOAKBTzhp1Bbj%2BF2VF2ld1lCrVwLhYK1Gt1gPVIINMuN4MN2s1Fv14KhMLYADonfCqQYFAonQ6Xcg3R7nbFsK6mO7Pd7faGA0GQ/7Az7g36vZG4%2B6LkIvAxaHhgAgCKQlSq9WbCzrzaaS8WrWXK0by3bmI6Y1GE2H4xHY%2BHG8nm0mO4n262nWmaQhgpgFISA4iCMjUVcMVjcfiFUPM9mCMv0woRyFuwjJ/KSWT6hSqQJafTGczWRzvNzedOueLYmKiSLn5Kzl9Pj8PpsLthVFYO5uVeP5fy/Q4P1/C4ADUxzsF5IKla0ixQ8s0OrS0TRrTCbQrXU61hNsm2IrtSN7Ftoz7EjOwo/cTiRFECAuTEcSCABrHUrHld5dmuaUFEQ7Yfnw0scOwrCxMk0SZMIhtqLI2iBwUuj%2ByoyjdynGdmPRYhCA4zAAH0NAlHj/gwiS8IsqSrKrSyizkzByOUjTnPUnsXI89yEVORjUV0/S8E4wyuFM35eMuAAVMcCEE0DfOPPBkEM%2BNogICA51YxcCTBLKDIVAKeiCoyNFIFi9KK4LQsnAMQBAG8uTmMLySSlL3TSiAwDANEsrxHK3GCddavqzlMCa99Tg4BZaE4eJeD8DgtFIVBOEVSxrDJJYVjvMxYh4UgCE0KaFnYkB4kkB0NAADjMMwAE47q4eJrqurgiSJaQZo4SReBYCQNFKhalpWjheAUEBSsOxaptIOBYBgRAQCWAgki8XMKAgNBbjoaJQlhThVCugA2ABaInJAuYBkEpKQHTMXhMHwIg9PQPR%2BEEEQxHYKQZEERQVHUaHSF0NpsWIJgkk4Hhptm%2BajuWzgAHk0dR5jUCoC5CdJ8nKepi5abMC4IA8bH6EZcw9rmXgoa0BYICQLGkhxsgMcd52QGAKQzD4OgAWIcGIAieWImCBoISl3gQ%2BYYgIUViJtEwBwI9ILGHgIRWM3DoWsAiLxgDcMRaHB7heCwFhDGAcRs7wYhE8cNkx3lulE7RtZ9sGqp5czCJxZjjwsHl6c8D%2BkvSAb4hmSUIVAQrzMjCOhYqAMYAFBgvBMGxRXoQW/b2eEURxB5vf%2BbUeWRf0CuUGsax9DwCJwcgBZUCSGpi5J4Z0FBIVTHWywzGB8eLNG6P3aHXDILgGDuE8C0fwkDpj9BiG0PI6QBBjFaMkVIKCGDwNKAMCYVQwECC6KMaB4xQEOE6CMIqxQEF6EmCQ7I6D6HUL6LgxBCwFBbVWBIGWHA5qkCBrwEGmtiZkwplTGmF1DYQFwIQEgPJdpcCtgdBeCwECYCYFgGIEATogEkLEB0d1YgfQ0JIMwkgiYA3iETO6%2BhOA/VIH9PaDoiZcCJldO6r0ibnSekYomAj5YgzBhDFR0M7YI3tkjFWaNyCUDdmbPGbBOANBYGyIkJMmBBiMPrO6DouCXQZkzEgeBWZtD3pzQ%2B0hj5KFPkLXQ3sxYSwjrw/hgiFYcGVijNGFx1YiO1hTOM2SuC5PyRoI2JsnZmwUbEMwyibYw0ifE6IsTMaoFNgMQZntHqlRoLQP2Acg5CyjmHZOxyY5xwTknUeqdGDp0zvLHOecC60CLsnMus81hLXwLXChDdi5LWbsgVuycO5fSWt3XuEJ%2B6fOtnpEe%2B1x6T0wNPcuRg56gDCXwZeq916b23sncpB9uZVNkCfQWS16kX3nj/Kwlhb733gE/F%2BGQ34fy/jS6w/8hGAJKcAnR5CagQKgYw2B6AcGzCQZgmoaDchSoyOKvBArKHdBlfgjoRCqEKsQbYKhqqdVTFHDMPBHCuHcxaXLIWwitZiKycAHJeTLpG1kczaZSjraqNIOozRAx%2BVfQcU43JpiiTxDuu9WIZiLGSDaG0oJtgQnzPCfASJyNVYrKWcQRJawUk6xYAoNklI2TDIdNqYYhS5EszZrICpxLebyBqeSnQcRSCNMliXc1ATLVK2iWrDWqgc15oLUWktzFjZrMmdEaZsQ5kL1hg7Mdzs03zrNvVZASQkiGULXdQyw7DJ9qqb7aIBzg6hxjqck9sd4512TjcwQGdaBZy%2BZgXO%2BdC7F32u8tFMLSDfLAX8puqgW4AhBYITuQsIVh2hYPOFydEWpGRTPNFwQMW2yxUwFea8N5b0YASqtRKJAkr5vWs%2BTaDDUuvnS7uD9%2BXP1fpwdYH8r6/wsFy5aPKsBUY4QQihzgICuD1YEQ1tDJX5AyHq5BNQtV0K4zUYhTRSFMOk8qxokmJi6vk3QzVgm2E8MWMsbhSi7F8ItcDTgmt%2B35vZEO2UwwnVFPNoo6dYS1EaK0ZQXh/qQD3QdLEBIz0o0Ax80SdxHaTOgzjZDD1p1JDxEMW9IkAMrqSEelwG6Zh/FfViMZoRnB3VOcM/TEL2WwsJoWOPNIzhJBAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/is_glowful/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/is_glowful.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/is_glowful.test.hpp)
