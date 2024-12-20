<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AllConfess`

<p style='text-align: right;'><a href="../../concepts.md#typelivore-all-confess">To Index</a></p>

## Description

`Typelivore::AllConfess` accepts a callable type predicate and a list of elements.
It returns true if the predicate evaluates to `true` for the value result of every element and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...&&Pred{}(Es::value))</code></pre>

## Structure

```C++
template<typename, typename...>
concept AllConfess = REQUIREMENT;
```

## Examples

`AllConfess` turns a fold expression of a callable type predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&Pred_0{}(***))` and `(...&&Pred_0{}(***)) && (...&&Pred_1{}(***))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
using Pred_0 = decltype([](auto...){return true;});

/**** Pred_1 ****/
using Pred_1 = decltype([](auto...){return true;});

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...&&Pred_0{}(Args::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...&&Pred_0{}(Args::value)) && (...&&Pred_1{}(Args::value))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZgCspAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1MrEmOgA%2BhqHB7vbJhoAgl6ZRsenF1cm/gAih1jItAIAE9UpgICYklYkt8IEwvEQAHRIpYmADsFlOBHWDEOBGIXkwXysqO%2BKP8Vke9weewObzO5y41wOd0ez3CwDpF0ZX1%2B/0BILBEKhMLhiORaIxmCxxBxeIJRLRpIVlMeNP2hwAakwgUz9iyHgRMCxUgZDV83KLUIcAJJfbBU8b4hya7VUiVUw6ew6zRzIQ5oBjjTCqVLEQ6Ww4ANzEBMOEttJOVD0VSapaqOVC8OJu%2BsNxtNhP8bmBoOYbCRCIexGACjtVNOAEcvHhTgpDhAK%2BYAGzdk70jTukkQKs1kAgaPeTBLFGPANBkNhmKoTyHTMMCAo9GY7GrsRKBWJlUGo0mphmoslxisTAVke1/z2x6N5utjtI7u996XQcwu9jicEtOcZmD2IHtp2IGfvSXA/sO1YKP%2BMZTjODxzoaC6HEuK5rhuErbjKuL4oWxLfG6qo3IcAAqmDjLqtxptshzYMQxAkA6zS%2BucTAKEorTUFm5pakC5owQ%2BdobmSFgcCstCcEkvB%2BBwWikKgnBuNY1jemsGyYMB/g8KQBCaNJKwANYgEkXYIgAHF2UhJKiXaSAAnP4jlmP4%2BicJIvAsBIGhBIpymqRwvAIUERlKdJpBwLAMCICAawEKk8LkJQaDGnQ8SRNenCqLZAC0TmHMAyB%2BlICJmLwZyECQeDoHo/CCCIYjsFIMiCIoKjqFFpC6FwpAAO7EEwqScDwMlyQpxkqZwADy8IpQQhyoFQhz5V2RWSCVZWHBVZjth4mX0GG5j6UsvCRVoKwQEgGWpFlZAUBA92PSAwBSGYfB0IaxAIRAMQzTE4QtEC428MDzDEECc0xNomAOODpAZWwghzQwtBg71WAxF4wAWrQtAIdwvBYCwhjAOI2MtgjjiRjRM3Bgj8JbAZ4SGrJvW0HgMQjdDHhYDNeJ4H5JOkPTxBLko3xGhT3NGMZKxUAYNYangmCDXNpZI01wiiOI7W611agzf1%2BgUygGmWPoPMIZAKyoKkDTEwV4zoDypiWNYZjBRLxD1Qz9vdLT2QuAw7ieB0eihOEQyVCMA1FFkAhTH4icZMnDDzMMCQDXYIcCH0kyR/ked1AXjQTAMscLAnthV6neizK02fx7nKwKNpmwSJNHDyaQQW8CF62FcVpXlZIlXtrgtWnR5XAXYZisrAgmBMFgCQbqQ5mSP4CKuaikgaJIZiSF2AWWc5XkcD5pB%2Bf4ZgIv4XaotZ/jWUkSRcG5znWQPM0hTCiACKisYrxVuolRaqVnqvROjlNgeVR7bQBBTPazkERcARMpGqRB/YNQGrrFqBtpBGyUCbXqugvrDVGuDXu/dB6zQ4AtZK8IVprQ2ltf0BhXhcHQZgq4EAjoPROnpMwi8rrRQgbA%2BIaUXqoGOiMFBRheFcCCDQQE8R/qA16pDUGSNdHQ1hvDRGYsUaMAIOjTGM0cZ4wJkTJGZM5ZbGUvgU4Dg8D02Jtg1QzNDRI3ZnUGa3NeagwFs4y6/tRYGQllLTAMtyZGHlqAKKSsVYKDVhrLWjAdayCIW1EhshjY9WUpQ82CtPZWGtsEu2W9HbO04K7Ag7sfgVO9r7eIeDA5b3zu45wEBXCNwGjHcoOc9BJwaIMtIGcGit0WGXHohcG4lzTsHXplc5g11GXnJZeQVnN2riMtuPdVjrG7gva%2B9CAGcBHptYqSiOS8IwVg6e%2BBcF6QXpdZepBV7rxGFvcyqigic1vvfJICIXJJGcmYKFIFrLfycv/XqgDbDAKXiksB8AIFJSWrI6RxB4FbBaCwYqLAFCRj9JGR5BZxjVVeXVfBHU9atQkAUzqZDik6ACENEaY0SZ0Omki%2BaUDlqrXWiSslFKqVnhostQR8jhHxD0v4cRoCpHyseri9VJ1xzIFSKkc4lLnLnGpQQc4qgEXqN%2BlooGINob6NtTDOGtMkZmLRhjLGLjMC43xmIexYtHGJPCaQVxIdPGMx8cgFm/jBCBK5jzPmQIwlC0iUjGJGQ4my0SeyUBysmCq3VprbWYtCH63yYyoppsuXcOMFbGw1T4AOydtkYm2w3aWy9pYH2Q8/YBxqR3cuayw4R12dHcOsy67jOyJMydpRNlHPmRXIubRllNwHQ0Jd47c7136JM/Zm7jmd1OW1fliLgrXPNdtUl5KoxSsNLRCAM83lnQ%2BWi66K814b0oL3EFARH7wo8mYQDXBrIaC7JC09Q9OBAJASksyIBd4YPfkkE%2B/gkigY8o5a%2B/gBVntCq%2Bky18qoQcYZ82D4tNGh0kEAA%3D)

By turning `(...&&Pred_0(***))` and `(...&&Pred_1(***))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<typename Predicate, typename...Elements>
concept AllConfess = (...&&Predicate{}(Elements::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBAKykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJn8bgIAE8UoxWJg7spiJh8KIwaQ7vDEcw2AA6YnYV6MAgKaHYEFoBjbFIEO5XWi0DwMKiYBQKO7QgAidwgxMJ5gAbKK0Ri8FjMCYAOxWWW8iCk8HkhQgEAANzEXkwKxW0Ks1xBfwB5xNxzuABVORSvubfmaTkCLfcJegAPoae2HIFeDJGVHoz3evl3LDIWh4zAQEyJKyJJVMLxEIUG%2BXogibBi44i6w1y3kG/xG4GOt3Bj1cH37P0B4BBjFVnn%2BfkRqMImNxhNJlOoNNyiyZ7O5/MlwvF0uuw53ABqTDhNaBYIhHxlMOTREeVJBszzDjnC5Bg5BdzPd1mHyld1ps0wqhSxDum9Qd213hRg4ehYLxsVv7LG5LSoLwc2%2BEEVxeNdoVhTsCUwIUrmIYBKX8alrnRABHLw8HRblmVZAQOS5GD3S9HEkJQoUd2uW8wQfJ8YlQTw7hAhgIHTIdMCzYgcyoMQlALf9jWuSDIXXWD8WRRDkNQ9CkMwbDcM5JkWTZYjULcMigiZWTqLQnkzDFIzVMI9lOU0siuAovTiRoq46PvR87iYli2I4wdh140d1wVXlj3LGcbVmJddyaRxkA9JguXiAhqFAmD5zhGCuB3NCOMnDg1loThEl4PwOC0UhUE4NxrGsC8Ni2T8zH8HhSAITQsrWABrEBEhFQkAA4RSkRJZRFSQAE5/AG2r9E4SReBYCQNCCAqipKjheHVIJGsKrLSDgWAYEQEANgIFIU3ISg0GeOh4kiZFOFUHqAFpBruYBkGQO4pEJMxeElIhiDwdA9H4QQRDEdgpBkQRFBUdQNtIXRrIAd2IJgUk4Hhsty/KmuKzgAHkUyOxlUCoO5bpFB7JCel63skD6BQ8c76Cfcw6pWXh1q0NYICQM6UgusgKAgHm%2BZAYApDMPg6DBYh1QgGIsZicJmjhVHeAV5hiDhHGYm0Op1vqs63gIHGGFoZWYawGIvGANwxFodVuF4LAWEMYBxHN5T6k1TksfvOoUx2erwjBHKYdoPAYiRjWPCwLGCF%2BmaHdIL3iCYpReXBF2w6MJq1ioAwUNnPBMHhnH8RV8HhFEcQwcB%2BQlDULG4f0F2UHKyx9HD9VIDWVAGSye27tmdA%2BVMSxrDMRbk9%2BrAu44roeiyFwGHcTx2j0UIFnKSo9EKTIBCmPxrN33ohi30ZrNqeoBH6SZV7yC/ul1ho5lPkYEgvuYD70S8WlfpZ37WAoKq2wJDow4HlUgC1eBLRJvdR6z1XrvTMAKXAhASCGRZmzHOawECYCYFgBIc82qSH8ISEaspJAaEkGYSQIo5odSGhNDgU1SAzX8GYQk/gRSyi6v4LqiREhcFGkNLqkCsZLRWiANaOctq7S5vtfGx0BZC0ZldNgN04EU0jC7N6Q1CRcEJEVb6JA/oA1kMDau0ha6QwbjDXQ4tEbIxVmAiBUDsYcDxodFMdwiawLJo9bRgYuB6IMd6CA9NeaMwwWYVmDUZHyJUfEE6gtUAM1GIE0WQ0uBBBoFGeIMs5YwzVkrcuxSNZax1g4cuBtyTG1NljC2VsbYsntvVJ2mcdhFXwOiT23sYa%2B2QP7cuQduhYzDhHJW0dOls3juXZOqdMDp2dkYLOoANq53zgoQuxdS6MHLrXCxoMrGyBsdDIq9jm7Z1HlYdu4zZ49z7gIAeQ8R5twsBPaBU8/re27vPJ%2BzgICuC/tZDeZQ3473SHvbId9D6pEhSfTe4KH4L2vp/GF39H5Xz6C/RF/9v5otyLCn%2B8wwV4q4IA4BoMXGYxhjA0m5MbwGCCSEwxKD8A/QweSrB6ycF4IIZQVqs0gghxYWwxIhJhqJCGmYaVRkupCMGmI2lnBJHSPWbI%2BA8iDoE2SYk4gaidjNBYI9FgChNSvU1MEwk4lZhfXZSY/61kDlVyORXU5jcAikEcSjB21KlWLVxoowmxNVAmrNRaq1NrGThNSZE%2BIGD/CxPZptBJsa%2Ba6rTYzLUyAUgpA9JaoaHoo0elDVYyW%2BTKCFKKmUs29Ua0VN1tU1Jhs6lmy6ZgS21tbatMdhnFZ0zSDdKfl7e2RjVB%2BzBMMwQozQ7h0jnCKZsdZmJ3mekRZfbXbhDWRzPgmztklzLonZ1IMJDHIhvXM5OhPVMuMG8juMR7nFUeQwe2uwh6tzHpYD5xUvkz3gIAzFvQl4r0JevZef9t5H3hVkYFcKihZAg%2BfP5WKb6tHRci/52KBiIffuMAYsHiU4dAesTYIDyVMNceIzgJMw3mrfJGtcIVlT2qZrVLlcSeWkFwfg0Yc8RXTQCBwhVtUzCia4F1DQIopX%2BugSq2wUiOMc0FSQ/RfDEjUOqJJ2qA0mH%2BBpQG5ainmpMM%2BjJ9x3KlNJ3yYvSQQA%3D%3D%3D)

## Links

- [Source code](../../../../conceptrodon/typelivore/concepts/all_confess.hpp)
- [Unit test](../../../../tests/unit/concepts/typelivore/all_confess.test.hpp)
- [Example](../../../code/facilities/concepts/typelivore/all_confess/implementation.hpp)
