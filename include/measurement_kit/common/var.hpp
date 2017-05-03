// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.
#ifndef MEASUREMENT_KIT_COMMON_VAR_HPP
#define MEASUREMENT_KIT_COMMON_VAR_HPP

#include <memory>
#include <stdexcept>

namespace mk {

template <typename T> class Var : public std::shared_ptr<T> {
    using std::shared_ptr<T>::shared_ptr;

  public:
    T *get() const { return operator->(); }

    T *operator->() const {
        if (std::shared_ptr<T>::get() == nullptr) {
            throw std::runtime_error("null pointer");
        }
        return std::shared_ptr<T>::operator->();
    }

    typename std::add_lvalue_reference<T>::type operator*() const {
        if (std::shared_ptr<T>::get() == nullptr) {
            throw std::runtime_error("null pointer");
        }
        return std::shared_ptr<T>::operator*();
    }

    template <typename R> Var<R> as() {
        return std::dynamic_pointer_cast<R>(*this);
    }

  protected:
  private:
    // NO ATTRIBUTES HERE BY DESIGN. DO NOT ADD ATTRIBUTES HERE BECAUSE
    // DOING THAT CREATES THE RISK OF OBJECT SLICING.
};

} // namespace mk
#endif
