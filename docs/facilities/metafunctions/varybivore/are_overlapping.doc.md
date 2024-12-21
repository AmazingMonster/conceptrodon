<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreOverlapping`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-overlapping">To Index</a></p>

## Description

`Varybivore::AreOverlapping` accepts a set of nonrepetitive variables and returns a predicate.
When invoked, the predicate returns true if the list created by appending arguments to the previously provided set contains repetitive members and returns false otherwise.

<pre><code>   Vs...
-> Args...
-> Vs... `overlaps` Args... ?
   false : true</code></pre>

## Type Signature

```Haskell
AreOverlapping ::   auto...
                 -> auto...
                 -> auto
```

## Structure

```C++
template<auto...>
struct AreOverlapping
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };

    template<auto...>
    static constexpr bool Page_v 
    {RESULT};
};
```

## Examples

We will showcase three examples.

Check whether `1, -1` and `0, 1, 2` overlap:

```C++
template<auto...Args>
using Metafunction = AreOverlapping<1, -1>
::Page<Args...>;

static_assert(Metafunction<0, 1, 2>::value);
```

Check whether `1, -1` and `0, 2, 2` overlap:

```C++
static_assert(Metafunction<0, 2, 2>::value);
```

Check whether `1, -1` and `0, 3, 2` overlap:

```C++
static_assert(! Metafunction<0, 3, 2>::value);
```

## Implementation

The name `AreOverlapping` is probably a bit misleading.
This function used to be a helper class for `Varybivore::AreUnique`.
It becomes a standalone function since its functionality is intuitive enough that it might be helpful on other occasions.

After instantiating the first two layers, `AreOverlapping` has two lists of variables to work with.
The first list must be a set, meaning repetitive variables are prohibited. The reason for this will be apparent later on.
For the function to return true, the second list must satisfy two properties:

- Every variable in the second list is not contained in the first.
- The second list does not contain repetitive variables.

To check if a variable is in the first list, we use a method described in `Typelivore::SetContains`.
Namely, we will create a class that inherits every 'variable' we would like to check against and use `std::is_base_of` to inspect whether an argument is a base of our class, subsequently determining if it is one of the elements our class inherited early on.

To 'inherit' variables, we need a helper class that transforms variables into types.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Since inheriting the same type multiple times is illegal in C++, variables in the first list must be nonrepetitive.

We will implement `AreOverlapping` using recursion over the length of the second list:

- **Base Case:** When only one variable exists, the function returns true if the variable is in the first list and returns false otherwise.

- **Recursive Case:** Pop the first variable from the list.
The function returns true if the variable is in the first list.
Otherwise, we append the variable to the first list and pass the result back to `AreOverlapping`.
Then, we invoke the second layer by the popped second list.

Here's the entire implementation:

```C++
template<auto...>
struct Shuttle;

template<auto...InspectedVariables>
struct AreOverlapping
: public Vay<InspectedVariables>...
{
    struct Detail
    {
        template<auto...>
        struct ProtoPage
        { using type = void; };
    };

// Recursive Case:
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        // `Detail` will stop recursion, achieving short-circuit.
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>,AreOverlapping>::value, 
            Detail, 
            AreOverlapping<InspectedVariables..., InspectingVariable>
        >::type::template ProtoPage<RestVariables...>::type;

        static constexpr bool value {std::is_same_v<type, void>};
    };

