#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

template <typename T> class weakPtr;
template <typename T> class sharedPtr;

class ControlBlock {
	private:
	    unsigned int sharedPtrCounter;
		unsigned int weakPtrCounter;
	public:
	    ControlBlock() {
			cout << "[DEBUG] ControlBlock constructor called: " << this << endl;
			sharedPtrCounter = 0;
			weakPtrCounter   = 0;
		}

		~ControlBlock() {
			cout << "[DEBUG] ControlBlock destructor called: " << this << endl;
		}
	 
	    void reset() { 
	      sharedPtrCounter = 0;
		  weakPtrCounter   = 0;
	    }
	 
	    unsigned int getSharedPtrCounter() { 
	      return sharedPtrCounter; 
	    }
	 
	 	unsigned int getWeakPtrCounter() { 
	      return weakPtrCounter; 
	    }

		void sharedPtrCounterIncrement() {
			sharedPtrCounter++;
		}

		void weakPtrCounterIncrement() {
			weakPtrCounter++;
		}

		void sharedPtrCounterDecrement() {
			if (sharedPtrCounter > 0) {
				sharedPtrCounter--;
			}
		}

		void weakPtrCounterDecrement() {
			if (weakPtrCounter > 0) {
				weakPtrCounter--;
			}
		}

		void debugPrint() {
			cout << "Shared pointer counter: " << sharedPtrCounter << endl;
			cout << "Weak pointer counter: "   << weakPtrCounter << endl;
		}
};
 
template <typename T> class sharedPtr {
	friend weakPtr;

	// makeShared frined function declaration.
	template <typename T, typename ...cargc_t>
	friend sharedPtr<T> makeShared(cargc_t ...constructorArguments);

	private:
	    ControlBlock *ctrlBlock;
	    T            *rawPtr;
	public:
	    sharedPtr(T *ptr = nullptr) {
	        rawPtr = ptr;
	        if (ptr) {
				ctrlBlock = new ControlBlock();
				ctrlBlock->sharedPtrCounterIncrement();
			}
	    }

	    sharedPtr(sharedPtr<T> &other) {
	        rawPtr    = other.rawPtr;
	        ctrlBlock = other.ctrlBlock;
	        ctrlBlock->sharedPtrCounterIncrement();
	    }
		
		
	    sharedPtr(weakPtr<T> &other) {
	        this->rawPtr    = other.rawPtr;
	        this->ctrlBlock = other.ctrlBlock;
			if (this->ctrlBlock != nullptr) {
	        	this->ctrlBlock->sharedPtrCounterIncrement();
			}
		}

		sharedPtr(sharedPtr<T> &&other) {
			this->rawPtr    = other.rawPtr;
			this->ctrlBlock = other.ctrlBlock;
	        other.rawPtr    = nullptr;
	        other.ctrlBlock = nullptr;
	    }

		void sharedPtrCounterIncrement() {
			ctrlBlock->sharedPtrCounterIncrement();
		}
		
	    unsigned int useCount() {
			if (ctrlBlock == nullptr) {
				return 0;
			}
	    	return ctrlBlock->getSharedPtrCounter(); 
	    }
	 
	 	// returns raw pointer to object.
	    T *get() { 
	      return rawPtr; 
	    }
	 
	 	// returns pointer to raw pointer.
	    T &operator*() { 
	      return *rawPtr; 
	    }

		void operator =(const sharedPtr<T> &other) { 
			this->rawPtr    = other.rawPtr;
			this->ctrlBlock = other.ctrlBlock;
			this->ctrlBlock->sharedPtrCounterIncrement();
	    }
	 
	    T *operator->() { 
	      return rawPtr;
	    }
	   
	    ~sharedPtr() {
			// cout << "sharedPtr destructor: " << this << endl;
			if (ctrlBlock != nullptr) {
	        	ctrlBlock->sharedPtrCounterDecrement();
			}
			if (ctrlBlock != nullptr && ctrlBlock->getSharedPtrCounter() == 0) {
	            delete rawPtr;
	        }
			if (ctrlBlock != nullptr &&  ctrlBlock->getSharedPtrCounter() == 0 && ctrlBlock->getWeakPtrCounter() == 0) {
	            delete ctrlBlock;
			}
	    }
};

template <typename T> class weakPtr {
	friend sharedPtr; 
	private:
	    ControlBlock *ctrlBlock = nullptr;
	    T            *rawPtr    = nullptr;

	public:
	    weakPtr(sharedPtr<T> &other) {
	        this->rawPtr    = other.rawPtr;
	        this->ctrlBlock = other.ctrlBlock;
			this->ctrlBlock->weakPtrCounterIncrement();
	    }

		weakPtr() {
			this->rawPtr    = nullptr;
	        this->ctrlBlock = nullptr;
		}

		// Converts weakPtr to sharedPtr.
		sharedPtr<T> lock() {
			if (this->ctrlBlock != nullptr)
				this->ctrlBlock->weakPtrCounterDecrement();
			return sharedPtr(*this);
		}

	    weakPtr(sharedPtr<T> &&other) {
	        rawPtr    = other.rawPtr;
	        ctrlBlock = other.ctrlBlock;
			other.rawPtr    = nullptr;
	        other.ctrlBlock = nullptr;
	    }
	 
	    unsigned int use_count() { 
			if (ctrlBlock == nullptr)
				return 0;
	      	return ctrlBlock->getSharedPtrCounter(); 
	    }
	 	
		bool expired() {
			if (ctrlBlock == nullptr || ctrlBlock->getSharedPtrCounter() == 0) {
				return true;
			}
			return false;
		}

	 	void reset() {
	 		if (ctrlBlock) {
	 			delete ctrlBlock;
				ctrlBlock = nullptr;
			}
			if (rawPtr) {
	        	delete rawPtr;
				rawPtr = nullptr;
			}
		 }

	    ~weakPtr() {
			if (ctrlBlock != nullptr) {
				ctrlBlock->weakPtrCounterIncrement();
			}

			if (ctrlBlock != nullptr && ctrlBlock->getSharedPtrCounter() == 0) {
	            delete rawPtr;
	        }
			if (ctrlBlock != nullptr &&  ctrlBlock->getSharedPtrCounter() == 0 && ctrlBlock->getWeakPtrCounter() == 0) {
	            delete ctrlBlock;
			}
	    }
};




template <typename T, typename ... cargc_t> 
sharedPtr<T> makeShared(cargc_t ... constructorArguments) {
	sharedPtr<T> res;
	uint8_t *tmp = new uint8_t[sizeof(T) + sizeof(ControlBlock)];
	new(tmp)T(constructorArguments...);
	new(tmp + sizeof(T))ControlBlock();
	res.rawPtr    = (T *)tmp;
	// res.ctrlBlock = reinterpret_cast<ControlBlock *>(tmp + sizeof(T));
	res.ctrlBlock = (ControlBlock *)(tmp + sizeof(T));
	res.ctrlBlock->sharedPtrCounterIncrement();
	return res;
}
