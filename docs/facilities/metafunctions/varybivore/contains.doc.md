<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Contains`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-contains">To Index</a></p>

## Description

`Varybivore::Contains` accepts a list of variables and returns a predicate.
When invoked by an argument, the predicate returns true if the argument is in the previously provided list and returns false if otherwise.

<pre><code>   Vs...
-> Arg
-> Arg &in; Vs... ?
   true : false</code></pre>

## Type Signature

```Haskell
Contains
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Contains
{
    template<auto>
    alias Page = RESULT;

    template<auto>
    static constexpr bool Page_v = RESULT;
};
```

## Examples

We will check whether `1` or `-1`  is inside `0, 1, 2, 2`.

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction = Contains<0, 1, 2, 2>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1>::value);
static_assert(! Metafunction<-1>::value);
```

## Implementation

`Varybivore::Contains` uses `Varybivore::IsSame` to compare variables and a fold expression to combine results.

Here's the entire implementation:

```C++
template<auto...Variables>
struct Contains
{
    template<auto Inspecting>
    struct ProtoPage
    {   
        static constexpr bool value 
        {(...||(IsSame<Variables, Inspecting>::value))};
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxCAArFykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpgprozIeJgK1wenF1fHv4df5zOlwO1yEnkIzQAngBJBRCViYD77AEETAsFIGVEmADMbiYXiIpGu%2BKIOOwQLGxC8DlB4PGMLhCKBJgA7BZrjNHMhrmgGGNMKoUsRrtFUJ5rgA3MReRGsixUMRKVm3HHs5Wq5kXVHozGYHF4gmoa4ANWaeCY0XoZIpBCpNLBtAhxAZ8LY%2BtNxHNlswRI9Xqt2PJFzlHKaXJ5An5guFovFUu8srZtpl6uxapZKrTmuBN1hrsRnyB2oxTCxuJJRoAKs1gJgCESKwA6Zt%2Bi30BTWi6U6kEa55pnBtlA64j0OlvDc3lRoUisW0SXSvUXUfXOUQZuN8wANm3DqdLqZuNb3oUROrxFrBDJIBA8Zli1TVkHmafgO%2Bfw//yBPx2fZ1aMYMMsiRPYAR/T8/gBIs0RLMsDSIDdj3bTtzm7GkPEEJgwg7QdXxXYtdX1Cs%2Bz5R4HDCYAUJXNDe2UYhUCIZQmFrYdRxDEdWJXEdOQnCM%2BVRaNZzjRdV2XLiOLZddm1ZNwZIgfs3SPM02zeIloVIzByKMa9b0XRYHwzDUxIkl9s3wmDCPLQ0N3OYBiEwADBA7QNOOuLwMiMa4mNrVdsVuLz6MY5i9VxWz7McggFA3a0s2fIy3xzCDkW/EFsFUVgMQLZL3yS7KEp/a4AFk6yYKgvAYciBBAk5oJ1UsQvg1AbIvZyg3OdyKKKkqyoq%2BpfP8jCmmw/UNCJZJrkCCaUJvbyGvOFropc2L8pBSs3l7QsuyA5AAH0mAUJQWggYqmh6yqGH1LgdLvTAH2Wnjdv2w6CAgMAwC607yvO/UAForsDG8bruiwOGWWhOASXg/A4LRSFQThZMsawOVWdZZTMbEeFIAhNFB5YAGtEkkRsNAADjMMwAE5Ka4BIydJrgWRZaRwY4SReBYCQNFG6HYfhjheAUEBRpxmHQdIOBYBgRAQFWAgUgJchKDQdE6DiCIEU4VRSa3H6t0ka5gGQbkpEbMxeEwfAiE9dA9H4QQRDEdgpBkQRFBUdQxdIXRkgAd2IJgUk4HgwYhqHcbhzgAHkCQV3tUCoa5td1/XDeN65TbMa4IA8VX6GFcxMcWXhRa0ZYICQFWUjVsgKAgKua5AYApECGhaFRYghYgaII%2BiMIoWD3g%2B%2BYZ0o%2BibRNNFrGVbYQQo4YWhIQjrBoi8YA8VoWghe4XgsBYQxgHEL38Hs8iJTeCOBU0glNixsJUVZ2HHWiAPnQ8LAI9tPBOZ30hz%2BIUUSh7j7yMI6IwuNlhUAMMABQxpXi%2Byjo8aGWN7bCFEOIF2qD3ZqAjj7fQB8UDWGsPoPA0QhaQGWKgFI9Rt4/TGOgHEtxTBI0sGYPm/8bYXwoV0SeWQXAMHcJ4doegQhhEGBUYYyRCiZAEJMPwUj0gyIYHMIY8RRi1F4QIXoEwhF5HUd0LR4x%2BhiPmJI2wRi5F6BmC0FREi1HLAUKjDYEhQ4cEhqQXmvB%2BZJx1nrA2RsTbEyzhAXAhASCrgxlwYu2MIHLAQJgJgWB4gQAJv4bEjZKbYmZhoAIkgtzcwSFuSm%2BhODs1IJzTGjYtxcC3KTSmDMtwJEkLTTJW4PER35oLYWMSxbl2lhXWWsdFZ1wbvnDWbBODNBYBKFkP0mA8gMJ5LglNGxcBJhbK2JA8C22SKgx2GDpBYKUDgr2uhAj%2B0DoPVx7jPGRw4DHeWBJrgJx8SnA2yBFnAAzistZGhs652rvnCJ2IzDRNLuLAZoy4hK3rqgPOwwPkH2WVwUabcO5dx7l7YeA9f7YtHuPSeg9SAz0AvPRey9MCr3XmILeRK94HyPrDE%2BvDz7b1hlfZAN8iX31qBHZ%2Br9ITv02LDL%2BP8sb/0AZgYBDKKIQL4NA2B8DEGMCJXs9BztDmyGwZ7WGZz8HgOYVYSwJCyHwEodQrItD6GMMNdYNhXiOHbK4Sknh51%2BGCNyPIoIAjbELAUUULIlj/VKN9WYuwmiGgWN0V68N51tHGLKKoqxUbPXJtmCYpNUSVhrGcVm1mNyOmcFeX4hZB9vmrJJtnUJ1tgVRJLrE0g8TEnDBdazMpFSVk5JZAkSmTNsS5P1skW5nTbDdPBX0%2BAAy5ZxxhVC4g4zNhTNTiwBQEpuQSmWY2XUYwNlhJtnbWQ%2ByNWu3kMcnVOgQDYlIBcoOO9rnhy9vzB5cdnmJ1UMu1d67N3bt7DnOFgK4jAuxGCuVkL/011neB/Ot5kApBSDtDdlMdo/p2u%2Bw5dB0WUExbDPFS9cX93xRPBwRKSVzwXnhpllK14b1pb/eloDhW7zwKfRwrLL6qGvqiblgheVe35VCIVn9PRit4BK9IUq0QyvAb0%2BVzFFWYAQUg1Vh71USE1W7M9uDL36uMEQ41z9yEuqoTQzgWx6GEJYRYe1cNHVYEMw4jRbqICuCDd69Aoa1GpEUfUVz0j6geasY5%2Bo8bXOxuC0YgLowU3CKi%2BmxNdiXHZrRol/ND6%2BZFrQ9cFda7JTfvqmMKtmyC6RJA70uJCSkmUFce2kAVNGzYmxAkOmzTuYNZZLU9pj7OBdJFg2wmkgEgZMZiybmpNJA0y4OTMwbTWbYjS147rPSy6uPNp19LAslt4z/nEDIzhJBAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/contains/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/contains.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/contains.test.hpp)