// Base Case:
    template<auto InspectingVariable>
    struct ProtoPage<InspectingVariable>
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, AreOverlapping>::value, 
            void,
            Shuttle<InspectedVariables..., InspectingVariable>
        >::type;
        
        static constexpr bool value {not std::is_same_v<type, void>};
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAArNIADqgKhE4MHt6%2BeqnpjgKh4VEssfEAnLaY9oUMQgRMxATZPn6BdpgOmQ1NBMWRMXGJ0gqNza25XLbj/WGDZcMVAJS2qF7EyOwc5v5hyN5YANQm/m5ejrSEAJ6n2CYaAIK7%2B4eYJ2cE18mYAPoExCYhAUdwezzMewYBy8x1ObmQY3QWCooKeYIImBYyQMGLhTAuqCOADUmngmNF6KjHmNiF4HEcALICVBEBi3NEAdgsRzGTEcyCOaAYY0wqmSxCO%2BKIRwAbmIvO8TFyScQyRTMEqACKnblanVg9GY7F8jVnKWoAB0VqpNLpBCOQgQFwIlP8VjRTwxWJxprc5qtFoAksKfg5MOgVWr6CD/Pcnrb6Y9iJgAPIyuIGZLJMLAMEgI7JLwUvACpkMFkCW5nYMKUMYiOk8nRu4Bg1csFHTs8gF2o6azCNOgdrtK92PLsTo5e424s0E1ux4eT7u0%2BnKYgV5RMYAap7Lzujo5edJGKffRX%2BTWy1B4dA6k4c7VupcPp9jsEAeg/RwASl0Nuk6ZHH6SggC%2B04%2BniBJHDWdY5pGTaYKQkrzlaf5jAh6oxnG45dgm9rrpu267rhB7tnu%2B5ficABsGj9oOtAmLRRwAO50LQ3aoMkRzJsgAGZMhTDIAgeCYDKOY8ggJAEAAtMgeCbF4hAWi%2BE7HhJXw/B8V6IiAKACPgdRiKpI5nCZy66SAeAKL80RMEovyoCiZxlhWbJwrBXSOEYmGutgpBJqm6bEJm2ZGHcelyt4SEnBR%2B5dvRQK0Mh5mToFaYZkwWY5h5IZeeGvmYAoAbIZ53Q%2BY26pUvFEUgJp7B1UaPpHIRRBbjucLoQQhXFdasZ6fV%2BoeqRk68vygoCCKYoStEqCeLK8qKlylnWb8CisH8MpwvVyEyjed6Lo%2BQ0jXqz7DVRFj2e8IHsOBTUmlB0pld5wCFdVeE9muG5tcRuW1l58GVX5L6jql6mnvV2ndugelCoZmTGXFk5wqlE4rTZdkOU5cKuayVZuM9gOqohdzIelwWhTl/UgFFCopUj8V7bepCo12jrOq6BN5WGDbE1hJUwdzL1vYuDOmdgA3nsdNVi52Y0lhNwoYtNRyzfNtNLRY5b2uja0bb8W2fOeu37aCR1nSd5vvkjEEPXORABj172duDwAtcRUOtag7W%2Bj1C73Bbp3W48H4AFThxHkcfp%2BEcACrYEIscR9HTxh5H6cp88aIQq8MIXvCAhbMkBDYQanr3bOfqoRaSbAKXTyu4yA5MFQXhQnUUPk5l2XhWc0xHDJXBUnpPtwrXvUqYugfxo0/K/PZSjNBADLN637eZHCGjIf3Zi1RryzHfLyDzwoi8EMvq9t90Aib8hZh33vi0HxbR8n2fEBgGATeNGv18MLfRxAhHF3tTfeOoOCrFoJwBIvA/AcC0KQVAnA3DWGsDydYmxFQQh4KQAgmgIGrAANYgGov4C0AAOchHINDUQSBoDQ/gzDkLMBUKoUCOCSF4CwCQ9DSBwIQUgjgvAFAgC3ng%2BBEDSBwFgDARAIB1gEELAQcglA0BYjoHECIG1OCqHIdRGS1FJBHGAMgAUUgLRmF4OGQgJBbx6H4IIEQYh2BSBkIIRQKh1ASNILoaYLFATJE4DwSB0DYH4MQZwFMFwlFHCckcXR%2BjDHGNMUccxZgjgQA8Oo%2BgEpdhcGWLwcRWhVgQCQGo7MOSVEQHKRo%2BIwApD3xoLQDExAREQGiOE6IYQmjXCCbwLpzBiDXBTNEbQXk%2BmkDUWwQQKYGC0F6d4rA0QvDAD9LQWgIjuC8CwCwQwwBxCLIUgDdMmyEGin/BiCZYQMTsIQVcaIgIhkeCwOEgEeBuFbNIMFWaSh%2By7KMFcIw%2BDVhUAMHXIkokWIph%2BHAnBDjhCiHEK4%2BFHi1DhN8foPZKBUGWH0HgaIIjICrC4nUTZMlESnE1KYSw1gzACOCqqLAhKICrE6H/FwDB3CeDaHoEI8xSjlDyGkDIAhJh%2BGmPkEVDABgCuGNMNldRegTG5VMaotQeizBlUMeI8rZhir0LyZoWrFg6tZRgrYEgQkcBgXw8Jgj4l6IMUYkxZjJAWIybgGxuTsEFNwcC1YCBMBMCwPEFlpBiGSDIRUfwHJJAaEkGYSQtENAJGomwzgnDSDcP8FwC01EuDUXIRUchBakhcASNG6itrvGCOEaIv1EiSmyNKfI6JFwqk1JyVotgnAmgsBlByGSTBBQGFPFwCoFpc1nMMrYmG0x4VOKRdIFFSg0XeN0PffxWU%2BlWptfw3ggiomKIuLEqgkpiD9sHcOg4ezUkTqnRkrJFS4gnAhGYX1RTJEts7XEDtqBsnDD7QOuSo76kVC4FvJpLS2kdO8QMnpEz4NDJGWMhwEypmMAILM%2BZ4SlkrLWRsiZOy9kHIQfgXijgTnhPOXxS5nzrk1HCfcx51xnnbAQW8j5ODvlpEwH8kjOZgV8DBQoCFmAoUwomQuxFLjl2yFRV4hBG7MVAupVYXF9zmXEuLpkMlFLLxqdpfSuIjKirwFZTUAGzgICuH1dMPlJRtVCoKJkOzpBJV1GNYK%2BVlm/5KpaCq8VaqrP1E1fypzuq%2BhucNXMRzJrLVrA2Ba/J%2BhQnVoEZwc9l6h0jtveOydFoNAepnd6nNH7/WkEDcG4YYb2GZuzRO%2BNHIK0cg5P4BNSbJDTH3REoRth62fqbfAFtCilF/oA8Qbt2w%2B1JJYAoGUAoZT5Z9GMKxJW7HztkIu2Tbj5CrsUzoAIpAt2BK2busJNbIltvtHEmbRi5sLdlMtk0YxH3/ufaV/w5XG1SLKe92p42Ps02QFmA247fgrYIPPC9hi%2BB0Gg5QWDCCkMLJwSjlD4zPkYZmXMhZZHMDLNWWIQjnziMAvY9so53QqPeJoxcbYOCGO3N4MxnpbHXmqi47wHjvzMQCaBT90F25ROQuhYwKTW2ZMSDk%2B4/b6KjugexTSjT%2BKtOIJ05NTgH5dKGcsHSg9DLbxmaJcF9lNnOVuYcwsbz7nhV1Dcx5zIXm5Wm8VXqwLBrfNu76M7nVMwose8i0a8L8WUsKHNS4876WD2Zbu0cB7i3nsYlexAT1RBSv5MKRVqrIbKBWvqyAFhFp/D%2BASHQrr9CS8ckLdH3rdaxEVeIf4aik6uAsPa6w6iHIuDUOmOw/wF2Mt9cG1ayxtfa0NuKasYK6RnCSCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/are_overlapping.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/are_overlapping.test.hpp)
