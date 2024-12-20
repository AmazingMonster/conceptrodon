<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsSameAs`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-is-same-as">To Index</a></p>

## Description

`Typelivore::IsSameAs` accepts a element and returns a function.
When invoked by an argument, the function returns true if the argument is the same as the element and returns false if otherwise.

<pre><code>Target -> Element -> Element == Target ? true : false</code></pre>

## Type Signature

```Haskell
IsSameAs ::   typename...
           -> typename...
           -> auto
```

## Structure

```C++
template<typename>
struct IsSameAs
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Examples

```C++
template<typename...Args>
using Metafunction = IsSameAs<int>
::Mold<Args...>;

static_assert(!Metafunction<int*>::value);
static_assert(Metafunction<int>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<typename Target>
struct IsSameAs
{
    template<typename Element>
    struct ProtoMold
    { static constexpr bool value {false}; };

    // This partial specialization will be chosen
    // if `Element` is deduced as `Target`.
    template<>
    struct ProtoMold<Target>
    { static constexpr bool value {true}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr auto Mold_v 
    {ProtoMold<Args...>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCBmGqQADqgKhE4MHt6%2BASlpGQKh4VEssfGJtpj2jgJCBEzEBNk%2BfoF2mA6Z9Y0ExZExcQlJCg1NLbntY31hA2VDiQCUtqhexMjsHOb%2BYcjeWADUJv5uBACeyZgA%2BgTETIQKx9gmGgCCL68EmCzJBl/HpwujFYmAOABVGsBMAQnh9RsQvA4DgBJBRCEGvR5vEwAdisbwOhIOXx%2Bf0wAPOl2YbAO2HobEEsIJRPhiIIB2UxFQRAAsp50B8iUc8QdRkxHMgDmgGKNMKpksQDtFUJ4DgA3MReUG4ixUMRKXEAEWOFmFxv8%2BPezMJJN%2B4vJJyZryFrKRnO5qD5tAFJwhxChMP8z2twtNYolUoEsvliuVqo13m1eNuWqNJrNJo%2BgqJtrJFKB1MwADoS69gMRMN9GARHkHs4SvOkjAcvegjv5DRyubz%2BQCyxWq4IFCWi7CLVmQ7n7fmqSCR69/bXg86WQ0I9LowqDkwvEQW/yrmqjiGde6e96%2B4uR08QCAE6mcebLWnx9i3gB6ABU35/v/fHy/b8wWwIQwR/f8P1/KDPwgq1Pm%2BO1/hOSlgTYedFydRswmAFtoSYKgvAYLoBHbTtUXRNhMQBMJA2XW9W0vYBhxLMdnzecM8GQK4mAUJQmggMAwB5PCCKI2oGGowRPxvO9NUwRZM3YtdOO43i4gICBhIaUTiIkk4aJk%2B95JNDhlloTgAFZeD8DgtFIVBODcaxrFFVZ1m1Mx/B4UgCE0UzlgAaxACzJCLDRJC4HF/A0CyNDMAA2eKzAADmS/ROEkXgWAkDQkhsuyHI4XgFBAJJfNs0zSDgWAYEQEBVgIZJd3ISg0B%2BOg4giEFOFUZL4oAWniyQDmAZBJSkIszF4TB8CIYg8HQPR%2BEEEQxHYKQZEERQVHUCrSF0LhSAAdzuZJOB4MzLOsvz7M4AB5XcmvZVAqAOXqBqGkaxoOCazAOCAPHa%2BhFW2LhFl4cqtGWCAkDa5IOrICgIDhhGQGAKQzD4OgvmIEqIGiG7ojCRoznO3gieYYgzju6JtE6crvLahkCDuhhaFJvasGiLxgDcMRaBK7heCwFhDGAcRObwCsujVTBBbsuVOl3TZvJo6obtoPBojuKmPCwG7bjwbKhdIWXiGVJRDW%2BMXNaMPzlioAwmIANTwTAjruqkyc24RRHEDblvkJQ1Bug79DFlBnMsfQtZKyBllQZJxMF/rRh9Q1TEsaxEl4VAzfmrA44gZYOl0lwGHcTxWj0EJZlKco9FSdJxImPxDqbwoGH6euhkO0vxJ6cYq9yPvqnp7ppm7wZ4j76ZW70MUmin%2BYZ5LtyNgkS6OCs0h8tzzg3r6wbhtG8bQr%2BiBcEIEgjk8sGIft5YEEwJgsHiYvSCCyR/CLABOfwcSSHCmYSQ8VcoWXir/dKHBMqkGyl5Is8UuDxWSr/ZKyCQpcAsv/eKu8bqFWKqVHy9sqq1RhvVR6zUkYo2Bl1NgnBGgsDVDifqTApQGGbFwX%2BRYuBhWmrNEgC0lqyFWv7aQgdtohz2roTGJ0mBnSFlvHee9bocAeo1XcBwXrbmIEwlhbC9hix%2Btw3hGh/qA3hsDW%2B/gzDg2IRVaGsNUBAziC1ZGzjLFDEYcw/qhijBcK4EkGgtAcZ4wJntCmJNvaRKpjTOmDhvZM2rKzdmN0uY8z5rQAW3sRY202HZfA0tHCy3ltNVQSsvjezVuZPamttYkz1vkiG81jbeTNhbTAVtRZGFtqABxfAnYKFdu7T2jBvaB1EetcRshJG7TsjI8OdtM5WGjnUouCck6ZBTmnY4Gco4WBzvZfOC05bwBLmPMuEBXDz0OrXEo09G4FBbsPNu%2BRm6ZGXg3UeNQJ69BuVUH5dRJ51webPP5LyF7AvuSvTeKw1gbzBtA5R%2BCD7eP0ewoxXCeFhX%2BlfOa1j772Khk/F%2Bb9KBb1gfA7h4UcTYJxFFSQIChqHRUQQ2wRDIaVWqnVBqT03E0M6t1DgjDPosAUGqSUaosVklGPw6%2BBdhErT9lMn2szQ55DkQoi6SLrp7UKuop6WjXoiuGmKiV6ppX2lGOYjxCNrH%2BDsZyxxKBbXA35a6oYErkjJEPFwq4MqCDcV0UNLGIS4hhMJsTKm0So3U1pvTRJzjmYpI5gUzA3Neb80Ft5XJPSmmkEKePEpN1FbIGVlUwQ6talax1mcRpBsWne3aWkTp1senYRIY7JgLs3Yey9ibCZyqJDTK2sHOZOg8gcOMPsmO0R1n2U2VGTg7406RyzpYQ5ec4gF1OfHAF49nBXIrv8u5cwvlvM7v8ju4lPm933bpQezQIXfIPQwR9t6Z62Dns%2Br9vQP2woUOvdaSjdUFVRcG014rJWWq%2BNay%2BAiQZ30dY/Ugz9X5DA/jUylCRuH%2BH8BZWKEVcp4ZxCgvBerOCELKihr%2BFk/4WWSglX%2Bkhf5RQAVwQINT/Cgf3kVIl/loFTXI2BvjTrlhm3SM4SQQA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/is_same_as.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/is_same_as.test.hpp)
