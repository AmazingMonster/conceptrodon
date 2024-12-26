#include <type_traits>

/**** IsPointer ****/
template<typename Type, auto>
concept IsPointer = std::is_pointer_v<Type>;

/**** checker ****/
consteval bool checker(IsPointer<0> auto)
{ return false; }

/**** checker ****/
consteval bool checker(IsPointer<0> auto*)
{ return true; }

/**** Pointer to void ****/
constexpr void* pointer = 0;

/**** Pointer to void* */
constexpr void** pointer_pointer = 0;

/**** Tests ****/
static_assert(! checker(pointer));
static_assert(checker(pointer_pointer));
