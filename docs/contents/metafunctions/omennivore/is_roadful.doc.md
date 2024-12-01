<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsRoadful`

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
template<template<typename...> class...>
struct RoadLike;

template<typename...>
struct MoldLike_0;

template<typename...>
struct MoldLike_1;

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAOykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG4EAJ4pjKyYR9gmGgCCY8ReDgDUAJIKAEqoTOhUXlod3uJkSFleM0cyFeaAYY0wqhSxFe0VQnleADcxF5MK9QRYqGIlKCACJHcGk8nA4HbXb7a4PI5uYGvVmvWl7JgHY4c%2BlMs4XZhsAB0opuMIMCgUouF4uQkoUrwA6s1MAhVkpSCy2byudceedLiKxYdsBKmFKZR5BEwwnEFNTTcCni8CB9vr9/oCmSriGqNfq3NamnbiNKTbcnYywRCmlCYQJ4Yjkaj0VjvLj8QRntdEmTDhS81TGQ8APQAKkrVerNdLwIrVdeABVMGNFdW62Wa92O9SHrruScdpzBwKjZgZXKFZOo49s67Xj8/qEANb6qwl%2B4DwNjoUTiPO%2BdvACynnQq8wAH0NMWQf3h3yDYKrjPbg8XSezxfL1xb4euXgyCXhaSgtBAnxLl6QLHJBF5MqetDnnga7XqQrwIUhKG/k6pogCA6Y4ost6QoBwFSnEBAQGAYDupBALQW4YQEDceEEZgREFhwyy0JwACsvB%2BBwWikKgnDMpY1gQqs6yZmYhw8KQBCaFxywriAvFmMKiRmJIAAcum8RoACcGkaAAbLphz6Jwki8CwEgaIEgnCaJHC8AoICBEpQlcaQcCwDAiAgKsBApF4BDkJQaC7HQcQRFcnCqLpZkALRmZIrzAMg0JSMKZi8Jg%2BBEMQeDoHo/CCCIYjsFIMiCIoKjqD5pC6FwpAAO7EEwKScDw3F8QJykiZwADy4VhW6qBUK8SWpelmXZa8uVmK8EAeDF9DIuY8mLLw3laMsEBINFKSxWQFAQCdZ0gMAUhmHwdDbGGlDREN0RhM0py9bw73MMQpwjdE2iYA432kNFbCCCNDC0F9zVYNEXjAG4Yi0B53C8FgLCGMA4jw3gfoOHgGKtkNCIg%2BFmwKUxtRDbQeDRF1/0eFgQ3Zng9kY6QJPEKiSgkjsOP00YynLFQBjAAoABqeCYO1I2CmDFXCKI4i1crDVqENrX6DjKDWNY%2BgMx5kDLKgKT1OjKVjOgRwkqYEmWGYLk8yVWAmxAyx2CD9QuAw7ieO0eghHa8zDG1hSZAIkx%2BBH6RRwwcxDPEbXe0TAi9BMgd5KntQ%2Bz04z9KHyd6DMWe5LHtiF0nFTh170kbBI/UcPxpDObwrkzclaUZVlOWSHlq24IQJB4nJXC7YpovLAgmB/MMnukGpkiHMKRmHIkASSDpZmObxZlGdZHC2aQ9nycKZlcBZRm6VfvGSFwvHr2ZbdDa57meVPPmHYFR3BeN4VIqXVQBtOKCUODNBYBiRIKUmDmiMEtIywouDCmEoVEebtyqyCqmraQGslBa2aroe6nVurfWbq3duw0OBjVCuFV4U1XiQOgbA%2BBwBEHINQatdap1Npj0OGYSe%2B1fJ/yuptIBYjhjMJgfKHGXAjJcECDQWgT0PIQFes1X6n0wZaP%2BoDYGoMuYQ0YAQaGsMhoIyRijWgaMwZYyFpsYS%2BBCaOBJujNBqgKbbDBjTHizV6aM0%2BizRxe0SqcwUjzPmmABbYyMMLUA38%2BAS2lrLeWisubKxwTVPBshNZNWEsQ3WIsHZWEsEbaIHszYWyyFbG2dsSnWGdh3V2pVSamy6PnZwEBXAx2Dv7GuCw45FCyL0oZCcBnhw6enBohdRlTPqJnIuZQS6p1mdnSuZclmDFrineuaxG4TyPpQt%2BnAmHECgTAuBsiEHyM4RoIeRVR7bQnntaepBZ7z3iIvPxJ8z5II0JIRIT9EiJEONvSQ6U2pUPfrYT%2Bwif7wD/iFCaEiQG8LAWwTgkD5osAUBiaEGJbn0jGAVR5mC2qZNVtkuq8gCH5J0CAKypCeoYwoYNZqrlaETQYdNbFGVcX4sxESvUYxuForOvww4QjRZ%2BWOuK8RF1JHxHxSkFIl5CVGUvMSggwFznpQeio%2B0L03ofX%2Bjo01AMgY%2BzBsYqGMM4ZOMwIjZGqN0YKXsXEkJpBnH5zcWTTxyBKY%2BMELTfxDMmanGCWzMJYNInpGiYLOJYQEkHSSUwSWMs5YK0YErbBVKJA5PqnS7WjKinGANmUgJlSRLVMTJwUsNt9aOwsE0kSLT3bwC9nnaZfsA4Vz6UhZZOy9CR3qHM0dWQJkp3mQXPocy04LOrsXYdqy53rNLkuodgy9kySbkc9lLlTl8teAKglwrtiiogMPYq/CXlfwOjPOeWAvnN1%2BQkJBhxDi8UMg/Ryn7EgWVfhyzgH8vJvOXokPKQKuBSCMgCxI68uDJD8YcA9HcQP3pUkffKQHD1uUw4sZYPMMjOEkEAA%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/is_roadful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_roadful.test.hpp)
