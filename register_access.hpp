#include <cstddef>

template <typename T>
class read_only;

template <typename T>
class write_only;

/**
 * A read/write register template
 * 
 * This is also used as a base class for the specfic read only and write only 
 * register templates
 */
template <typename T>
class read_write {
private:
    T volatile *addr;
public:
    read_write(std::size_t volatile address) : addr(reinterpret_cast<T volatile *>(address)) {}

    operator T() const { return *addr; }

    read_write<T>& operator=(T const &t) { *addr = t; return *this;}
public:
    void operator=(write_only<T> const &) = delete;
};

/**
 * A read only register template 
 */
template <typename T>
class read_only : public read_write<T> {
public:
    read_only(std::size_t volatile address) : read_write<T>(address) {}

    operator T() const {return read_write<T>::operator T(); }
public:
    read_only(read_only const &) = delete;
    read_only(read_only const &&) = delete;

    read_only<T>& operator=(T const &t)  = delete;
};


/**
 * A write only register template 
 */
template <typename T>
class write_only : public read_write<T> {
public:
    write_only(std::size_t address) : read_write<T>(address) {}
    /**
     * chaining not allowed since it's write only.
     */
    void operator=(T const &t)  { read_write<T>::operator=(t); }

public:
    write_only(write_only const &) = delete;
    write_only(write_only const &&) = delete;

    operator T() const = delete;

    write_only<T>& operator=(write_only<T> const &)  = delete;
};
