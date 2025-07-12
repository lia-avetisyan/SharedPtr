template<typename T>
class SharedPtr {
private:
    T* ptr;
    int* ref_count;
    int* weak_count;

public:

    SharedPtr() noexcept : ptr(nullptr), ref_count(nullptr), weak_count(nullptr) {}

    explicit SharedPtr(T* p = nullptr) : ptr(p) {
        if (ptr) {
            ref_count = new int(1);
        } else {
            ref_count = nullptr;
        }
    }

    SharedPtr(const SharedPtr& other) {
        ptr = other.ptr;
        ref_count = other.ref_count;
        weak_count = other.weak_count;
        if (ref_count) {
            ++(*ref_count);
        }
    }

    SharedPtr(SharedPtr&& other) noexcept {
        ptr = other.ptr;
        ref_count = other.ref_count;
        weak_count = other.weak_count;

        other.ptr = nullptr;
        other.ref_count = nullptr;
        other.weak_count = nullptr;
    }



    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            weak_count = other.weak_count;
            if (ref_count) {
                ++(*ref_count);
            }
        }
        return *this;
    }



    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            weak_count = other.weak_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
            other.weak_count = nullptr;
        }
        return *this;
    }

    ~SharedPtr() {
        release();
    }

    const T& operator*() const noexcept {
        return *ptr;
    }

    const T* operator->() const noexcept {
        return ptr;
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }


    T* get() const noexcept {
        return ptr;
    }

    int use_count() const noexcept {
        return ref_count ? *ref_count : 0;
    }

    void reset(T* new_ptr = nullptr) {
        release();
        ptr = new_ptr;
        if (new_ptr) {
            ref_count = new int(1);
        }
        else {
            ref_count = nullptr;
        }
    }

private:
    void release() {
        if (ref_count) {
            --(*ref_count);
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
                if (weak_count && *weak_count == 0) {
                    delete weak_count;
                }
            }
            ptr = nullptr;
            ref_count = nullptr;
            weak_count = nullptr;
        }
    }
};



int main() {

    return 0;
}
