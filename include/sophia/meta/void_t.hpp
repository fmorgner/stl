#ifndef SOPHIA_META__VOID_T
#define SOPHIA_META__VOID_T

/**
 * @file void_t.hpp
 * @author Felix Morgner
 * @since 0.1
 */

namespace sophia::meta
  {

  namespace internal
    {
    /**
     * @internal
     * @author Felix Morgner
     * @since 0.1
     *
     * @brief A template class to transform an arbitrary amount of arbitrary types into void.f
     *
     * This class enables the use of SFINAE to select template specilizations based on contraints base on the concepts of
     * "more specialized" template instantiations.
     *
     * @note This class is not be required if C++ newer than 14 is used.
     */
    template<typename ...>
    struct void_type
      {
      /**
       * @internal
       * @author Felix Morgner
       * @since 0.1
       *
       * An alias for void, so that void_type::type is always valid
       */
      using type = void;
      };
    }

  /**
   * @author Felix Morgner
   * @since 0.1
   *
   * @brief A template type alias to transform an arbitrary amount of arbitrary types into void.
   */
  template<typename ...Erased>
  using void_t = typename internal::void_type<Erased...>::type;

  }

#endif
