#ifndef CTL_ALLOCATOR_TRAITS_H_
#define CTL_ALLOCATOR_TRAITS_H_
#include "type_traits.h"

namespace ctl {

template<typename Alloc>
struct allocator_traits
{
    using allocator_type = Alloc;
    using value_type = typename Alloc::value_type;
    using pointer = typename Alloc::pointer;
    using const_pointer = typename Alloc::const_pointer;
    using void_pointer = void*;
    using const_void_pointer = const void*;
    using difference_type = typename Alloc::difference_type;
    using size_type = typename Alloc::size_type;

    using propagate_on_container_copy_assignment = false_type;
    using propagate_on_container_move_assignment = true_type;
    using propagate_on_container_swap = false_type;
    using is_always_equal = true_type;

    template<typename T>
    using rebind_alloc = typename Alloc::template rebind<T>::other;

    template<typename T>
    using rebind_traits = allocator_traits<rebind_alloc<T>>;

    __attribute__((__always_inline__)) static pointer allocate(Alloc& a,
                                                               size_type n)
    {
        return a.allocate(n);
    }

    __attribute__((__always_inline__)) static void deallocate(Alloc& a,
                                                              pointer p,
                                                              size_type n)
    {
        a.deallocate(p, n);
    }

    template<typename T, typename... Args>
    __attribute__((__always_inline__)) static void construct(Alloc& a,
                                                             T* p,
                                                             Args&&... args)
    {
        ::new ((void*)p) T(static_cast<Args&&>(args)...);
    }

    template<typename T>
    __attribute__((__always_inline__)) static void destroy(Alloc& a, T* p)
    {
        p->~T();
    }

    __attribute__((__always_inline__)) static size_type max_size(
      const Alloc& a) noexcept
    {
        return __PTRDIFF_MAX__ / sizeof(value_type);
    }

    __attribute__((__always_inline__)) static Alloc
    select_on_container_copy_construction(const Alloc& a)
    {
        return a;
    }
};

} // namespace ctl

#endif // CTL_ALLOCATOR_TRAITS_H_
