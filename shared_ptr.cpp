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
        if (ref_count) {
            ++(*ref_count);
        }
    }


    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = std::move(other.ptr);
            ref_count = std::move(other.ref_count);
        }
        return *this;
    };

    ~SharedPtr() {
        release();
    }

    T& operator*() const noexcept {
        return *ptr;
    }

    T* operator->() const noexcept {
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
            }
            ptr = nullptr;
            ref_count = nullptr;
        }
    }
};


int main() {

    return 0;
}
