// <!--
// The MIT License (MIT)
//
// Copyright (c) 2024 Kris Jusiak <kris@jusiak.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
module;
#include "mem"
export module mem;

export namespace mem {
  /**
   * template<class TAllocator> concept allocator_like =
   *   requires(TAllocator alloc, typename TAllocator::value_type* ptr, std::size_t n) {
   *     typename TAllocator::value_type;
   *     { alloc.allocate(n) } -> std::same_as<decltype(ptr)>;
   *     { alloc.deallocate(ptr, n) } -> std::same_as<void>;
   *     #if __cpp_lib_allocate_at_least >= 202302L
   *     { allocate_at_least(n) } -> std::same_as<std::allocation_result<T*, std::size_t>>;
   *     #endif
   *   };
   */
  using mem::allocator_like;

  inline namespace allocator {
    /**
     * template<
     *   class T,
     *   std::align_val_t alignment = 64u,
     *   auto on_error = [] { return nullptr; }
     * > requires (std::has_single_bit(std::size_t(alignment)))
     * struct aligned {
     *   using value_type = T;
     *
     *   constexpr aligned() noexcept = default;
     *   constexpr ~aligned() noexcept = default;
     *
     *   [[nodiscard]]
     *   constexpr auto allocate(std::size_t n) noexcept(noexcept(on_error())) -> T*;
     *
     *   #if __cpp_lib_allocate_at_least >= 202302L
     *   [[nodiscard]]
     *   constexpr auto allocate_at_least(std::size_t n) noexcept(noexcept(allocate(n));
     *   #endif
     *
     *   constexpr void deallocate(T* ptr, std::size_t n) noexcept;
     * };
     */
    using mem::allocator::aligned;

    /**
     * template<
     *   class T,
     *   std::size_t N,
     *   std::align_val_t alignment = alignof(T),
     *   auto on_error = [] { return nullptr; }> requires
     *     (std::has_single_bit(std::size_t(alignment))) and
     *     (std::size_t(alignment) <= alignof(std::max_align_t)) and
     *     (not (N % std::size_t(alignment)))
     * struct stack {
     *   using value_type = T;
     *
     *   constexpr stack() noexcept = default;
     *   constexpr ~stack() noexcept = default;
     *
     *   [[nodiscard]]
     *   constexpr auto allocate(std::size_t n) noexcept(noexcept(on_error())) -> T*;
     *
     *   #if __cpp_lib_allocate_at_least >= 202302L
     *   [[nodiscard]]
     *   constexpr auto allocate_at_least(std::size_t n) noexcept(noexcept(allocate(n));
     *   #endif
     *
     *   constexpr void deallocate(T* ptr, std::size_t n) noexcept;
     * };
     */
    using mem::allocator::stack;

    /**
     * template<class T,
     *   std::size_t N = (1u << 21u),
     *   auto on_error = [] { return nullptr; }>
     * struct transparent_huge_pages {
     *   using value_type = T;
     *
     *   constexpr transparent_huge_pages() noexcept = default;
     *   constexpr ~transparent_huge_pages() noexcept = default;
     *
     *   [[nodiscard]]
     *   constexpr auto allocate(std::size_t n) noexcept(noexcept(on_error())) -> T*;
     *
     *   #if __cpp_lib_allocate_at_least >= 202302L
     *   [[nodiscard]]
     *   constexpr auto allocate_at_least(std::size_t n) noexcept(noexcept(allocate(n));
     *   #endif
     *
     *   constexpr void deallocate(T *ptr, std::size_t n) noexcept;
     * };
     */
    using mem::allocator::transparent_huge_pages;

    /**
     * struct huge_pages {
     *   using value_type = T;
     *
     *   constexpr huge_pages() noexcept = default;
     *   constexpr ~huge_pages() noexcept = default;
     *
     *   [[nodiscard]]
     *   constexpr auto allocate(std::size_t n) noexcept(noexcept(on_error())) -> T*;
     *
     *   #if __cpp_lib_allocate_at_least >= 202302L
     *   [[nodiscard]]
     *   constexpr auto allocate_at_least(std::size_t n) noexcept(noexcept(allocate(n));
     *   #endif
     *
     *   constexpr void deallocate(T *ptr, std::size_t n) noexcept;
     * };
     */
    using mem::allocator::huge_pages;

    /**
     * template<class T, auto on_error = [] { return nullptr; }>
     * struct numa {
     *   using value_type = T;
     *
     *   constexpr explicit numa(auto node = {}) noexcept;
     *   constexpr ~numa() noexcept = default;
     *
     *   [[nodiscard]]
     *   constexpr auto allocate(std::size_t n) noexcept(noexcept(on_error())) -> T*;
     *
     *   #if __cpp_lib_allocate_at_least >= 202302L
     *   [[nodiscard]]
     *   constexpr auto allocate_at_least(std::size_t n) noexcept(noexcept(allocate(n));
     *   #endif
     *
     *   constexpr void deallocate(T* ptr, std::size_t n) noexcept;
     * };
     */
    using mem::allocator::numa;
  } // namespace allocator
} // namespace mem

// -*- mode: c++; -*-
// vim: set filetype=cpp:
